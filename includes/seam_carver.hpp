#pragma once

#include "image_ppm.hpp"

class SeamCarver {
public:
  // default constructor
  SeamCarver();

  // overloaded constructor. sets the instance's image_ as a DEEP COPY
  // of the image parameter
  SeamCarver(const ImagePPM& image);

  // sets the instance's image_ to be DEEP COPY of the image parameter
  void set_image(const ImagePPM& image);

  // returns the instance's image_
  const ImagePPM& get_image() const;

  // returns the image's height
  int get_height() const;

  // returns the image's width
  int get_width() const;

  // returns the energy of the pixel at row col in image_
  int get_energy(int row, int col) const;

  // returns the horizontal seam of image_ with the least amount of
  // energy
  // 
  // the ith int in the returned array corresponds to which row at
  // col i is in the seam. example:
  //
  //    | x |   |   
  // ---+---+---+---
  //  x |   | x |   
  // ---+---+---+---
  //    |   |   | x
  // returns {1, 0, 1, 2}
  int* get_horizontal_seam() const;

  // returns the vertical seam of image_ with the least amount of
  // energy
  // 
  // the ith int in the returned array corresponds to which col at
  // row i is in the seam. example:
  //
  //    | x |   |   
  // ---+---+---+---
  //    |   | x |   
  // ---+---+---+---
  //    |   | x | 
  // returns {1, 2, 2}
  int* get_vertical_seam() const;

  // removes one horizontal seam in image_. example:
  //
  // image_ before:
  //  0 | 1 | 2 | 3 
  // ---+---+---+---
  //  4 | 5 | 6 | 7  
  // ---+---+---+---
  //  8 | 9 | 10| 11
  //
  // seam to remove:
  //    | x |   |   
  // ---+---+---+---
  //  x |   | x |   
  // ---+---+---+---
  //    |   |   | x
  //
  // image_ after:
  //  0 | 5 | 2 | 3  
  // ---+---+---+---
  //  8 | 9 | 10| 7  
  void remove_horizontal_seam();

  // removes one vertical seam in image_. example:
  //
  // image_ before:
  //  0 | 1 | 2 | 3 
  // ---+---+---+---
  //  4 | 5 | 6 | 7  
  // ---+---+---+---
  //  8 | 9 | 10| 11
  // 
  // seam to remove:
  //    | x |   |   
  // ---+---+---+---
  //    |   | x |   
  // ---+---+---+---
  //    |   | x | 
  //
  // image_ after:
  //  0 | 2 | 3 
  // ---+---+---
  //  4 | 5 | 7
  // ---+---+---
  //  8 | 9 | 11 
  void remove_vertical_seam();

  /**
   * Add any helper methods you may need
   */

private:
  ImagePPM image_;
  
  /**
   * Add any variables you may need
   */

  /**
   * Add any helper methods you may need
   */
};
