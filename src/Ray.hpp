#pragma once

#include "Common/CommonIncludes.hpp"

class Ray {
public : 
    Ray();
    Ray(vector3 origin, vector3 direction);
    Ray(const Ray& r);

    vector3 Origin() const;
    vector3 Direction() const;
    vector3 PointAt(real t) const;

private:
    vector3 origin;
    vector3 direction;
};
