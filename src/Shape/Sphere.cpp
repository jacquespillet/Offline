#include "Sphere.hpp"


Sphere::Sphere(const vector3& center, real radius, const rgb& color) : center(center), radius(radius), color(color) {}

BoundingBox Sphere::GetBoundingBox() const {
    BoundingBox bb(vector3(-radius), vector3(radius));
    return bb;
}   


bool Sphere::Hit(Ray r, real tmin, real tmax, real time, HitPoint& hit) const {
    vector3 oc = r.Origin() - center;

    real a = glm::dot(r.Direction(), r.Direction());
    real b = 2 * dot(oc, r.Direction());
    real c = dot(oc, oc) - radius * radius;

    real delta = b*b - 4 * a * c;
    
    if(delta < 0) {
        return false;
    } else {
        double t = (- b - sqrt(delta)) / (2 * a);
        if(t > tmin && t < tmax) {
            vector3 hitPosition = r.PointAt(t);
            // vector2 uv = GetUv(hitPosition);
            ONB uvw;
            vector3 normal = glm::normalize(hitPosition -  center);
            uvw.InitFromW(normal);

            hit.p = hitPosition;
            hit.color = color;
            hit.uvw = uvw;
            hit.t = t;
        }
        t = (- b + sqrt(delta)) / (2 * a);
        if(t > tmin && t < tmax) {
            vector3 hitPosition = r.PointAt(t);
            // vector2 uv = GetUv(hitPosition);
            ONB uvw;
            vector3 normal = glm::normalize(hitPosition -  center);
            uvw.InitFromW(normal);

            hit.p = hitPosition;
            hit.color = color;
            hit.uvw = uvw;
            hit.t = t;
        }
    }
    return false;    
}

bool Sphere::ShadowHit(Ray r, real tmin, real tmax, real time) const {
    vector3 oc = r.Origin() - center;
    
    real a = glm::dot(r.Direction(), r.Direction());
    real b = 2 * dot(oc, r.Direction());
    real c = dot(oc, oc) - radius * radius;

    real delta = b*b - 4 * a * c;
    
    if(delta < 0) {
        return false;
    } else {
        double t = (- b - sqrt(delta)) / (2 * a);
        if(t > tmin && t < tmax) {
            return true;
        }
        t = (- b + sqrt(delta)) / (2 * a);
        if(t > tmin && t < tmax) {
            return true;
        }
    }

    return false;  
}

