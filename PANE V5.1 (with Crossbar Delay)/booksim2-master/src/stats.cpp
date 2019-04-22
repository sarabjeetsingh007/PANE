// $Id$


/*stats.cpp
 *
 *class stores statistics gnerated by the trafficmanager such as the latency
 *hope count of the the flits
 *
 *reset option resets the min and max alues of this statistiscs
 */

#include "booksim.hpp"
#include <iostream>
#include <sstream>
#include <limits>
#include <cmath>
#include <cstdio>

#include "stats.hpp"

Stats::Stats( Module *parent, const string &name,
	      double bin_size, int num_bins ) :
  Module( parent, name ), _num_bins( num_bins ), _bin_size( bin_size )
{
  Clear();
}

void Stats::Clear( )
{
  _num_samples = 0;
  _sample_sum  = 0.0;
  _sample_squared_sum = 0.0;

  _hist.assign(_num_bins, 0);

  _min = numeric_limits<double>::quiet_NaN();
  _max = -numeric_limits<double>::quiet_NaN();
  
  //  _reset = true;
}

double Stats::Average( ) const
{
  return _sample_sum / (double)_num_samples;
}

double Stats::Variance( ) const
{
  return (_sample_squared_sum * (double)_num_samples - _sample_sum * _sample_sum) / ((double)_num_samples * (double)_num_samples);
}

double Stats::Min( ) const
{
  return _min;
}

double Stats::Max( ) const
{
  return _max;
}

double Stats::Sum( ) const
{
  return _sample_sum;
}

double Stats::SquaredSum( ) const
{
  return _sample_squared_sum;
}

int Stats::NumSamples( ) const
{
  return _num_samples;
}

void Stats::AddSample( double val )
{
  ++_num_samples;
  _sample_sum += val;

  // NOTE: the negation ensures that NaN values are handled correctly!
  _max = !(val <= _max) ? val : _max;
  _min = !(val >= _min) ? val : _min;

  //double clamp between 0 and num_bins-1
  int b = (int)fmax(floor( val / _bin_size ), 0.0);
  b = (b >= _num_bins) ? (_num_bins - 1) : b;

  _hist[b]++;
}

void Stats::Display( ostream & os ) const
{
  os << *this << endl;
}

ostream & operator<<(ostream & os, const Stats & s) {
  vector<int> const & v = s._hist;
  os << "[ ";
  for(size_t i = 0; i < v.size(); ++i) {
    os << v[i] << " ";
  }
  os << "]";
  return os;
}
