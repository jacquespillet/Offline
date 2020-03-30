#pragma once

#include "Common/CommonIncludes.hpp"
#include "Image.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "Shape/Shape.hpp"
#include "Texture/Cubemap.hpp"

class Shape;

class Renderer {
public: 
    void Render(Image& target, Camera& camera, int numSamples=32);

    std::vector<Shape*> shapes;
    Camera camera;

    std::vector<vector2> pixelSamples;
    std::vector<vector2> lensSamples;
    std::vector<real> timeSamples;
    std::vector<vector2> brdfSamples;

    Cubemap skybox;


private: 
    int numSamples;
    real ambient = 0.2;
    
    rgb GetColor(const Ray& ray, int depth, int currentSample) const;
    bool Hit(Ray ray, HitPoint& hit, real time) const;

};
