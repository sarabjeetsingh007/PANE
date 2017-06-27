// $Id$


#ifndef _STATS_HPP_
#define _STATS_HPP_

#include "module.hpp"

class Stats : public Module {
  int    _num_samples;
  double _sample_sum;
  double _sample_squared_sum;

  //bool _reset;
  double _min;
  double _max;

  int    _num_bins;
  double _bin_size;

  vector<int> _hist;

public:
  Stats( Module *parent, const string &name,
	 double bin_size = 1.0, int num_bins = 10 );

  void Clear( );

  double Average( ) const;
  double Variance( ) const;
  double Max( ) const;
  double Min( ) const;
  double Sum( ) const;
  double SquaredSum( ) const;
  int    NumSamples( ) const;

  void AddSample( double val );
  inline void AddSample( int val ) {
    AddSample( (double)val );
  }

  int GetBin(int b){ return _hist[b];}

  void Display( ostream & os = cout ) const;

  friend ostream & operator<<(ostream & os, const Stats & s);

};

ostream & operator<<(ostream & os, const Stats & s);

#endif
