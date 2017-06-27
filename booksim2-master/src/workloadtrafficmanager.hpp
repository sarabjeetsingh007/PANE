// $Id$


#ifndef _WORKLOADTRAFFICMANAGER_HPP_
#define _WORKLOADTRAFFICMANAGER_HPP_

#include <iostream>
#include <vector>
#include <list>

#include "trafficmanager.hpp"
#include "workload.hpp"

class WorkloadTrafficManager : public TrafficManager {

protected:

  int _sample_period;
  int _max_samples;
  int _warmup_periods;

  vector<Workload *> _workload;

  int _overall_runtime;
  int source_map_1[64];		//Sneha
  int dest_map_1[64];		//Sneha
  int source_map_5[64];		//Sneha
  int dest_map_5[64];		//Sneha

  virtual void _Inject( );
  virtual void _RetirePacket( Flit * head, Flit * tail );
  virtual void _ResetSim( );
  virtual bool _SingleSim( );

  bool _Completed( );

  virtual void _UpdateOverallStats( );

  virtual string _OverallStatsHeaderCSV() const;
  virtual string _OverallClassStatsCSV(int c) const;

  virtual void _DisplayClassStats(int c, ostream & os) const;
  virtual void _DisplayOverallClassStats(int c, ostream & os) const;

public:

  WorkloadTrafficManager( const Configuration &config, const vector<Network *> & net );
  virtual ~WorkloadTrafficManager( );

};

#endif
