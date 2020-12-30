#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "pixel.hpp"

class ImagePPM {
public:
  // default constructor
  ImagePPM();

  // constructor that initializes the instance from a file at path
  ImagePPM( const std::string& path );

  // copy constructor. Should intialize the instance as DEEP COPY of source
  ImagePPM( const ImagePPM& source );

  // assignment operator. Should set the instance to be a DEEP COPY of
  // source
  ImagePPM &operator=( const ImagePPM& source );

  // destructor. releases all heap memory used by the instance
  ~ImagePPM();

  // returns the Pixel at row col
  Pixel get_pixel(int row, int col) const;

  // returns the width of the image
  int get_width() const;

  // returns the height of the image
  int get_height() const;

  // returns the max color value of the image
  int get_max_color_value() const;

  // outputs the image in plain PPM format
  friend std::ostream &operator<<( std::ostream& os, const ImagePPM& image );

  // fills in image using the stream. the stream contains an image in plain
  // PPM format
  friend std::istream &operator>>( std::istream& is, ImagePPM& image );

  /**
   * Add any helper methods you may need
   */
  void remove_seam(int * path, bool is_vertical);
  

private:
  int height_;
  int width_;
  int max_color_value_;
  Pixel** pixels_;

  /**
   * Add any variables you may need
   */

  /**
   * Add any helper methods you may need
   */
};


