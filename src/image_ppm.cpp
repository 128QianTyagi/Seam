#include "../includes/image_ppm.hpp"

ImagePPM::ImagePPM() {

}

ImagePPM::ImagePPM(const std::string& path) {
    std::fstream file = std::fstream(path);
    std::string line = "";
    std::getline(file, line);
    if (line != "P3") {
        file.close();
        return;
    }

    std::getline(file, line);
    int index = 0;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ' ') {
            index = i;
            break;
        }
    }
    width_ = std::stoi(line.substr(0, index));
    height_ = std::stoi(line.substr(index + 1));
    std::cout << width_ << " , " << height_ << "\n";

    // Parse max value line
    std::getline(file, line);
    max_color_value_ = std::stoi(line);
    std::cout << "Max color value = " << max_color_value_ << "\n";

    //parsing pixels
    pixels_ = new Pixel*[height_];

    for (int y = 0; y < height_; y++) {
        pixels_[y] = new Pixel[width_];
        for (int x = 0; x < width_; x++) {
            std::getline(file, line);
            int r = std::stoi(line);
            std::getline(file, line);
            int g = std::stoi(line);
            std::getline(file, line);
            int b = std::stoi(line);
            // pixels_[x + (width_ * y)];
            pixels_[y][x] =  Pixel(r, g, b);
        }
    }
    file.close();
}

ImagePPM::ImagePPM(const ImagePPM& source) {
    width_ = source.width_;
    height_ = source.height_;
    max_color_value_ = source.max_color_value_;

    pixels_ = new Pixel*[height_];

    for (int y = 0; y < height_; y++) {
        pixels_[y] = new Pixel[width_];
        for (int x = 0; x < width_; x++) {
            pixels_[y][x] = source.get_pixel(y, x);
        }
    }    
}

ImagePPM& ImagePPM::operator=( const ImagePPM& source ) {
    if (this == &source) {
        return *this;
    }

    width_ = source.width_;
    height_ = source.height_;
    max_color_value_ = source.max_color_value_;

    pixels_ = new Pixel*[height_];

    for (int y = 0; y < height_; y++) {
        pixels_[y] = new Pixel[width_];
        for (int x = 0; x < width_; x++) {
            pixels_[y][x] = source.get_pixel(y, x);
        }
    }
}

ImagePPM::~ImagePPM() {
    if (pixels_ != nullptr) {   
        for (int y = 0; y < height_; y++) {
            delete[] pixels_[y];
        }
        delete[] pixels_;
    }
    pixels_ = nullptr;
}

Pixel ImagePPM::get_pixel(int row, int col) const {
    return pixels_[row][col];
}

int ImagePPM::get_width() const {
    return width_;
}

int ImagePPM::get_height() const {
    return height_;
}

int ImagePPM::get_max_color_value() const {
    return max_color_value_;
}