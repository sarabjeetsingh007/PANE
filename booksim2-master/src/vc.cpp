// $Id$


/*vc.cpp
 *
 *this class describes a virtual channel in a router
 *it includes buffers and virtual channel state and controls
 *
 *This class calls the routing functions
 */

#include <limits>
#include <sstream>

#include "globals.hpp"
#include "booksim.hpp"
#include "vc.hpp"

const char * const VC::VCSTATE[] = {"idle",
				    "routing",
				    "vc_alloc",
				    "active"};

VC::VC( const Configuration& config, int outputs, 
	Module *parent, const string& name )
  : Module( parent, name ), 
    _state(idle), _out_port(-1), _out_vc(-1), _pri(0), _watched(false), 
    _expected_pid(-1), _last_id(-1), _last_pid(-1)
{
  _lookahead_routing = !config.GetInt("routing_delay");
  _route_set = _lookahead_routing ? NULL : new OutputSet( );

  string priority = config.GetStr( "priority" );
  if ( priority == "local_age" ) {
    _pri_type = local_age_based;
  } else if ( priority == "queue_length" ) {
    _pri_type = queue_length_based;
  } else if ( priority == "hop_count" ) {
    _pri_type = hop_count_based;
  } else if ( priority == "none" ) {
    _pri_type = none;
  } else {
    _pri_type = other;
  }

  _priority_donation = config.GetInt("vc_priority_donation");
}

VC::~VC()
{
  if(!_lookahead_routing) {
    delete _route_set;
  }
}

void VC::AddFlit( Flit *f )
{
  assert(f);

  if(_expected_pid >= 0) {
    if(f->pid != _expected_pid) {
      ostringstream err;
      err << "Received flit " << f->id << " with unexpected packet ID: " << f->pid 
	  << " (expected: " << _expected_pid << ")";
      Error(err.str());
    } else if(f->tail) {
      _expected_pid = -1;
    }
  } else if(!f->tail) {
    _expected_pid = f->pid;
  }
    
  // update flit priority before adding to VC buffer
  if(_pri_type == local_age_based) {
    f->pri = numeric_limits<int>::max() - GetSimTime();
    assert(f->pri >= 0);
  } else if(_pri_type == hop_count_based) {
    f->pri = f->hops;
    assert(f->pri >= 0);
  }
  _buffer.push_back(f);
  UpdatePriority();
}

Flit *VC::RemoveFlit( )
{
  Flit *f = NULL;
  if ( !_buffer.empty( ) ) {
    f = _buffer.front( );
    _buffer.pop_front( );
    _last_id = f->id;
    _last_pid = f->pid;
    UpdatePriority();
  } else {
    Error("Trying to remove flit from empty buffer.");
  }
  return f;
}



void VC::SetState( eVCState s )
{
  Flit * f = FrontFlit();
  
  if(f && f->watch)
    *gWatchOut << GetSimTime() << " | " << FullName() << " | "
		<< "Changing state from " << VC::VCSTATE[_state]
		<< " to " << VC::VCSTATE[s] << "." << endl;
  
  _state = s;
}

const OutputSet *VC::GetRouteSet( ) const
{
  return _route_set;
}

void VC::SetRouteSet( OutputSet * output_set )
{
  _route_set = output_set;
  _out_port = -1;
  _out_vc = -1;
}

void VC::SetOutput( int port, int vc )
{
  _out_port = port;
  _out_vc   = vc;
}

void VC::UpdatePriority()
{
  if(_buffer.empty()) return;
  if(_pri_type == queue_length_based) {
    _pri = _buffer.size();
  } else if(_pri_type != none) {
    Flit * f = _buffer.front();
    if((_pri_type != local_age_based) && _priority_donation) {
      Flit * df = f;
      for(size_t i = 1; i < _buffer.size(); ++i) {
	Flit * bf = _buffer[i];
	if(bf->pri > df->pri) df = bf;
      }
      if((df != f) && (df->watch || f->watch)) {
	*gWatchOut << GetSimTime() << " | " << FullName() << " | "
		    << "Flit " << df->id
		    << " donates priority to flit " << f->id
		    << "." << endl;
      }
      f = df;
    }
    if(f->watch)
      *gWatchOut << GetSimTime() << " | " << FullName() << " | "
		  << "Flit " << f->id
		  << " sets priority to " << f->pri
		  << "." << endl;
    _pri = f->pri;
  }
}


void VC::Route( tRoutingFunction rf, const Router* router, const Flit* f, int in_channel )
{
  rf( router, f, in_channel, _route_set, false );
  _out_port = -1;
  _out_vc = -1;
}

// ==== Debug functions ====

void VC::SetWatch( bool watch )
{
  _watched = watch;
}

bool VC::IsWatched( ) const
{
  return _watched;
}

void VC::Display( ostream & os ) const
{
  if ( _state != VC::idle ) {
    os << FullName() << ": "
       << " state: " << VCSTATE[_state];
    if(_state == VC::active) {
      os << " out_port: " << _out_port
	 << " out_vc: " << _out_vc;
    }
    os << " fill: " << _buffer.size();
    if(!_buffer.empty()) {
      os << " front: " << _buffer.front()->id;
    }
    os << " pri: " << _pri;
    os << endl;
  }
}
