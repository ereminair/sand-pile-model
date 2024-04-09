#pragma once

#include "Arguments.h"

#include <iostream>
#include <cstdlib>

struct Arguments {
  std::string input;
  std::string output;
  uint64_t max_iter;
  uint64_t freq;
};

Arguments ArgumentsInput (int size, char* input[]);