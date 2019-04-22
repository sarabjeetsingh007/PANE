/*router.cpp
 *
 *The base class of either iq router or event router
 *contains a list of channels and other router configuration variables
 *
 *The older version of the simulator uses an array of flits and credit to 
 *simulate the channels. Newer version ueses flitchannel and credit channel
 *which can better model channel delay
 *
 *The older version of the simulator also uses vc_router and chaos router
 *which are replaced by iq rotuer and event router in the present form
 */

#include "booksim.hpp"
#include <iostream>
#include <cassert>
#include "router.hpp"

//////////////////Sub router types//////////////////////
#include "iq_router.hpp"
//#include "event_router.hpp"
//#include "chaos_router.hpp"
///////////////////////////////////////////////////////

int const Router::STALL_BUFFER_BUSY = -2;
int const Router::STALL_BUFFER_CONFLICT = -3;
int const Router::STALL_BUFFER_FULL = -4;
int const Router::STALL_BUFFER_RESERVED = -5;
int const Router::STALL_CROSSBAR_CONFLICT = -6;

Router::Router( const Configuration& config, Module *parent, const string & name, int id, int inputs, int outputs ) :
TimedModule( parent, name ), _id( id ), _inputs( inputs ), _outputs( outputs ), _partial_internal_cycles(0.0)
{
  _crossbar_delay   = ( config.GetInt( "st_prepare_delay" ) + config.GetInt( "st_final_delay" ) );
  _credit_delay     = config.GetInt( "credit_delay" );
  _input_speedup    = config.GetInt( "input_speedup" );
  _output_speedup   = config.GetInt( "output_speedup" );
  _internal_speedup = config.GetFloat( "internal_speedup" );
  _classes          = config.GetInt( "classes" );

#ifdef TRACK_FLOWS
  _received_flits.resize(_classes, vector<int>(_inputs, 0));
  _stored_flits.resize(_classes);
  _sent_flits.resize(_classes, vector<int>(_outputs, 0));
  _active_packets.resize(_classes);
  _outstanding_credits.resize(_classes, vector<int>(_outputs, 0));
#endif

#ifdef TRACK_STALLS
  _buffer_busy_stalls.resize(_classes, 0);
  _buffer_conflict_stalls.resize(_classes, 0);
  _buffer_full_stalls.resize(_classes, 0);
  _buffer_reserved_stalls.resize(_classes, 0);
  _crossbar_conflict_stalls.resize(_classes, 0);
#endif

}

void Router::AddInputChannel( FlitChannel *channel, CreditChannel *backchannel )
{
  _input_channels.push_back( channel );
  _input_credits.push_back( backchannel );
  channel->SetSink( this, _input_channels.size() - 1 ) ;
}

void Router::AddOutputChannel( FlitChannel *channel, CreditChannel *backchannel )
{
  _output_channels.push_back( channel );
  _output_credits.push_back( backchannel );
  _channel_faults.push_back( false );
  channel->SetSource( this, _output_channels.size() - 1 ) ;
}

void Router::Evaluate( )
{
  _partial_internal_cycles += _internal_speedup;
  while( _partial_internal_cycles >= 1.0 ) {
    _InternalStep( );
    _partial_internal_cycles -= 1.0;
  }
}

void Router::OutChannelFault( int c, bool fault )
{
  assert( ( c >= 0 ) && ( (size_t)c < _channel_faults.size( ) ) );

  _channel_faults[c] = fault;
}

bool Router::IsFaultyOutput( int c ) const
{
  assert( ( c >= 0 ) && ( (size_t)c < _channel_faults.size( ) ) );

  return _channel_faults[c];
}

/*Router constructor*/
Router *Router::NewRouter( const Configuration& config, Module *parent, const string & name, int id, int inputs, int outputs )
{
  const string type = config.GetStr( "router" );
  Router *r = NULL;
  if ( type == "iq" ) {
    r = new IQRouter( config, parent, name, id, inputs, outputs );
  } 
//	else if ( type == "event" ) {
//    r = new EventRouter( config, parent, name, id, inputs, outputs );
//  } else if ( type == "chaos" ) {
//    r = new ChaosRouter( config, parent, name, id, inputs, outputs );
//  } 
else {
    cerr << "Unknown router type: " << type << endl;
  }
  /*For additional router, add another else if statement*/
  /*Original booksim specifies the router using "flow_control"
   *we now simply call these types. 
   */

  return r;
}
