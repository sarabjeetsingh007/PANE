// $Id$


#ifndef _TRAFFIC_HPP_
#define _TRAFFIC_HPP_

#include <vector>
#include <set>
#include "config_utils.hpp"

using namespace std;

class TrafficPattern {
protected:
  int _nodes;
  TrafficPattern(int nodes);
public:
  virtual ~TrafficPattern() {}
  virtual void reset();
  virtual int dest(int source) = 0;
  static TrafficPattern * New(string const & pattern, int nodes, 
			      Configuration const * const config = NULL);
};

class PermutationTrafficPattern : public TrafficPattern {
protected:
  PermutationTrafficPattern(int nodes);
};

class BitPermutationTrafficPattern : public PermutationTrafficPattern {
protected:
  BitPermutationTrafficPattern(int nodes);
};

class BitCompTrafficPattern : public BitPermutationTrafficPattern {
public:
  BitCompTrafficPattern(int nodes);
  virtual int dest(int source);
};

class TransposeTrafficPattern : public BitPermutationTrafficPattern {
protected:
  int _shift;
public:
  TransposeTrafficPattern(int nodes);
  virtual int dest(int source);
};

class BitRevTrafficPattern : public BitPermutationTrafficPattern {
public:
  BitRevTrafficPattern(int nodes);
  virtual int dest(int source);
};

class ShuffleTrafficPattern : public BitPermutationTrafficPattern {
public:
  ShuffleTrafficPattern(int nodes);
  virtual int dest(int source);
};

class DigitPermutationTrafficPattern : public PermutationTrafficPattern {
protected:
  int _k;
  int _n;
  int _xr;
  DigitPermutationTrafficPattern(int nodes, int k, int n, int xr = 1);
};

class TornadoTrafficPattern : public DigitPermutationTrafficPattern {
public:
  TornadoTrafficPattern(int nodes, int k, int n, int xr = 1);
  virtual int dest(int source);
};

class NeighborTrafficPattern : public DigitPermutationTrafficPattern {
public:
  NeighborTrafficPattern(int nodes, int k, int n, int xr = 1);
  virtual int dest(int source);
};

class RandomPermutationTrafficPattern : public TrafficPattern {
private:
  vector<int> _dest;
  inline void randomize(int seed);
public:
  RandomPermutationTrafficPattern(int nodes, int seed);
  virtual int dest(int source);
};

class RandomTrafficPattern : public TrafficPattern {
protected:
  RandomTrafficPattern(int nodes);
};

class UniformRandomTrafficPattern : public RandomTrafficPattern {
public:
  UniformRandomTrafficPattern(int nodes);
  virtual int dest(int source);
};

class UniformBackgroundTrafficPattern : public RandomTrafficPattern {
private:
  set<int> _excluded;
public:
  UniformBackgroundTrafficPattern(int nodes, vector<int> excluded_nodes);
  virtual int dest(int source);
};

class DiagonalTrafficPattern : public RandomTrafficPattern {
public:
  DiagonalTrafficPattern(int nodes);
  virtual int dest(int source);
};

class AsymmetricTrafficPattern : public RandomTrafficPattern {
public:
  AsymmetricTrafficPattern(int nodes);
  virtual int dest(int source);
};

class Taper64TrafficPattern : public RandomTrafficPattern {
public:
  Taper64TrafficPattern(int nodes);
  virtual int dest(int source);
};

class BadPermDFlyTrafficPattern : public DigitPermutationTrafficPattern {
public:
  BadPermDFlyTrafficPattern(int nodes, int k, int n);
  virtual int dest(int source);
};

class BadPermYarcTrafficPattern : public DigitPermutationTrafficPattern {
public:
  BadPermYarcTrafficPattern(int nodes, int k, int n, int xr = 1);
  virtual int dest(int source);
};

class HotSpotTrafficPattern : public TrafficPattern {
private:
  vector<int> _hotspots;
  vector<int> _rates;
  int _max_val;
public:
  HotSpotTrafficPattern(int nodes, vector<int> hotspots, 
			vector<int> rates = vector<int>());
  virtual int dest(int source);
};

#endif
