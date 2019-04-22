// $Id$


#ifndef _GLOBALS_HPP_
#define _GLOBALS_HPP_
#include <string>
#include <vector>
#include <iostream>

/*all declared in main.cpp*/

int GetSimTime();

class Stats;
Stats * GetStats(const std::string & name);

extern bool gPrintActivity;

extern int gK;
extern int gN;
extern int gC;

extern int gNodes;

extern bool gTrace;

extern std::ostream * gWatchOut;

#endif
