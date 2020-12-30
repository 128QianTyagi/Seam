#include "../includes/seam_carver.hpp"

SeamCarver::SeamCarver() {
    energyMap = std::unordered_map<std::pair<int, int>, int, pair_hash>();
}

SeamCarver::SeamCarver(const ImagePPM& image) : image_(image) {
    energyMap = std::unordered_map<std::pair<int, int>, int, pair_hash>();
    std::vector<std::vector<int>> result = compute_vertical_energies();
}

void SeamCarver::set_image(const ImagePPM& image) {
    image_ = image;
}

const ImagePPM& SeamCarver::get_image() const {
    return image_;
}

int SeamCarver::get_width() const {
    return image_.get_width();
}

int SeamCarver::get_height() const {
    return image_.get_height();
}

int SeamCarver::get_energy(int row, int col) const {
    Pixel left, right, up , down;

    if (row == 0) {
        up = image_.get_pixel(image_.get_height()-1, col);
    } else {
        up = image_.get_pixel(row-1, col);
    }

    if (row == image_.get_height() - 1) {
        down = image_.get_pixel(0, col);
    } else {
        down = image_.get_pixel(row+1, col);
    }

    if (col == 0) {
        left = image_.get_pixel(row, image_.get_width()-1);
    } else {
        left = image_.get_pixel(row, col-1);
    }

    if (col == image_.get_width() - 1) {
        right = image_.get_pixel(row, 0);
    } else {
        right = image_.get_pixel(row, col+1);
    }

    int energy = 0;
    energy += (left.get_red() - right.get_red()) * (left.get_red() - right.get_red());
    energy += (left.get_green() - right.get_green()) * (left.get_green() - right.get_green());
    energy += (left.get_blue() - right.get_blue()) * (left.get_blue() - right.get_blue());

    energy += (up.get_red() - down.get_red()) * (up.get_red() - down.get_red());
    energy += (up.get_green() - down.get_green()) * (up.get_green() - down.get_green());
    energy += (up.get_blue() - down.get_blue()) * (up.get_blue() - down.get_blue());

    return energy;
}



int SeamCarver::findMinPath(int row, int col) {
    if (row == image_.get_height() - 1) {
        int result = get_energy(row, col);
        // energyMap[{row, col}] = result;
        return result;
    }

    if (energyMap.find({row, col}) != energyMap.end()) {
        return energyMap[{row, col}];
    }

    int left = findMinPath(row + 1, col - 1);
    int down = findMinPath(row + 1, col);
    int right = findMinPath(row + 1, col + 1);

    // int best = get_energy(row, col) + std::min(left, down, right);
    // energyMap[{row, col}] = best;
    return 0;
}

int* SeamCarver::get_vertical_seam() const {
    std::vector<std::vector<int>> energies = compute_vertical_energies();
    int * path = new int[get_height()];

    int startingValue = energies[0][0];
    int currentColumn = 0;

    for (int col = 1; col < get_width(); col++) {
        if (energies[0][col] < startingValue) {
            startingValue = energies[0][col];
            currentColumn = col;
        }
    }    

    path[0] = currentColumn;

    for (int i = 0; i < get_height() - 1; i++) {
        startingValue = energies[i + 1][path[i]];
        currentColumn = path[i];

        if (path[i] < get_width() - 1) {
            int right = energies[i + 1][path[i] + 1];
            if (right < startingValue) {
                startingValue = right;
                currentColumn = path[i] + 1;
            }
        }

        if (path[i] > 0) {
            int left = energies[i + 1][path[i] - 1];
            if (left < startingValue) {
                startingValue = left;
                currentColumn = path[i] - 1;
            }
        }

        path[i + 1] = currentColumn;
    }

    return path;
}

std::vector<std::vector<int>> SeamCarver::compute_vertical_energies() const {
    std::vector<std::vector<int>> result;
    result.resize(get_height(), std::vector<int>(get_width()));
    for (int x = 0; x < get_width(); x++) {
        result[get_height() - 1][x] = get_energy(get_height() - 1, x);
    }

    for (int row = get_height() - 2; row >= 0; row--) {
        for (int col = 0; col < get_width(); col++) {
            int energy = get_energy(row, col);
            int best = get_energy(row + 1, col);

            if (col < get_width() - 1) {
                int right = get_energy(row + 1, col + 1);
                best = std::min(best, right);
            }

            if (col > 0) {
                int left = get_energy(row + 1, col - 1);
                best = std::min(best, left);
            }

            result[row][col] = best + energy;
        }
    }

    return result;
    // std::cout << result.size() << "," << result[0].size() << "\n";
}

std::vector<std::vector<int>> SeamCarver::compute_horizontal_energies() const {
    std::vector<std::vector<int>> result;
    result.resize(get_height(), std::vector<int>(get_width()));
    for (int y = 0; y < get_height(); y++) {
        result[y][get_width() - 1] = get_energy(y, get_width() - 1);
    }

    for (int col = get_width() - 2; col >= 0; col--) {
        for (int row = 0; row < get_height(); row++) {
            int energy = get_energy(row, col);
            int best = get_energy(row, col + 1);

            if (row < get_height() - 1) {
                int down = get_energy(row + 1, col + 1);
                best = std::min(best, down);
            }

            if (row > 0) {
                int up = get_energy(row - 1, col + 1);
                best = std::min(best, up);
            }

            result[row][col] = best + energy;
        }
    }

    return result;
    // std::cout << result.size() << "," << result[0].size() << "\n";
}

int* SeamCarver::get_horizontal_seam() const {
    std::vector<std::vector<int>> energies = compute_horizontal_energies();
    int * path = new int[get_width()];

    int startingValue = energies[0][0];
    int currentColumn = 0;

    for (int row = 1; row < get_height(); row++) {
        if (energies[row][0] < startingValue) {
            startingValue = energies[row][0];
            currentColumn = row;
        }
    }    

    path[0] = currentColumn;

    for (int i = 0; i < get_width() - 1; i++) {
        startingValue = energies[path[i]][i + 1];
        currentColumn = path[i];

        if (path[i] < get_height() - 1) {
            int down = energies[path[i] + 1][i + 1];
            if (down < startingValue) {
                startingValue = down;
                currentColumn = path[i] + 1;
            }
        }

        if (path[i] > 0) {
            int up = energies[path[i] - 1][i + 1];
            if (up < startingValue) {
                startingValue = up;
                currentColumn = path[i] - 1;
            }
        }

        path[i + 1] = currentColumn;
    }

    return path;
}

void SeamCarver::remove_vertical_seam() {
    int * path = get_vertical_seam();
    image_.remove_seam(path, true);
    delete[] path;
}

void SeamCarver::remove_horizontal_seam() {
    int * path = get_horizontal_seam();
    image_.remove_seam(path, false);
    delete[] path;
}