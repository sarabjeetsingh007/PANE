// $Id$


/*flit.cpp
 *
 *flit struct is a flit, carries all the control signals that a flit needs
 *Add additional signals as necessary. Flits has no concept of length
 *it is a singluar object.
 *
 *When adding objects make sure to set a default value in this constructor
 */

#include "booksim.hpp"
#include "flit.hpp"

stack<Flit *> Flit::_all;
stack<Flit *> Flit::_free;

ostream& operator<<( ostream& os, const Flit& f )
{
  os << "  Flit ID: " << f.id << " (" << &f << ")" 
     << " Packet ID: " << f.pid
     << " Class: " << f.cl 
     << " Head: " << f.head
     << " Tail: " << f.tail << endl;
  os << "  Source: " << f.src << "  Dest: " << f.dest << " Intm: "<<f.intm<<endl;
  os << "  Creation time: " << f.ctime << " Injection time: " << f.itime << " Arrival time: " << f.atime << " Phase: "<<f.ph<< endl;
  os << "  VC: " << f.vc << endl;
  return os;
}

Flit::Flit() 
{  
  Reset();
}  

void Flit::Reset() 
{  
  vc        = -1 ;
  cl        = -1 ;
  head      = false ;
  tail      = false ;
  ctime     = -1 ;
  itime     = -1 ;
  atime     = -1 ;
  id        = -1 ;
  pid       = -1 ;
  hops      = 0 ;
  watch     = false ;
  record    = false ;
  intm = 0;
  src = -1;
  dest = -1;
  pri = 0;
  intm =-1;
  ph = -1;
  data = 0;
  repeat_change = 0;
}  

Flit * Flit::New() {
  Flit * f;
  if(_free.empty()) {
    f = new Flit;
    _all.push(f);
  } else {
    f = _free.top();
    f->Reset();
    _free.pop();
  }
  return f;
}

void Flit::Free() {
  _free.push(this);
}

void Flit::FreeAll() {
  while(!_all.empty()) {
    delete _all.top();
    _all.pop();
  }
}
