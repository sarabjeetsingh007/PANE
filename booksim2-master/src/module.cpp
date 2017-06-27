// $Id$


/*module.cpp
 *
 *The basic class that is extended by all other components of the network
 *Provides the basic hierarchy structure and basic fuctions
 *
 */

#include <iostream>
#include <cstdlib>

#include "booksim.hpp"
#include "module.hpp"

Module::Module( Module *parent, const string& name )
{
  _name = name;

  if ( parent ) { 
    parent->_AddChild( this );
    _fullname = parent->_fullname + "/" + name;
  } else {
    _fullname = name;
  }
}

void Module::_AddChild( Module *child )
{
  _children.push_back( child );
}

void Module::DisplayHierarchy( int level, ostream & os ) const
{
  vector<Module *>::const_iterator mod_iter;

  for ( int l = 0; l < level; l++ ) {
    os << "  ";  
  }

  os << _name << endl;

  for ( mod_iter = _children.begin( );
	mod_iter != _children.end( ); mod_iter++ ) {
    (*mod_iter)->DisplayHierarchy( level + 1 );
  }
}

void Module::Error( const string& msg ) const
{
  cout << "Error in " << _fullname << " : " << msg << endl;
  exit( -1 );
}

void Module::Debug( const string& msg ) const
{
  cout << "Debug (" << _fullname << ") : " << msg << endl;
}

void Module::Display( ostream & os ) const 
{
  os << "Display method not implemented for " << _fullname << endl;
}
