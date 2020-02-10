#pragma once

#include "Shape.hpp"
#include "Common/CommonIncludes.hpp"

class MovingSphere : public Shape {
public : 
    MovingSphere(const vector3& center, real radius, const rgb& color, real minTime, real maxTime);
    BoundingBox GetBoundingBox() const;
    
    bool Hit(Ray r, real tmin, real tmax, real time, HitPoint& hit) const;
    bool ShadowHit(Ray r, real tmin, real tmax, real time) const;

    vector3 GetCenter(real time) const;

private: 
    vector3 center;
    real radius;
    rgb color;    

    real minTime, maxTime;
};
