// $Id$


#ifndef _BATCHTRAFFICMANAGER_HPP_
#define _BATCHTRAFFICMANAGER_HPP_

#include <iostream>
#include <vector>

#include "synthetictrafficmanager.hpp"

class BatchTrafficManager : public SyntheticTrafficManager {

protected:

  vector<int> _max_outstanding;
  vector<int> _batch_size;
  int _batch_count;
  int _last_id;
  int _last_pid;

  Stats * _batch_time;
  double _overall_min_batch_time;
  double _overall_avg_batch_time;
  double _overall_max_batch_time;

  ostream * _sent_packets_out;

  virtual void _RetireFlit( Flit *f, int dest );

  virtual int _IssuePacket( int source, int cl );
  virtual void _ClearStats( );
  virtual bool _SingleSim( );

  virtual void _UpdateOverallStats( );

  virtual string _OverallStatsHeaderCSV() const;
  virtual string _OverallClassStatsCSV(int c) const;
  virtual void _DisplayOverallClassStats( int c, ostream & os ) const;
  virtual void _DisplayClassStats( int c, ostream & os ) const;
  virtual void _WriteClassStats( int c, ostream & os ) const;


public:

  BatchTrafficManager( const Configuration &config, const vector<Network *> & net );
  virtual ~BatchTrafficManager( );

};

#endif
