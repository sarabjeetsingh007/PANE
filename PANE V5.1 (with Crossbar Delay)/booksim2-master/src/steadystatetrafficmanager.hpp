// $Id$


#ifndef _STEADYSTATETRAFFICMANAGER_HPP_
#define _STEADYSTATETRAFFICMANAGER_HPP_

#include <vector>

#include "synthetictrafficmanager.hpp"
#include "injection.hpp"

class SteadyStateTrafficManager : public SyntheticTrafficManager {

protected:

  vector<double> _load;

  vector<string> _injection;
  vector<InjectionProcess *> _injection_process;

  bool _measure_latency;

  int   _sample_period;
  int   _max_samples;
  int   _warmup_periods;

  vector<double> _latency_thres;

  vector<double> _stopping_threshold;
  vector<double> _acc_stopping_threshold;

  vector<double> _warmup_threshold;
  vector<double> _acc_warmup_threshold;

  virtual int _IssuePacket( int source, int cl );

  virtual void _ResetSim( );

  virtual bool _SingleSim( );

  virtual string _OverallStatsHeaderCSV() const;
  virtual string _OverallClassStatsCSV(int c) const;

public:

  SteadyStateTrafficManager( const Configuration &config, const vector<Network *> & net );
  virtual ~SteadyStateTrafficManager( );

};

#endif
