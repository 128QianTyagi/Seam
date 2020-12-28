//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//                  MP : Seam Carver  : Student Test Cases                  //
//                                                                          //
// Written By :                         Environment :                       //
// Date ......:                         Compiler ...:                       //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up                             //
//////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"
#include "grader_support.hpp"

//////////////////////////////////////////////////////////////////////////////
//                                 Includes                                 //
//////////////////////////////////////////////////////////////////////////////
#include "../includes/image_ppm.hpp"
#include "../includes/pixel.hpp"
#include "../includes/seam_carver.hpp"

//////////////////////////////////////////////////////////////////////////////
//                                Test Cases                                //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

bool pixel_array_equals(const ImagePPM& actual, const ImagePPM& expected) {
  try {
    for (int row = 0; row < expected.get_height(); row ++) {
      for (int col = 0; col < expected.get_width(); col ++) {
        const Pixel& pa = actual.get_pixel(row, col);
        const Pixel& pe = expected.get_pixel(row, col);

        if (pa.get_red() != pe.get_red() || 
            pa.get_green() != pe.get_green() ||
            pa.get_blue() != pa.get_blue()) {
          return false;
        }
      }
    }
  } catch (int e) {
    // most likely from nullptr if actual length and height are not
    // the expected length and height
    return false; 
  }

  return true;
}

bool image_ppm_equal_stream(const ImagePPM& image, std::istream& file) {
  std::string line;

  // skip P3 line
  getline(file, line);

  // evaluate width and height
  getline(file, line);
  int space = line.find_first_of(' ');
  if (std::stoi(line.substr(0, space)) != image.get_width()) {
    return false;
  }

  if (std::stoi(line.substr(space+1)) != image.get_height()) {
    return false;
  }

  // evaluate max color value
  getline(file, line);
  if (std::stoi(line) != image.get_max_color_value()) {
    return false;
  }
  
  // evaluate pixels
  for (int row = 0; row < image.get_height(); row ++) {
    for (int col = 0; col < image.get_width(); col ++) {
      Pixel cur = image.get_pixel(row, col);

      getline(file, line);
      if (line != std::to_string(cur.get_red())) {
        return false;
      }

      getline(file, line);
      if (line != std::to_string(cur.get_green())) {
        return false;
      }

      getline(file, line);
      if (line != std::to_string(cur.get_blue())) {
        return false;
      }
    }
  }

  return true;
}

bool image_ppm_equality(const ImagePPM& a, const ImagePPM& b) {
  if (a.get_width() != b.get_width() || a.get_height() != b.get_height()) {
    return false;
  }

  if (a.get_max_color_value() != b.get_max_color_value()) {
    return false;
  }

  return pixel_array_equals(a, b);
}

const std::string GIVEN_FILE_PATH = "images/image1.ppm";
const std::string SMALL_FILE_PATH = "images/image2.ppm";
const std::string LARGE_FILE_PATH = "images/ocean.ppm";
const std::string ZEROD_FILE_PATH = "images/zerod-image.ppm";

/**
 *  ImagePPM TESTS
 */

TEST_CASE("ImagePPM file path constructor, given file", "[file_path][weight_1]") {
  ImagePPM test_image(GIVEN_FILE_PATH);
  std::ifstream given_file(GIVEN_FILE_PATH);

  REQUIRE(image_ppm_equal_stream(test_image, given_file));
  given_file.close();
}

TEST_CASE("ImagePPM file path constructor, small file", "[file_path][weight_2]") {
  ImagePPM test_image(SMALL_FILE_PATH);
  std::ifstream small_file(SMALL_FILE_PATH);

  REQUIRE(image_ppm_equal_stream(test_image, small_file));
  small_file.close();
}

TEST_CASE("ImagePPM file path constructor, large file", "[file_path][weight_2]") {
  ImagePPM test_image(LARGE_FILE_PATH);
  std::ifstream large_file(LARGE_FILE_PATH);

  REQUIRE(image_ppm_equal_stream(test_image, large_file));
  large_file.close();
}

