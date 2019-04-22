// $Id$


#ifndef _TIMED_MODULE_HPP_
#define _TIMED_MODULE_HPP_

#include "module.hpp"

class TimedModule : public Module {

public:
  TimedModule(Module * parent, string const & name) : Module(parent, name) {}
  virtual ~TimedModule() {}
  
  virtual void ReadInputs() = 0;
  virtual void Evaluate() = 0;
  virtual void WriteOutputs() = 0;
  virtual void CallLeftOverCredits( ) = 0; 	//*Sarab
};

#endif
