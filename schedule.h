#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "structures.h"
#include <vector>


std::vector<std::string> read_exp(Equation eq);

void schedule(Program *p);

#endif