TEST_CASE("ImagePPM copy constuctor correctness", "[image_copy_ctor][weight_2]") {
  ImagePPM source_image;

  Pixel**& pixels = source_image.*sol::stowed<sol::image_pixels>::value;
  pixels = new Pixel*[1];
  pixels[0] = new Pixel[1];
  pixels[0][0] = Pixel(2, 2, 2);

  int& height = source_image.*sol::stowed<sol::image_height>::value;
  height = 1;

  int& width = source_image.*sol::stowed<sol::image_width>::value;
  width = 1;

  int& max_color_value = source_image.*sol::stowed<sol::image_max_color_value>::value;
  max_color_value = 11;

  ImagePPM test_image(source_image);

  REQUIRE(image_ppm_equality(source_image, test_image));
}

TEST_CASE("ImagePPM copy constructor, deep copy", "[image_copy_ctor][weight_3]") {
  ImagePPM source_image;

  Pixel**& pixels = source_image.*sol::stowed<sol::image_pixels>::value;
  pixels = new Pixel*[1];
  pixels[0] = new Pixel[1];
  pixels[0][0] = Pixel(2, 2, 2);

  int& height = source_image.*sol::stowed<sol::image_height>::value;
  height = 1;

  int& width = source_image.*sol::stowed<sol::image_width>::value;
  width = 1;

  int& max_color_value = source_image.*sol::stowed<sol::image_max_color_value>::value;
  max_color_value = 11;

  ImagePPM test_image(source_image);

  pixels[0][0] = Pixel(5, 5, 5);
  REQUIRE_FALSE(image_ppm_equality(source_image, test_image));
}

TEST_CASE("ImagePPM assignment operator correctness", "[assignment_op][weight_1]") {
  ImagePPM source_image;

  Pixel**& pixels = source_image.*sol::stowed<sol::image_pixels>::value;
  pixels = new Pixel*[1];
  pixels[0] = new Pixel[1];
  pixels[0][0] = Pixel(2, 2, 2);

  int& height = source_image.*sol::stowed<sol::image_height>::value;
  height = 1;

  int& width = source_image.*sol::stowed<sol::image_width>::value;
  width = 1;

  int& max_color_value = source_image.*sol::stowed<sol::image_max_color_value>::value;
  max_color_value = 11;

  ImagePPM test_image = source_image;

  REQUIRE(image_ppm_equality(source_image, test_image));
}

TEST_CASE("ImagePPM assignment operator, deep copy", "[assignment_op][weight_1]") {
  ImagePPM source_image;

  Pixel**& pixels = source_image.*sol::stowed<sol::image_pixels>::value;
  pixels = new Pixel*[1];
  pixels[0] = new Pixel[1];
  pixels[0][0] = Pixel(2, 2, 2);

  int& height = source_image.*sol::stowed<sol::image_height>::value;
  height = 1;

  int& width = source_image.*sol::stowed<sol::image_width>::value;
  width = 1;

  int& max_color_value = source_image.*sol::stowed<sol::image_max_color_value>::value;
  max_color_value = 11;

  ImagePPM test_image = source_image;

  pixels[0][0] = Pixel(5, 5, 5);
  REQUIRE_FALSE(image_ppm_equality(source_image, test_image));
}

/*
TEST_CASE("ImagePPM assignment operator, memory management", "[assignment_op][memory_management][weight_3]") {

}

TEST_CASE("ImagePPM destructor, empty image", "[image_destructor][memory_management][weight_1]") {

}

TEST_CASE("ImagePPM destructor, non-empty image", "[image_destructor][memory_management][weight_4]") {

}
*/

TEST_CASE("ImagePPM output operator, given file", "[output_op][weight_1]") {
  ImagePPM test_image(GIVEN_FILE_PATH);

  std::stringstream output;
  output << test_image;
  output.seekg(0);

  REQUIRE(image_ppm_equal_stream(test_image, output));
}

