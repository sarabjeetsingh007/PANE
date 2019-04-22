// $Id$


#include "random_utils.hpp"
#include <algorithm>
#include <cassert>

extern long ran_x[];
extern double ran_u[];
#define KK 100

void SaveRandomState( std::vector<long> & save_x, std::vector<double> & save_u ) {
  save_x.assign(ran_x, ran_x + KK);
  save_u.assign(ran_u, ran_u + KK);
}

void RestoreRandomState( std::vector<long> const & save_x, std::vector<double> const & save_u) {
  assert(save_x.size() == KK);
  std::copy(save_x.begin(), save_x.end(), ran_x);
  assert(save_u.size() == KK);
  std::copy(save_u.begin(), save_u.end(), ran_u);
}
