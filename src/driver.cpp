#include <fstream>
#include <iostream>

#include "../includes/image_ppm.hpp"
#include "../includes/seam_carver.hpp"

void print_usage(const std::string& command);

int main(int argc, char* argv[]) {
  std::string out_option = "-o";
  // if (argc < 4 || out_option != argv[argc - 2]) {
  //   print_usage(argv[0]);
  //   return 1;
  // }

  // std::ifstream infile(argv[1]);
  // if (!infile.good()) {
  //   std::cout << "file '" << argv[1] << "' not found" << std::endl;
  //   return 1;
  // }

  // ImagePPM image;
  // infile >> image;
  // infile.close();

  // SeamCarver carver(image);
  // for (int i = 2; i < argc - 2; i += 2) {
  //   std::string times_string = argv[i + 1];
  //   int times = 0;
  //   try {
  //     times = std::stoi(times_string);
  //   } catch (const std::exception& e) {
  //     std::cout << "Malformed option" << std::endl;
  //     print_usage(argv[0]);
  //     return 1;
  //   }

  //   std::string option = argv[i];
  //   if (option == "-h") {
  //     for (int t = 0; t < times; t++) {
  //       carver.remove_horizontal_seam();
  //     }
  //   } else if (option == "-v") {
  //     for (int t = 0; t < times; t++) {
  //       carver.remove_vertical_seam();
  //     }
  //   } else {
  //     std::cout << argv[i] << " not an option" << std::endl;
  //     print_usage(argv[0]);
  //     return 1;
  //   }
  // }

  // std::ofstream outfile(argv[argc - 1]);
  // outfile << carver.get_image();
  // outfile.close();
  // ImagePPM image = ImagePPM("images/image1.ppm");
  // ImagePPM image2 = image;
  // Pixel p = image.get_pixel(2, 3);
  // std::cout << p.get_red() << ", " << p.get_green() << ", " << p.get_blue() << "\n";
  // image.~ImagePPM();


  // Pixel p2 = image2.get_pixel(2, 3);
  // std::cout << p2.get_red() << ", " << p2.get_green() << ", " << p2.get_blue() << "\n";  

  // SeamCarver carver = SeamCarver(image2);
  // std::cout << image2.get_pixel(0, 1).get_red() << ", " << image2.get_pixel(0, 1).get_green() << ", " << image2.get_pixel(0, 1).get_blue() << "\n";
  // std::cout << image2.get_pixel(0, 3).get_red() << ", " << image2.get_pixel(0, 3).get_green() << ", " << image2.get_pixel(0, 3).get_blue() << "\n";
  // std::cout << image2.get_pixel(1, 0).get_red() << ", " << image2.get_pixel(1, 0).get_green() << ", " << image2.get_pixel(1, 0).get_blue() << "\n";
  // std::cout << image2.get_pixel(2, 0).get_red() << ", " << image2.get_pixel(2, 0).get_green() << ", " << image2.get_pixel(2, 0).get_blue() << "\n";
  // return 0;

  std::fstream imageFile = std::fstream("images/image1.ppm");
  ImagePPM image;
  imageFile >> image;
  std::cout << image.get_width() << " , " << image.get_height() << "\n";
  std::cout << "printing imageppm\n";
  std::cout << image;
  return 0;
}

void print_usage(const std::string& command) {
  std::cout << "Usage: " << command << " INPUT_FILE [options] -o OUTPUT_FILE\n"
            << "Options:\n"
            << "\t-h times\tcarve times horizontal seams\n"
            << "\t-v times\tcarve times vertical seams\n";
}