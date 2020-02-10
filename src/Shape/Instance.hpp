#pragma once

#include "Shape.hpp"
#include "Common/CommonIncludes.hpp"

class Instance : public Shape {
public : 
    Instance() {}
    ~Instance() {}

    Instance(const glm::mat4& transform, const glm::mat4& inverse, Shape* _prim);
    Instance(const glm::mat4& transform, Shape* _prim);

    bool Hit(Ray r, real tmin, real tmax, real time, HitPoint& hit) const;
    bool ShadowHit(Ray r, real tmin, real tmax, real time) const;

    BoundingBox GetBoundingBox() const;    


    glm::mat4 M;
    glm::mat4 N;
    Shape* prim;
};
