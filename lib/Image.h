#pragma once

#include <string>
#include <vector>
#include <cstdint>

struct Color {
  float r, g, b;
  Color();
  Color(float r, float g, float b);
};

struct Image {
  Image(int64_t width, int64_t height);
  Color GetColor(int64_t x, int64_t y) const;
  void SetColor(const Color& color, int64_t x, int64_t y);
  void Export(const std::string& path) const;
  void SetWidthAndHeight(int64_t width, int64_t height);
  int64_t NewWidth;
  int64_t NewHeight;
  std::vector<Color> Colors;
  void SetPile(std::vector<std::vector<int64_t>> pile);
};

static const Color kWhite(255, 255, 255);
static const Color kGreen(0, 255, 0);
static const Color kViolet(105, 0, 198);
static const Color kYellow(255, 255, 0);
static const Color kBlack(0, 0, 0);

