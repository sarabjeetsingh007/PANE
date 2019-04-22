// $Id$


#include <sstream>

#include "globals.hpp"
#include "booksim.hpp"
#include "buffer.hpp"

Buffer::Buffer( const Configuration& config, int outputs, Module *parent, const string& name ) :
Module( parent, name ), _occupancy(0)
{
  int num_vcs = config.GetInt( "num_vcs" );

  _size = config.GetInt("buf_size");
  if(_size < 0) {
    _size = num_vcs * config.GetInt( "vc_buf_size" );
  };

  _vc.resize(num_vcs);

  for(int i = 0; i < num_vcs; ++i)
  {
    ostringstream vc_name;
    vc_name << "vc_" << i;
    _vc[i] = new VC(config, outputs, this, vc_name.str( ) );
  }

#ifdef TRACK_BUFFERS
  int classes = config.GetInt("classes");
  _class_occupancy.resize(classes, 0);
#endif
}

Buffer::~Buffer()
{
  for(vector<VC*>::iterator i = _vc.begin(); i != _vc.end(); ++i) {
    delete *i;
  }
}

void Buffer::AddFlit( int vc, Flit *f )
{
  if(_occupancy >= _size) {
    Error("Flit buffer overflow.");
  }
  ++_occupancy;
//	cout<<"AddFlit_VC"<<vc<<"_ID"<<f->id<<"("<<_occupancy<<","<<_size<<")\n";
  _vc[vc]->AddFlit(f);
#ifdef TRACK_BUFFERS
  ++_class_occupancy[f->cl];
#endif
}

void Buffer::Display( ostream & os ) const
{
  for(vector<VC*>::const_iterator i = _vc.begin(); i != _vc.end(); ++i) {
    (*i)->Display(os);
  }
}
