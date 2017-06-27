// $Id$


#ifndef _VC_HPP_
#define _VC_HPP_

#include <deque>

#include "flit.hpp"
#include "outputset.hpp"
#include "routefunc.hpp"
#include "config_utils.hpp"

class VC : public Module {
public:
  enum eVCState { state_min = 0, idle = state_min, routing, vc_alloc, active, 
		  state_max = active };
  struct state_info_t {
    int cycles;
  };
  static const char * const VCSTATE[];
  
private:

  deque<Flit *> _buffer;
  
  eVCState _state;
  
  OutputSet *_route_set;
  int _out_port, _out_vc;

  enum ePrioType { local_age_based, queue_length_based, hop_count_based, none, other };

  ePrioType _pri_type;

  int _pri;

  int _priority_donation;

  bool _watched;

  int _expected_pid;

  int _last_id;
  int _last_pid;

  bool _lookahead_routing;

public:
  
  VC( const Configuration& config, int outputs,
      Module *parent, const string& name );
  ~VC();

  void AddFlit( Flit *f );
	
	inline void printbuf() const
	{
		for (unsigned i=0; i<_buffer.size(); i++)
		    std::cout << ' ' << _buffer.at(i)->id<<endl;
		  cout<<"------\n";
	}
	
  inline Flit *FrontFlit( ) const
  {
    return _buffer.empty() ? NULL : _buffer.front();
  }
  
  Flit *RemoveFlit( );
  
  
  inline bool Empty( ) const
  {
    return _buffer.empty( );
  }

  inline VC::eVCState GetState( ) const
  {
    return _state;
  }


  void SetState( eVCState s );

  const OutputSet *GetRouteSet( ) const;
  void SetRouteSet( OutputSet * output_set );

  void SetOutput( int port, int vc );

  inline int GetOutputPort( ) const
  {
    return _out_port;
  }


  inline int GetOutputVC( ) const
  {
    return _out_vc;
  }

  void UpdatePriority();
 
  inline int GetPriority( ) const
  {
    return _pri;
  }
  void Route( tRoutingFunction rf, const Router* router, const Flit* f, int in_channel );

  inline int GetOccupancy() const
  {
    return (int)_buffer.size();
  }

  // ==== Debug functions ====

  void SetWatch( bool watch = true );
  bool IsWatched( ) const;
  void Display( ostream & os = cout ) const;
};

#endif 
