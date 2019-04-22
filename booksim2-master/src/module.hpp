// $Id$


#ifndef _MODULE_HPP_
#define _MODULE_HPP_

#include "booksim.hpp"

#include <string>
#include <vector>
#include <iostream>

class Module {
private:
  string _name;
  string _fullname;

  vector<Module *> _children;

protected:
  void _AddChild( Module *child );

public:
  Module( Module *parent, const string& name );
  virtual ~Module( ) { }
  
  inline const string & Name() const { return _name; }
  inline const string & FullName() const { return _fullname; }

  void DisplayHierarchy( int level = 0, ostream & os = cout ) const;

  void Error( const string& msg ) const;
  void Debug( const string& msg ) const;

  virtual void Display( ostream & os = cout ) const;
};

#endif
