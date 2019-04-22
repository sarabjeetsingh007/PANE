// $Id$


//////////////////////////////////////////////////////////////////////
//
//  File Name: channel.hpp
//
//  The Channel models a generic channel with a multi-cycle 
//   transmission delay. The channel latency can be specified as 
//   an integer number of simulator cycles.
//
/////
#ifndef _CHANNEL_HPP
#define _CHANNEL_HPP

#include <queue>
#include <cassert>
#include <stdio.h>

#include "globals.hpp"
#include "module.hpp"
#include "timed_module.hpp"

using namespace std;

template<typename T>
class Channel : public TimedModule {
public:
  Channel(Module * parent, string const & name);
  virtual ~Channel() {}

  // Physical Parameters
  void SetLatency(int cycles);
  int GetLatency() const { return _delay ; }
  
  // Send data 
  virtual void Send(T * data);
  
  // Receive data
  virtual T * Receive(); 
  
  virtual void ReadInputs();
  virtual void Evaluate() {}
  virtual void WriteOutputs();
  virtual void CallLeftOverCredits( ){}
protected:
  int _delay;
  T * _input;
  T * _output;
  queue<pair<int, T *> > _wait_queue;

};

template<typename T>
Channel<T>::Channel(Module * parent, string const & name)
  : TimedModule(parent, name), _delay(1), _input(0), _output(0) {
}

template<typename T>
void Channel<T>::SetLatency(int cycles) {
  if(cycles <= 0) {
    Error("Channel must have positive delay.");
  }
  _delay = cycles ;
}

template<typename T>
void Channel<T>::Send(T * data) {
  _input = data;
//if(_input)
//	cout<<_input->id<<" at "<<GetSimTime()<<"s<- From Channel.Send()->2"<<endl;
}

template<typename T>
T * Channel<T>::Receive() {
//	if(_output)
//		cout<<_output->id<<" at "<<GetSimTime()<<"s<- From Channel.Receive()->7"<<endl;
  return _output;
}

template<typename T>
void Channel<T>::ReadInputs() {
  if(_input) {
    _wait_queue.push(make_pair(GetSimTime() + _delay - 1, _input));
//	cout<<_input->id<<" at "<<GetSimTime()<<"s<- From Channel.ReadInputs()->4"<<endl;
    _input = 0;
  }
}

template<typename T>
void Channel<T>::WriteOutputs() {
  _output = 0;
  if(_wait_queue.empty()) {
    return;
  }
  pair<int, T *> const & item = _wait_queue.front();
  int const & time = item.first;
  if(GetSimTime() < time) {
    return;
  }
  assert(GetSimTime() == time);
  _output = item.second;
//	cout<<_output->id<<" at "<<GetSimTime()<<"<- From Channel.WriteOutputs()->6"<<endl;
  assert(_output);
  _wait_queue.pop();
}
#endif
