#include "Sphere.hpp"


Sphere::Sphere(const glm::vec3& center, real radius, const rgb& color) : center(center), radius(radius), color(color) {}

BoundingBox Sphere::GetBoundingBox() const {
    BoundingBox bb = {
        glm::vec3(-radius),
        glm::vec3(radius)
    };

    return bb;
}   


bool Sphere::Hit(const Ray& r, real tmin, real tmax, real time, HitPoint& hit) const {
    glm::vec3 oc = r.Origin() - center;

    float a = glm::dot(r.Direction(), r.Direction());
    float b = 2 * dot(oc, r.Direction());
    float c = dot(oc, oc) - radius * radius;

    float delta = b*b - 4 * a * c;
    
    if(delta < 0) {
        return false;
    } else {
        double t = (- b - sqrt(delta)) / (2 * a);
        if(t > tmin && t < tmax) {
            glm::vec3 hitPosition = r.PointAt(t);
            // glm::vec2 uv = GetUv(hitPosition);

            hit.color = color;
            hit.normal = glm::normalize(hitPosition -  center);
            hit.t = t;
            return true;
        }
        t = (- b + sqrt(delta)) / (2 * a);
        if(t > tmin && t < tmax) {
            glm::vec3 hitPosition = r.PointAt(t);
            // glm::vec2 uv = GetUv(hitPosition);
            hit.color = color;
            hit.normal = glm::normalize(hitPosition -  center);
            hit.t = t;
            return true;
        }
    }
    return false;    
}

bool Sphere::ShadowHit(const Ray& r, real tmin, real tmax, real time) const {
    glm::vec3 oc = r.Origin() - center;
    
    float a = glm::dot(r.Direction(), r.Direction());
    float b = 2 * dot(oc, r.Direction());
    float c = dot(oc, oc) - radius * radius;

    float delta = b*b - 4 * a * c;
    
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