TEST_CASE("ImagePPM output operator, small file", "[output_op][weight_2]") {
  ImagePPM test_image(SMALL_FILE_PATH);

  std::stringstream output;
  output << test_image;
  output.seekg(0);

  REQUIRE(image_ppm_equal_stream(test_image, output));
}

TEST_CASE("ImagePPM output operator, large file", "[output_op][weight_2]") {
  ImagePPM test_image(LARGE_FILE_PATH);

  std::stringstream output;
  output << test_image;
  output.seekg(0);

  REQUIRE(image_ppm_equal_stream(test_image, output));
}

TEST_CASE("ImagePPM input operator, given file", "[input_op][weight_1]") {
  std::ifstream given_file(GIVEN_FILE_PATH);
  
  ImagePPM test_image;
  given_file >> test_image;
  given_file.seekg(0);

  REQUIRE(image_ppm_equal_stream(test_image, given_file));
  given_file.close();
}

TEST_CASE("ImagePPM input operator, small file", "[input_op][weight_1]") {
  std::ifstream small_file(SMALL_FILE_PATH);
  
  ImagePPM test_image;
  small_file >> test_image;
  small_file.seekg(0);

  REQUIRE(image_ppm_equal_stream(test_image, small_file));
  small_file.close();
}

/*
TEST_CASE("ImagePPM input operator memory management, non-empty image", "[input_op][memory_management][weight_3]") {
  
}
*/

/**
 *  SeamCarver TESTS
 */ 

TEST_CASE("SeamCarver overloaded constructor correctness, empty image", "[seam_carver_ctor][weight_1]") {
  ImagePPM image;
  SeamCarver test_carver(image);

  REQUIRE(image_ppm_equality(image, test_carver.get_image()));
}

TEST_CASE("SeamCarver overloaded constructor correctness, non-empty image", "[seam_carver_ctor][weight_2]") {
  ImagePPM image(SMALL_FILE_PATH);
  SeamCarver test_carver(image);

  REQUIRE(image_ppm_equality(image, test_carver.get_image()));
}

TEST_CASE("SeamCarver overloaded constructor, image deep copy", "[seam_carver_ctor][weight_2]") {
  ImagePPM image(SMALL_FILE_PATH);
  SeamCarver test_carver(image);

  Pixel** pixels = image.*sol::stowed<sol::image_pixels>::value;
  pixels[0][0] = Pixel(1, 2, 3);

  REQUIRE_FALSE(image_ppm_equality(image, test_carver.get_image()));
}

TEST_CASE("SeamCarver set image correctness", "[set_image][weight_1]") {
  ImagePPM image(SMALL_FILE_PATH);
  SeamCarver test_carver;
  test_carver.set_image(image);

  REQUIRE(image_ppm_equality(image, test_carver.get_image()));
}

TEST_CASE("SeamCarver set image, deep copy", "[set_image][weight_1]") {
  ImagePPM image(SMALL_FILE_PATH);
  SeamCarver test_carver;
  test_carver.set_image(image);

  Pixel** pixels = image.*sol::stowed<sol::image_pixels>::value;
  pixels[0][0] = Pixel(1, 2, 3);

  REQUIRE_FALSE(image_ppm_equality(image, test_carver.get_image()));
}

/*
TEST_CASE("SeamCarver set image memory management", "[set_image][memory_management][weight_3]") {

}
*/

TEST_CASE("SeamCarver get energy, given image", "[get_energy][weight_2]") {
  // all these were calculated by hand
  int expected_energies[3][4] = {{75, 525, 525, 450},
                               {0,0,0,0},
                               {75, 525, 525, 450}};

  ImagePPM image(GIVEN_FILE_PATH);
  SeamCarver test_carver(image);

  for (int row = 0; row < 3; row ++) {
    for (int col = 0; col < 4; col ++) {
      REQUIRE(expected_energies[row][col] == test_carver.get_energy(row, col));
    }
  }
}

