#pragma once

#include "Shape.hpp"
#include "Common/CommonIncludes.hpp"
#include "BoundingBox.hpp"

class Sphere : public Shape {
public : 
    Sphere(const vector3& center, real radius, const rgb& color);
    BoundingBox GetBoundingBox() const;    
    
    bool Hit(Ray r, real tmin, real tmax, real time, HitPoint& hit) const;
    bool ShadowHit(Ray r, real tmin, real tmax, real time) const;

private: 
    vector3 center;
    real radius;
    rgb color;
};
