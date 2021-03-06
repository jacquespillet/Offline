#include "Image.hpp"

Image::Image() {}

Image::Image(int width, int height) {
    this->width = width;
    this->height = height;

    pixels = imageData(width*height, rgb(0));
}

Image::Image(int width, int height, const rgb& background) {
    this->width = width;
    this->height = height;

    pixels = imageData(width*height, background);
}

int Image::GetWidth() const {
    return width;
}
int Image::GetHeight() const {
    return height;
}


bool Image::set(int x, int y, const rgb& color) {
    
    uint64_t inx = ((height - 1 - y) * width) + x;
    if(x < 0 || x > width) return false;
    if(y < 0 || y > height) return false;

    pixels[inx] = color;
    return true;
}

void Image::gammaCorrect(real gamma) {
    rgb temp;

    real power = 1.0 / gamma;
    for(int i=0; i<pixels.size(); ++i) {
        temp = pixels[i];
        pixels[i] = glm::pow(temp, vector3(power));
    }
}

void Image::WritePPM(const std::string& fileName) const {
    std::fstream fs (fileName, std::fstream::out);

    fs << "P3\n" << width << " " << height << "\n255\n";
    
    for(int i=0; i<pixels.size(); i++) {
        int r = std::min(pixels[i].x * 256, 255.0);
        int g = std::min(pixels[i].y * 256, 255.0);
        int b = std::min(pixels[i].z * 256, 255.0);

        fs << r << " " << g << " " << b << "\n";

    }
    fs.close();
}