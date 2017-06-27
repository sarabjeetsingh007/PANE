// $Id$


#ifndef _BUFFER_HPP_
#define _BUFFER_HPP_

#include <vector>

#include "vc.hpp"
#include "flit.hpp"
#include "outputset.hpp"
#include "routefunc.hpp"
#include "config_utils.hpp"

class Buffer : public Module {
  
  int _occupancy;
  int _size;

  vector<VC*> _vc;

#ifdef TRACK_BUFFERS
  vector<int> _class_occupancy;
#endif

public:
  
  Buffer( const Configuration& config, int outputs,
	  Module *parent, const string& name );
  ~Buffer();

  void AddFlit( int vc, Flit *f );

  inline Flit *RemoveFlit( int vc )
  {
    --_occupancy;
#ifdef TRACK_BUFFERS
    int cl = _vc[vc]->FrontFlit()->cl;
    assert(_class_occupancy[cl] > 0);
    --_class_occupancy[cl];
#endif
    return _vc[vc]->RemoveFlit( );
  }

inline void printbuf(int vc) const
{
	cout<<", vc:"<<vc<<"\n";
	_vc[vc]->printbuf();
}
  
  inline Flit *FrontFlit( int vc ) const
  {
    return _vc[vc]->FrontFlit( );
  }
  
  inline bool Empty( int vc ) const
  {
    return _vc[vc]->Empty( );
  }

  inline bool Full( ) const
  {
    return _occupancy >= _size;
  }

  inline VC::eVCState GetState( int vc ) const
  {
    return _vc[vc]->GetState( );
  }

  inline void SetState( int vc, VC::eVCState s )
  {
    _vc[vc]->SetState(s);
  }

  inline const OutputSet *GetRouteSet( int vc ) const
  {
    return _vc[vc]->GetRouteSet( );
  }

  inline void SetRouteSet( int vc, OutputSet * output_set )
  {
    _vc[vc]->SetRouteSet(output_set);
  }

  inline void SetOutput( int vc, int out_port, int out_vc )
  {
    _vc[vc]->SetOutput(out_port, out_vc);
  }

  inline int GetOutputPort( int vc ) const
  {
    return _vc[vc]->GetOutputPort( );
  }

  inline int GetOutputVC( int vc ) const
  {
    return _vc[vc]->GetOutputVC( );
  }

  inline int GetPriority( int vc ) const
  {
    return _vc[vc]->GetPriority( );
  }

  inline void Route( int vc, tRoutingFunction rf, const Router* router, const Flit* f, int in_channel )
  {
    _vc[vc]->Route(rf, router, f, in_channel);
  }

  // ==== Debug functions ====

  inline void SetWatch( int vc, bool watch = true )
  {
    _vc[vc]->SetWatch(watch);
  }

  inline bool IsWatched( int vc ) const
  {
    return _vc[vc]->IsWatched( );
  }

  inline int GetOccupancy( ) const
  {
    return _occupancy;
  }

  inline int GetOccupancy( int vc ) const
  {
    return _vc[vc]->GetOccupancy( );
  }

#ifdef TRACK_BUFFERS
  inline int GetOccupancyForClass(int c) const
  {
    return _class_occupancy[c];
  }
#endif

  void Display( ostream & os = cout ) const;
};

#endif 