TEST_CASE("SeamCarver get energy, small image", "[get_energy][weight_8]") {
  // all these were calculated by hand
  int expected_energies[4][4] = {{2500, 26850, 2550, 2550},
                                 {30000, 0, 5000, 11300},
                                 {4800, 31850, 4850, 7550},
                                 {54300, 50, 29300, 11350}};

  ImagePPM image(SMALL_FILE_PATH);
  SeamCarver test_carver(image);

  for (int row = 0; row < 4; row ++) {
    for (int col = 0; col < 4; col ++) {
      REQUIRE(expected_energies[row][col] == test_carver.get_energy(row, col));
    }
  }
}

TEST_CASE("SeamCarver find seam doesn't modify image", "[find_seam][weight_2]") {
  ImagePPM image(SMALL_FILE_PATH);
  SeamCarver test_carver(image);

  int* seam = test_carver.get_horizontal_seam();
  delete[] seam;
  seam = nullptr;

  seam = test_carver.get_vertical_seam();
  delete[] seam;
  seam = nullptr;

  std::ifstream file(SMALL_FILE_PATH);
  REQUIRE(image_ppm_equal_stream(test_carver.get_image(), file));
  file.close();
}

TEST_CASE("SeamCarver find h. seam, zerod image", "[find_seam][weight_1]") {
  ImagePPM image(ZEROD_FILE_PATH);
  SeamCarver test_carver(image);

  std::unique_ptr<int[]> seam(test_carver.get_horizontal_seam());
  REQUIRE(seam[0] == 0);
  REQUIRE(seam[1] == 0);
  REQUIRE(seam[2] == 0);
  
}

TEST_CASE("SeamCarver find v. seam, zerod image", "[find_seam][weight_1]") {
  ImagePPM image(ZEROD_FILE_PATH);
  SeamCarver test_carver(image);

  std::unique_ptr<int[]> seam(test_carver.get_vertical_seam());
  REQUIRE(seam[0] == 0);
  REQUIRE(seam[1] == 0);
  REQUIRE(seam[2] == 0);
}

TEST_CASE("SeamCarver find h. seam, given image", "[find_seam][weight_1]") {
  ImagePPM image(GIVEN_FILE_PATH);
  SeamCarver test_carver(image);

  /**
   *  Energies for image 1: 
   *  75  525 525 450
   *  0   0   0   0
   *  75  525 525 450
   */
  std::unique_ptr<int[]> seam(test_carver.get_horizontal_seam());
  for (int i = 0; i < test_carver.get_width(); i ++) {
    REQUIRE(seam[i] == 1);
  }
}

TEST_CASE("SeamCarver find v. seam, given image", "[find_seam][weight_1]") {
  ImagePPM image(GIVEN_FILE_PATH);
  SeamCarver test_carver(image);

  /**
   *  Energies for image 1: 
   *  75  525 525 450
   *  0   0   0   0
   *  75  525 525 450
   */
  std::unique_ptr<int[]> seam(test_carver.get_vertical_seam());
  for (int i = 0; i < test_carver.get_height(); i ++) {
    REQUIRE(seam[i] == 0);
  }
}

TEST_CASE("SeamCarver find h. seam, small image", "[find_seam][weight_2]") {
  ImagePPM image(SMALL_FILE_PATH);
  SeamCarver test_carver(image);

  /**
   *  Energies for image 2:
   *  2500  26850 2550  2550
   *  30000 0     5000  11300
   *  4800  31850 4850  7550
   *  54300 50    29300 11350
   */
  std::unique_ptr<int[]> seam(test_carver.get_horizontal_seam());
  REQUIRE(seam[0] == 0);
  REQUIRE(seam[1] == 1);
  REQUIRE(seam[2] == 0);
  REQUIRE(seam[3] == 0);
}

