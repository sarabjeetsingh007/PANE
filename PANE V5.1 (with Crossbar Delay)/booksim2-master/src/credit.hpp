// $Id$


#ifndef _CREDIT_HPP_
#define _CREDIT_HPP_

#include <set>
#include <stack>

class Credit {

public:

  set<int> vc;

  // these are only used by the event router
  bool head, tail;
  int  id;

  void Reset();
  
  static Credit * New();
  void Free();
  static void FreeAll();
  static int OutStanding();
private:

  static stack<Credit *> _all;
  static stack<Credit *> _free;

  Credit();
  ~Credit() {}

};

#endif
