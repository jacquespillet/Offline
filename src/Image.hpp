#pragma once
#include "Common/CommonIncludes.hpp"

typedef std::vector<rgb> imageData;

class Image {

public: 
    Image();
    Image(int width, int height);
    Image(int width, int height, const rgb& backgroundColor);

    bool set(int x, int y, const rgb& color);

    void gammaCorrect(real gamma);

    void WritePPM(const std::string& filename) const;

private:
    imageData pixels;
    int width;
    int height;
};
