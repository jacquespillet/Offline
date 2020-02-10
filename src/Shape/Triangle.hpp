#pragma once

#include "Common/CommonIncludes.hpp"
#include "Shape.hpp"

class Triangle : public Shape {
public: 
    Triangle(const vector3& _p0, const vector3& _p1, const vector3& _p2, const rgb& color);

    bool Hit(Ray r, real tmin, real tmax, real time, HitPoint& hit) const;
    bool ShadowHit(Ray r, real tmin, real tmax, real time) const;

private:
    vector3 p0, p1, p2;
    rgb color;
};
