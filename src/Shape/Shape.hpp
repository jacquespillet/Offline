#pragma once

#include "Common/CommonIncludes.hpp"

#include "Ray.hpp"

struct BoundingBox {
    glm::vec3 min;
    glm::vec3 max;
};

struct HitPoint {
    real t;
    glm::vec3 normal;
    rgb color;
};

class Shape {
public: 
    virtual bool Hit(const Ray& r, float tmin, float tmax, float time, HitPoint& hit) const=0;
    virtual bool ShadowHit(const Ray& r, float tmin, float tmax, float time) const=0;
};