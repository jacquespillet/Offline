#pragma once

#include "Common/CommonIncludes.hpp"
#include "Common/Split.hpp"

class BVH : public Shape {
public: 
    BVH();
    BVH(Shape** shapes, int listSize);
    BVH(Shape* _shape1,Shape* _shape2);
    BVH(Shape* _shape1,Shape* _shape2, const BoundingBox& _bbox);

    BoundingBox GetBoundingBox() const;    
    bool Hit(Ray r, real tmin, real tmax, real time, HitPoint& hit) const;
    bool ShadowHit(Ray r, real tmin, real tmax, real time) const;

    Shape* BuildBranch(Shape** shapes, int listSize, int axis);

    BoundingBox bbox;
    Shape* left;
    Shape* right;
};
