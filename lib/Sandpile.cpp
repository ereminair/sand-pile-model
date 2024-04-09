#include "Sandpile.h"
#include "Image.h"

#include <fstream>
#include <string>
#include <vector>

void SandPile::GetSandPile() {
  std::ifstream fin(this->path);
  int64_t temp, step = 0;
  std::vector<uint64_t> x;
  std::vector<uint64_t> y;
  std::vector<uint64_t> key;
  while(fin >> temp) {
    step++;
    if (step == 1) {
      x.push_back(temp);
    }
    else if (step == 2) {
      y.push_back(temp);
    } else if (step == 3) {
      step = 0;
      key.push_back(temp);
    }
  }
  for (int i = 0; i < this->width; ++i) {
    std::vector<int64_t> line(this->length, 0);
    this->pile.push_back(line);
  }
  for (int i = 0; i < x.size(); ++i) {
    this->pile[x[i] - 1][y[i] - 1] = key[i];
  }
}

void SandPile::Topling(int64_t f, const std::string out, int64_t max_iter) {
  int64_t index = 0;
  bool check = false;
  std::vector<std::vector<int64_t>> diff = this->pile;
  while (!check) {
    check = true;
    size_t x1 = 0;
    size_t y1 = 0;
    int64_t w = this->width;
    int64_t l = this->length;
    for (int i = 0; i < l; ++i) {
      for (int j = 0; j < w; ++j) {
        if (this->pile[i + y1][j + x1] >= 4) {
          if (i + y1 == 0) {
            std::vector<int64_t> temp(width, 0);
            this->pile.emplace(this->pile.begin(), temp);
            diff.emplace(diff.begin(), temp);
            this->length++;
            y1++;
          }

          if (i + y1 == this->pile.size() - 1) {
            std::vector<int64_t> temp(this->width, 0);
            this->pile.emplace(this->pile.end(), temp);
            diff.emplace(diff.end(), temp);
            this->length++;
          }

          if (j + x1 == 0) {
            for (int64_t k = 0; k < this->length; ++k) {
              this->pile[k].emplace(this->pile[k].begin(), 0);
              diff[k].emplace(diff[k].begin(), 0);
            }
            this->width++;
            x1++;
          }

          if (j + x1 == this->pile[i].size() - 1) {
            for (int64_t k = 0; k < this->length; ++k) {
              this->pile[k].emplace(this->pile[k].end(), 0);
              diff[k].emplace(diff[k].end(), 0);
            }
            this->width++;
          }

          diff[i + 1 + y1][j + x1] += 1;
          diff[i - 1 + y1][j + x1] += 1;
          diff[i + y1][j + 1 + x1] += 1;
          diff[i + y1][j - 1 + x1] += 1;
          diff[i + y1][j + x1] -= 4;
          check = false;
        }
      }
    }

    for (int i = 0; i < this->length; ++i) {
      for (int j = 0; j < this->width; ++j) {
        this->pile[i][j] += diff[i][j];
        diff[i][j] = 0;
      }
    }

    index++;
    if (index == max_iter) {
      break;
    }

    if (index % f == 0 && f != 0 || check) {
      Image pic(this->width, this->length);
      std::string Out = out;
      pic.SetPile(pile);
      if (out[out.size() - 1] == '/') {
        Out += "out" + std::to_string(index) + ".bmp";
      } else {
        Out += "/out" + std::to_string(index) + ".bmp";
      }
      pic.Export(Out);
    }
  }
}
