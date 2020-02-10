#pragma once

#include "Common/CommonIncludes.hpp"
#include "Ray.hpp"

class BoundingBox {
public:

    BoundingBox(){}
    BoundingBox(const vector3& a, const vector3& b);
    vector3 Min() const;
    vector3 Max() const;
    bool RayIntersects(const Ray& r, float tmin, float tmax) const;

    vector3 pp[2];
};

inline BoundingBox Surround(const BoundingBox& b1, const BoundingBox& b2) {
    vector3 min = glm::min(b1.Min(), b2.Min());
    vector3 max = glm::max(b1.Max(), b2.Max());

    return BoundingBox(min, max);
}

inline bool BoundingBox::RayIntersects(const Ray& r, float tmin, float tmax) const {
    real intervalMin = tmin;
    real intervalMax = tmax;

    int posneg = r.posneg[0];
    float t0 = (pp[posneg].x - r.Origin().x) * r.InvDirection().x;
    float t1 = (pp[1 - posneg].x - r.Origin().x) * r.InvDirection().x;
    if(t0 > intervalMin) intervalMin = t0;
    if(t1 < intervalMax) intervalMax = t1;
    if(intervalMin > intervalMin) return false;

    posneg = r.posneg[1];
    t0 = (pp[posneg].y - r.Origin().y) * r.InvDirection().y;
    t1 = (pp[1 - posneg].y - r.Origin().y) * r.InvDirection().y;
    if(t0 > intervalMin) intervalMin = t0;
    if(t1 < intervalMax) intervalMax = t1;
    if(intervalMin > intervalMin) return false;

    posneg = r.posneg[2];
    t0 = (pp[posneg].z - r.Origin().z) * r.InvDirection().z;
    t1 = (pp[1 - posneg].z - r.Origin().z) * r.InvDirection().z;
    if(t0 > intervalMin) intervalMin = t0;
    if(t1 < intervalMax) intervalMax = t1;
    if(intervalMin > intervalMin) return false;
}