TEST_CASE("SeamCarver find v. seam, small image", "[find_seam][weight_2]") {
  ImagePPM image(SMALL_FILE_PATH);
  SeamCarver test_carver(image);

  /**
   *  Energies for image 2:
   *  2500  26850 2550  2550
   *  30000 0     5000  11300
   *  4800  31850 4850  7550
   *  54300 50    29300 11350
   */
  std::unique_ptr<int[]> seam(test_carver.get_vertical_seam());
  for (int i = 0; i < test_carver.get_height(); i ++) {
    REQUIRE(seam[i] == i % 2);
  }
}

TEST_CASE("SeamCarver find h. seam after v. carve, given image", "[find_seam][weight_1]") {
  ImagePPM image(GIVEN_FILE_PATH);
  SeamCarver test_carver(image);

  test_carver.remove_vertical_seam();
  std::unique_ptr<int[]> seam(test_carver.get_horizontal_seam());

  /**
   * carved image energies:
   *  300 525 150
   *  225 0   225
   *  300 525 150
   */
  REQUIRE(seam[0] == 1);
  REQUIRE(seam[1] == 1);
  REQUIRE(seam[2] == 0);
}

TEST_CASE("SeamCarver find v. seam after v. carve, given image", "[find_seam][weight_1]") {
  ImagePPM image(GIVEN_FILE_PATH);
  SeamCarver test_carver(image);

  test_carver.remove_vertical_seam();
  std::unique_ptr<int[]> seam(test_carver.get_vertical_seam());

  /**
   * carved image energies:
   *  300 525 150
   *  225 0   225
   *  300 525 150
   */
  REQUIRE(seam[0] == 2);
  REQUIRE(seam[1] == 1);
  REQUIRE(seam[2] == 2);
}

TEST_CASE("SeamCarver find seams after h. carve, small image", "[find_seam][weight_2]") {
  ImagePPM image(SMALL_FILE_PATH);
  SeamCarver test_carver(image);

  test_carver.remove_horizontal_seam();
  /**
   * carved image energies:
   *  5200  7500  9650  0
   *  4800  15000 4850  7550
   *  24350 50    29150 100
   */

  std::unique_ptr<int[]> horizontal_seam(test_carver.get_horizontal_seam());
  REQUIRE(horizontal_seam[0] == 1);
  REQUIRE(horizontal_seam[1] == 2);
  REQUIRE(horizontal_seam[2] == 1);
  REQUIRE(horizontal_seam[3] == 0);

  std::unique_ptr<int[]> vertical_seam(test_carver.get_vertical_seam());
  REQUIRE(vertical_seam[0] == 3);
  REQUIRE(vertical_seam[1] == 2);
  REQUIRE(vertical_seam[2] == 1);
}

TEST_CASE("SeamCarver find seams after v. carve, small image", "[find_seam][weight_2]") {
  ImagePPM image(SMALL_FILE_PATH);
  SeamCarver test_carver(image);

  test_carver.remove_vertical_seam();
  /**
   * carved image energies:
   *  7500 2550 5050
   *  0    5000 11300
   *  4800 4850 50
   *  0    5050 11350
   */
  
  std::unique_ptr<int[]> horizontal_seam(test_carver.get_horizontal_seam());
  REQUIRE(horizontal_seam[0] == 1);
  REQUIRE(horizontal_seam[1] == 2);
  REQUIRE(horizontal_seam[2] == 2);

  std::unique_ptr<int[]> vertical_seam(test_carver.get_vertical_seam());
  REQUIRE(vertical_seam[0] == 1);
  REQUIRE(vertical_seam[1] == 0);
  REQUIRE(vertical_seam[2] == 0);
  REQUIRE(vertical_seam[3] == 0);
}

/*
TEST_CASE("SeamCarve carve seam memory management", "[carve_seam][memory_management][weight_2]") {
  
}
*/

TEST_CASE("SeamCarver carve h. seam, given image", "[carve_seam][weight_2]") {
  ImagePPM image(GIVEN_FILE_PATH);
  SeamCarver test_carver(image);

  test_carver.remove_horizontal_seam();

  std::ifstream expected_file("images/image1-h1.ppm");
  REQUIRE(image_ppm_equal_stream(test_carver.get_image(), expected_file));
  expected_file.close();
}

