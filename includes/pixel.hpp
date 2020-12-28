#pragma once

// DO NOT MODIFY
class Pixel {
public:
  Pixel() {
    red_ = -1;
    green_ = -1;
    blue_ = -1;
  }

  Pixel(int r, int g, int b) {
    red_ = r;
    green_ = g;
    blue_ = b;
  }

  int get_red() const { return red_; }

  int get_blue() const { return blue_; }

  int get_green() const { return green_; }

  friend bool operator==(const Pixel& lhs, const Pixel& rhs) {
    return lhs.red_ == rhs.red_ &&
           lhs.green_ == rhs.green_ &&
           lhs.blue_ == rhs.blue_;
  }

private:
  int red_;
  int blue_;
  int green_;
};
