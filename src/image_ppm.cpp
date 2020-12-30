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
    if (pixels_ != nullptr) {   
        for (int y = 0; y < height_; y++) {
            delete[] pixels_[y];
        }
        delete[] pixels_;
    }

    pixels_ = nullptr;
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

std::istream& operator>>(std::istream& is, ImagePPM& image) {
    std::string line = "";
    std::getline(is, line);
    if (line != "P3") {
        return is;
    }

    std::getline(is, line);
    int index = 0;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ' ') {
            index = i;
            break;
        }
    }
    
    image.width_ = std::stoi(line.substr(0, index));
    image.height_ = std::stoi(line.substr(index + 1));
    std::cout << image.width_ << " , " << image.height_ << "\n";

    // Parse max value line
    std::getline(is, line);
    image.max_color_value_ = std::stoi(line);
    std::cout << "Max color value = " << image.max_color_value_ << "\n";

    //parsing pixels
    image.pixels_ = new Pixel*[image.height_];

    for (int y = 0; y < image.height_; y++) {
        image.pixels_[y] = new Pixel[image.width_];
        for (int x = 0; x < image.width_; x++) {
            std::getline(is, line);
            int r = std::stoi(line);
            std::getline(is, line);
            int g = std::stoi(line);
            std::getline(is, line);
            int b = std::stoi(line);
            // pixels_[x + (width_ * y)];
            image.pixels_[y][x] =  Pixel(r, g, b);
        }
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const ImagePPM& image) {
    os << "P3" << std::endl;
    os << image.height_ << " " << image.width_ << std::endl;
    os << image.get_max_color_value() << std::endl;

    for (int y = 0; y < image.get_height(); y++) {
        for (int x = 0; x < image.get_width(); x++) {
            Pixel p = image.get_pixel(y, x);
            os << p.get_red() << std::endl;
            os << p.get_green() << std::endl;
            os << p.get_blue() << std::endl;
        }
    }
    return os;
}

void ImagePPM::remove_seam(int * path, bool is_vertical) {
    if (path == nullptr || pixels_ == nullptr)
        return;
    if (is_vertical) {
        // Remove vertical path
        Pixel** buffer = new Pixel*[height_];
        for (int y = 0; y < height_; y++) {
            buffer[y] = new Pixel[width_ - 1];
            for (int x = 0; x < width_ - 1; x++) {
                if (x == path[y])
                    continue;
                buffer[y][x] = pixels_[y][x];
            }
        }
        width_--;
        if (pixels_ != nullptr) {   
            for (int y = 0; y < height_; y++) {
                delete[] pixels_[y];
            }
            delete[] pixels_;
        }
        pixels_ = buffer;
    } else {
        Pixel** buffer = new Pixel*[height_ - 1];
        for (int y = 0; y < height_ - 1; y++) {
            buffer[y] = new Pixel[width_];
            for (int x = 0; x < width_; x++) {
                if (y == path[y])
                    continue;
                buffer[y][x] = pixels_[y][x];
            }
        }
        height_--;
        if (pixels_ != nullptr) {   
            for (int y = 0; y < height_; y++) {
                delete[] pixels_[y];
            }
            delete[] pixels_;
        }
        pixels_ = buffer;
    }
}