#pragma once

#include "Common/CommonIncludes.hpp"

#include "Ray.hpp"
#include "ONB.hpp"

struct BoundingBox {
    vector3 min;
    vector3 max;
};

struct HitPoint {
    real t;
    vector3 p;
    ONB uvw;
    rgb color;
};

class Shape {
public: 
    virtual bool Hit(Ray r, real tmin, real tmax, real time, HitPoint& hit) const=0;
    virtual bool ShadowHit(Ray r, real tmin, real tmax, real time) const=0;
};