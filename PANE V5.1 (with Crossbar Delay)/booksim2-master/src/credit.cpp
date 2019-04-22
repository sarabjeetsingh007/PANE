// $Id$


/*credit.cpp
 *
 *A class for credits
 */

#include "booksim.hpp"
#include "credit.hpp"

stack<Credit *> Credit::_all;
stack<Credit *> Credit::_free;

Credit::Credit()
{
  Reset();
}

void Credit::Reset()
{
  vc.clear();
  head = false;
  tail = false;
  id   = -1;
}

Credit * Credit::New() {
  Credit * c;
  if(_free.empty()) {
    c = new Credit();
    _all.push(c);
  } else {
    c = _free.top();
    c->Reset();
    _free.pop();
  }
  return c;
}

void Credit::Free() {
  _free.push(this);
}

void Credit::FreeAll() {
  while(!_all.empty()) {
    delete _all.top();
    _all.pop();
  }
}


int Credit::OutStanding(){
  return _all.size()-_free.size();
}
