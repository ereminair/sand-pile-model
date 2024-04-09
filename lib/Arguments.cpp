#include "Arguments.h"
#include <string.h>

Arguments ArgumentsInput (int size, char* input[]) {
  Arguments result;
  for (int i = 1; i < size - 1; ++i) {
    if (strcmp(input[i], "-i") == 0 || strcmp(input[i], "--input") == 0) {
      result.input = input[i + 1];
    }
    else if (strcmp(input[i], "-o") == 0 || strcmp(input[i], "--output") == 0) {
      result.output = input[i + 1];
    }
    else if (strcmp(input[i], "-m") == 0 || strcmp(input[i], "--max-iter") == 0) {
      result.max_iter = std::stoi(input[i + 1]);
    }
    else if (strcmp(input[i], "-f") == 0 || strcmp(input[i], "--freq") == 0) {
      result.freq = std::stoi(input[i + 1]);
    }
  }

  return result;
}