#include "Cubemap.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Cubemap::Cubemap(){init=false;}

Cubemap::Cubemap(std::vector<std::string> files) {
    this->files = files;
    for(int i=0; i<files.size(); i++) {
        stbi_set_flip_vertically_on_load(true);  
		unsigned char *data = stbi_load(files[i].c_str(), &width, &height, &nrChannels, 0);
		std::vector<uint8_t> textureData;
        if(data) {
			std::cout << "Texture:Constructor:SUCCESS" << std::endl;
            textureData = std::vector<uint8_t>(data, data + (width * height * nrChannels));
        }else
		{
			std::cout << "Texture:Constructor: ERROR::Failed to load texture" << std::endl;
			return;
		} 
		stbi_image_free(data);
        texturesData.push_back(textureData);
    }

    init = true;
}

glm::vec4 Cubemap::Sample(glm::vec3 stp) const {
    FACE faceToSample=FACE::RIGHT;

    float max = -999999999;
    if(stp.x > 0 && std::abs(stp.x) > max) {max = std::abs(stp.x); faceToSample = FACE::RIGHT;}
    if(stp.x < 0 && std::abs(stp.x) > max) {max = std::abs(stp.x); faceToSample = FACE::LEFT;}
    
    if(stp.y > 0 && std::abs(stp.y) > max) {max = std::abs(stp.y); faceToSample = FACE::TOP;}
    if(stp.y < 0 && std::abs(stp.y) > max) {max = std::abs(stp.y); faceToSample = FACE::BOTTOM;}
    
    if(stp.z > 0 && std::abs(stp.z) > max) {max = std::abs(stp.z); faceToSample = FACE::BACK;}
    if(stp.z < 0 && std::abs(stp.z) > max) {max = std::abs(stp.z); faceToSample = FACE::FRONT;}
    
    // std::cout << glm::to_string(stp) << "  " << faceToSample << std::endl;

    float s = stp.x; float t = stp.y; float p = stp.z;
    float u, v;
    if(faceToSample == FACE::RIGHT) {
        u = 1 - (0.5 - p / (2 * s)); 
        v = 1 - (0.5 - t / (2 * s)); 
    } else if(faceToSample == FACE::LEFT) {
        u = 1 - (0.5 - p / (2 * s)); 
        v = 1 - (0.5 + t / (2 * s)); 
    } else if(faceToSample == FACE::TOP) {
        u = 0.5 + s / (2 * t); 
        v = 0.5 + p / (2 * t); 
    } else if(faceToSample == FACE::BOTTOM) {
        u = 0.5 - s / (2 * t); 
        v = 0.5 + p / (2 * t); 
    } else if(faceToSample == FACE::BACK) {
        u = 1 - (0.5 + s / (2 * p)); 
        v = 1 - (0.5 - t / (2 * p)); 
    } else if(faceToSample == FACE::FRONT) {
        u = 1 - (0.5 + s / (2 * p)); 
        v = 1 - (0.5 + t / (2 * p)); 
    }

    int texCoordsX = std::max(0, std::min(width-1, (int)(u * (float)width)));
    int texCoordsY = std::max(0, std::min(height-1, (int)(v * (float)height)));
    int inx = texCoordsY * width * nrChannels + texCoordsX * nrChannels;
    inx = std::max(0, std::min((int)texturesData[faceToSample].size()-4, inx));
    
    float r, g, b, a;

    r =  (float)(texturesData[faceToSample][inx]) / 255.0f;
    if(nrChannels >1)  g =  (float)(texturesData[faceToSample][inx + 1]) / 255.0f;
    if(nrChannels > 2) b =  (float)(texturesData[faceToSample][inx + 2]) / 255.0f;
    if(nrChannels > 3) a =  (float)(texturesData[faceToSample][inx + 3]) / 255.0f;
    return glm::vec4(r, g, b, a);

    // return glm::vec4(0);

}