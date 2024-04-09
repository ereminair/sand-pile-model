#include "Image.h"

#include <iostream>
#include <fstream>
#include <cstdint>

Color::Color()
    : r(0), g(0), b(0) {
}

Color::Color(float r, float g, float b)
    : r(256 - r), g(256 - g), b(256 - b) {
}

Image::Image(int64_t width, int64_t height)
    : NewWidth(width), NewHeight(height), Colors(std::vector<Color>(width * height)) {
}

Color Image::GetColor(int64_t x, int64_t y) const {
  return Colors[y * NewWidth + x];
}

void Image::SetColor(const Color& color, int64_t x, int64_t y) {
  Colors[y * NewWidth + x] = color;
}

void Image::SetPile(const std::vector<std::vector<int64_t>> pile) {
  for (int i = 0; i < pile.size(); ++i) {
    for (int j = 0; j < pile[i].size(); ++j) {
      if (pile[i][j] == 0) {
        this->SetColor(kWhite, i, this->NewWidth - j - 1);
      } else if (pile[i][j] == 1) {
        this->SetColor(kGreen, i, this->NewWidth - j - 1);
      } else if (pile[i][j] == 2) {
        this->SetColor(kViolet, i, this->NewWidth - j - 1);
      } else if (pile[i][j] == 3) {
        this->SetColor(kYellow, i, this->NewWidth - j - 1);
      } else if (pile[i][j] > 3) {
        this->SetColor(kBlack, i, this->NewWidth - j - 1);
      }
    }
  }
}

void Image::Export(const std::string& path) const {
  std::ofstream f;
  f.open(path, std::ios::out | std::ios::binary);

  if (!f.is_open()) {
    std::cout << '\n' << "File was not open" << '\n';
    return;
  }

  unsigned char bmpPad[3] = {0, 0, 0};
  const uint32_t kPaddingAmount = (4 - (NewWidth * 3) % 4) % 4;
  const uint32_t kFileHeaderSize = 14;
  const uint32_t kInformationHeaderSize = 40;
  const uint64_t kFileSize = kFileHeaderSize + kInformationHeaderSize + NewWidth * NewHeight * 3 + kPaddingAmount * NewHeight;

  char fileHeader[kFileHeaderSize];

  fileHeader[0] = 'B';
  fileHeader[1] = 'M';
  fileHeader[2] = kFileSize;
  fileHeader[3] = kFileSize >> 8;
  fileHeader[4] = kFileSize >> 16;
  fileHeader[5] = kFileSize >> 24;

  for (int i = 6; i <= 9; ++i) {
    fileHeader[i] = 0;
  }

  fileHeader[10] = kFileHeaderSize + kInformationHeaderSize;

  for (int i = 11; i <= 13; ++i) {
    fileHeader[i] = 0;
  }

  unsigned char informationHeader[kInformationHeaderSize];
  informationHeader[0] = kInformationHeaderSize;

  for (int i = 1; i <= 3; ++i) {
    informationHeader[i] = 0;
  }

  informationHeader[4] = NewWidth;
  informationHeader[5] = NewWidth >> 8;
  informationHeader[6] = NewWidth >> 16;
  informationHeader[7] = NewWidth >> 24;
  informationHeader[8] = NewHeight;
  informationHeader[9] = NewHeight >> 8;
  informationHeader[10] = NewHeight >> 16;
  informationHeader[11] = NewHeight >> 24;
  informationHeader[12] = 1;
  informationHeader[13] = 0;
  informationHeader[14] = 24;
  informationHeader[15] = 0;
  informationHeader[16] = 0;
  informationHeader[17] = 0;
  informationHeader[18] = 0;
  informationHeader[19] = 0;

  for (int i = 20; i <= 39; ++i) {
    informationHeader[i] = 0;
  }

  f.write(reinterpret_cast<char *>(fileHeader), kFileHeaderSize);
  f.write(reinterpret_cast<char *>(informationHeader), kInformationHeaderSize);

  for (int y = 0; y < NewHeight; ++y) {
    for (int x = 0; x < NewWidth; ++x) {
      char r = static_cast<char>(GetColor(x, y).r * 255.0f);
      char g = static_cast<char>(GetColor(x, y).g * 255.0f);
      char b = static_cast<char>(GetColor(x, y).b * 255.0f);
      char color[] = {b, g, r};
      f.write(reinterpret_cast<char *>(color), 3);
    }
    f.write(reinterpret_cast<char *>(bmpPad), kPaddingAmount);
  }
  f.close();
  std::cout << '\n' << "File " << path << " created" << '\n';
}

