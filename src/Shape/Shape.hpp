#pragma once

#include "Common/CommonIncludes.hpp"

#include "Ray.hpp"
#include "ONB.hpp"
#include "BoundingBox.hpp"

class Material;

struct HitPoint {
    real t;
    vector3 p;
    ONB uvw;
    rgb color;
    vector2 uv;
    Material* material;
};

class Shape {
public: 
    virtual bool Hit(Ray r, real tmin, real tmax, real time, HitPoint& hit) const=0;
    virtual bool ShadowHit(Ray r, real tmin, real tmax, real time) const=0;
    virtual BoundingBox GetBoundingBox() const=0;

    Material* material;
};