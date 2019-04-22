// $Id$


#ifndef _FLIT_HPP_
#define _FLIT_HPP_

#include <iostream>
#include <stack>

#include "booksim.hpp"
#include "outputset.hpp"

class Flit {

public:

  int vc;

  int cl;

  bool head;
  bool tail;
  
  int  ctime;
  int  itime;
  int  atime;

  int  id;
  int  pid;

  bool record;

  int  src;
  int  dest;

  int  pri;

  int  hops;
  bool watch;
  
  int starttime;	//Sarab
//  int hid;		//Sarab (Head ID)
  
  int repeat_change;
  
  // intermediate destination (if any)
  mutable int intm;

  // phase in multi-phase algorithms
  mutable int ph;

  // Fields for arbitrary data
  void* data ;

  // Lookahead route info
  OutputSet la_route_set;

  void Reset();

  static Flit * New();
  void Free();
  static void FreeAll();

private:

  Flit();
  ~Flit() {}

  static stack<Flit *> _all;
  static stack<Flit *> _free;

};

ostream& operator<<( ostream& os, const Flit& f );

#endif
