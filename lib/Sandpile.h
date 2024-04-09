#pragma once

#include "Arguments.h"
#include "Image.h"
#include "Sandpile.h"

#include <vector>
#include <string>

struct SandPile {
  std::vector<std::vector<int64_t>> pile;
  int64_t length;
  int64_t width;
  std::string path;
  void GetSandPile();
  void Topling(int64_t f, std::string out, int64_t max_iter);
};


