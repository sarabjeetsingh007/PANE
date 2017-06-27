// $Id$


#ifndef _SYNTHETICTRAFFICMANAGER_HPP_
#define _SYNTHETICTRAFFICMANAGER_HPP_

#include <vector>

#include "trafficmanager.hpp"
#include "traffic.hpp"
#include "stats.hpp"

class SyntheticTrafficManager : public TrafficManager {

private:

  vector<vector<int> > _packet_size;
  vector<vector<int> > _packet_size_rate;
  vector<int> _packet_size_max_val;

protected:

  vector<string> _traffic;
  vector<TrafficPattern *> _traffic_pattern;

  vector<int> _reply_class;
  vector<int> _request_class;

  vector<vector<int> > _qtime;
  vector<vector<bool> > _qdrained;

  vector<Stats *> _tlat_stats;     
  vector<double> _overall_min_tlat;  
  vector<double> _overall_avg_tlat;  
  vector<double> _overall_max_tlat;  

  vector<vector<Stats *> > _pair_tlat;

  virtual void _RetirePacket( Flit * head, Flit * tail );

  virtual int _IssuePacket( int source, int cl ) = 0;

  virtual void _Inject( );

  virtual bool _PacketsOutstanding( ) const;

  virtual void _ResetSim( );

  virtual string _OverallStatsHeaderCSV() const;
  virtual string _OverallClassStatsCSV(int c) const;

  int _GetNextPacketSize(int cl) const;
  double _GetAveragePacketSize(int cl) const;

  SyntheticTrafficManager( const Configuration &config, const vector<Network *> & net );

public:

  virtual ~SyntheticTrafficManager( );

};

#endif
