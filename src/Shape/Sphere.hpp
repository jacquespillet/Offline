#pragma once

#include "Shape.hpp"
#include "Common/CommonIncludes.hpp"

class Sphere : public Shape {
public : 
    Sphere(const glm::vec3& center, real radius, const rgb& color);
    BoundingBox GetBoundingBox() const;    
    
    bool Hit(const Ray& r, real tmin, real tmax, real time, HitPoint& hit) const;
    bool ShadowHit(const Ray& r, real tmin, real tmax, real time) const;

private: 
    glm::vec3 center;
    real radius;
    rgb color;
};