TEST_CASE("SeamCarver carve v. seam, given image", "[carve_seam][weight_2]") {
  ImagePPM image(GIVEN_FILE_PATH);
  SeamCarver test_carver(image);

  test_carver.remove_vertical_seam();

  std::ifstream expected_file("images/image1-v1.ppm");
  REQUIRE(image_ppm_equal_stream(test_carver.get_image(), expected_file));
  expected_file.close();
}

TEST_CASE("SeamCarver carve h. seam, small image", "[carve_seam][weight_3]") {
  ImagePPM image(SMALL_FILE_PATH);
  SeamCarver test_carver(image);

  test_carver.remove_horizontal_seam();

  std::ifstream expected_file("images/image2-h1.ppm");
  REQUIRE(image_ppm_equal_stream(test_carver.get_image(), expected_file));
  expected_file.close();
}

TEST_CASE("SeamCarver carve v. seam, small image", "[carve_seam][weight_3]") {
  ImagePPM image(SMALL_FILE_PATH);
  SeamCarver test_carver(image);

  test_carver.remove_vertical_seam();

  std::ifstream expected_file("images/image2-v1.ppm");
  REQUIRE(image_ppm_equal_stream(test_carver.get_image(), expected_file));
  expected_file.close();
}

TEST_CASE("SeamCarver carve h. seam, large image", "[carve_seam][weight_3]") {
  ImagePPM image(LARGE_FILE_PATH);
  SeamCarver test_carver(image);

  test_carver.remove_horizontal_seam();

  std::ifstream expected_file("images/ocean-h1.ppm");
  REQUIRE(image_ppm_equal_stream(test_carver.get_image(), expected_file));
  expected_file.close();
}

TEST_CASE("SeamCarver carve v. seam, large image", "[carve_seam][weight_3]") {
  ImagePPM image(LARGE_FILE_PATH);
  SeamCarver test_carver(image);

  test_carver.remove_vertical_seam();

  std::ifstream expected_file("images/ocean-v1.ppm");
  REQUIRE(image_ppm_equal_stream(test_carver.get_image(), expected_file));
  expected_file.close();
}

TEST_CASE("SeamCarver carve successive seams, small image", "[carve_seam][weight_4]") {
  ImagePPM image(SMALL_FILE_PATH);
  SeamCarver test_carver(image);

  test_carver.remove_vertical_seam();
  test_carver.remove_horizontal_seam();

  std::ifstream expected_file("images/image2-v1h1.ppm");
  REQUIRE(image_ppm_equal_stream(test_carver.get_image(), expected_file));
  expected_file.close();
}

TEST_CASE("SeamCarver carve successive seams, large image", "[carve_seam][weight_4]") {
  ImagePPM image(LARGE_FILE_PATH);
  SeamCarver test_carver(image);

  test_carver.remove_vertical_seam();
  test_carver.remove_horizontal_seam();

  std::ifstream expected_file("images/ocean-v1h1.ppm");
  REQUIRE(image_ppm_equal_stream(test_carver.get_image(), expected_file));
  expected_file.close();
}

TEST_CASE("SeamCarver carve lots of seams, large image", "[seam_carver][weight_8]") {
  ImagePPM image(LARGE_FILE_PATH);
  SeamCarver test_carver(image);

  // ./seam_carver images/ocean.ppm -h 5 -v 2 -h 10 -v 20 -o images/ocean-mult.ppm

  for (int i = 0; i < 5; i ++) {
    test_carver.remove_horizontal_seam();
  }

  test_carver.remove_vertical_seam();
  test_carver.remove_vertical_seam();

  for (int i = 0; i < 10; i ++) {
    test_carver.remove_horizontal_seam();
  }

  for (int i = 0; i < 20; i ++) {
    test_carver.remove_vertical_seam();
  }

  std::ifstream expected_file("images/ocean-mult.ppm");
  REQUIRE(image_ppm_equal_stream(test_carver.get_image(), expected_file));
  expected_file.close();
}