// $Id$


#ifndef _RANDOM_UTILS_HPP_
#define _RANDOM_UTILS_HPP_

#include <vector>

// interface to Knuth's RANARRAY RNG
void   ran_start(long seed);
long   ran_next( );
void   ranf_start(long seed);
double ranf_next( );

inline void RandomSeed( long seed ) {
  ran_start( seed );
  ranf_start( seed );
}

inline unsigned long RandomIntLong( ) {
  return ran_next( );
}

// Returns a random integer in the range [0,max]
inline int RandomInt( int max ) {
  return ( ran_next( ) % (max+1) );
}

// Returns a random floating-point value in the rage [0,1]
inline double RandomFloat(  ) {
  return ranf_next( );
}

// Returns a random floating-point value in the rage [0,max]
inline double RandomFloat( double max ) {
  return ( ranf_next( ) * max );
}

// Saves the current generator state
void SaveRandomState( std::vector<long> & save_x, std::vector<double> & save_u );

// Restores the generator state from previously saved values
void RestoreRandomState( std::vector<long> const & save_x, std::vector<double> const & save_u );

#endif
