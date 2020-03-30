#pragma once
#include "Common/CommonIncludes.hpp"

class Cubemap {
public:
    Cubemap();
    Cubemap(std::vector<std::string> files);
    glm::vec4 Sample(glm::vec3 uvw) const;

    bool init=false;
private:
    std::vector<std::string> files;
    std::vector<std::vector<uint8_t>> texturesData;
    int width, height, nrChannels;
    enum FACE {RIGHT, LEFT, TOP, BOTTOM, BACK, FRONT};
};
