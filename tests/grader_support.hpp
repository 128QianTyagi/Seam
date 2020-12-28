#ifndef GRADERSUPPORT_H
#define GRADERSUPPORT_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "../includes/image_ppm.hpp"
#include "../includes/pixel.hpp"


namespace sol {

// This is a rewrite of the technique in this article:
// http://bloglitb.blogspot.com/2010/07/access-to-private-members-thats-easy.html

template <class Tag>
struct stowed {
  static typename Tag::type value;
};
template <class Tag>
typename Tag::type stowed<Tag>::value;

// Generate a static data member whose constructor initializes
// stowed<Tag>::value.  This type will only be named in an explicit
// instantiation, where it is legal to pass the address of a private
// member.
//   Node*&  head = dll.*sol::stowed<sol::dll_head>::value;
//   Node*&  tail = dll.*sol::stowed<sol::dll_tail>::value;
//   size_t& size = dll.*sol::stowed<sol::dll_size>::value;

template <class Tag, typename Tag::type x>
class stow_private {
  stow_private() { stowed<Tag>::value = x; }
  static stow_private instance;
};
template <class Tag, typename Tag::type x>
stow_private<Tag, x> stow_private<Tag, x>::instance;

struct image_pixels {
  typedef Pixel**(ImagePPM::*type);
};
template class stow_private<image_pixels, &ImagePPM::pixels_>;


struct image_max_color_value {
  typedef int(ImagePPM::*type);
};
template class stow_private<image_max_color_value, &ImagePPM::max_color_value_>;

struct image_height {
  typedef int(ImagePPM::*type);
};
template class stow_private<image_height, &ImagePPM::height_>;

struct image_width {
  typedef int(ImagePPM::*type);
};
template class stow_private<image_width, &ImagePPM::width_>;





};  // namespace sol

#endif