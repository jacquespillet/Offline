#pragma once

#include "Common/CommonIncludes.hpp"
#include "Shape.hpp"

class Triangle : public Shape {
public: 
    Triangle(const glm::vec3& _p0, const glm::vec3& _p1, const glm::vec3& _p2, const rgb& color);

    bool Hit(const Ray& r, real tmin, real tmax, real time, HitPoint& hit) const;
    bool ShadowHit(const Ray& r, real tmin, real tmax, real time) const;

private:
    glm::vec3 p0, p1, p2;
    rgb color;
};
