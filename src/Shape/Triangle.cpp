#include "Triangle.hpp"
Triangle::Triangle(const glm::vec3& _p0, const glm::vec3& _p1, const glm::vec3& _p2, const rgb& _color) : p0(_p0), p1(_p1), p2(_p2), color(_color){}

bool Triangle::Hit(const Ray& r, real tmin, real tmax, real time, HitPoint& hit) const {
    const real kEpsilon = 1e-8; 

    glm::vec3 p0p1 = p1 - p0; 
    glm::vec3 p0p2 = p2 - p0; 
    glm::vec3 pvec = glm::cross(r.Direction(), p0p2);
    real det = glm::dot(p0p1, pvec);

    // ray and triangle are parallel if det is close to 0
    if (std::abs(det) < kEpsilon) return false; 

    real invDet = 1 / det; 

    glm::vec3 tvec = r.Origin() - p0; 
    real u = glm::dot(tvec, pvec) * invDet; 
    if (u < 0 || u > 1) return false; 

    glm::vec3 qvec = glm::cross(tvec, p0p1); 
    real v = glm::dot(r.Direction(), qvec) * invDet; 
    if (v < 0 || u + v > 1) return false; 

    real t = glm::dot(p0p2, qvec) * invDet; 

    if(t >= tmin && t <= tmax) {
        hit.color = color;
        hit.t = t;
        hit.normal = glm::normalize(glm::cross(p1-p0, p2-p0));
        return true;
    }
    return false; 
}

bool Triangle::ShadowHit(const Ray& r, real tmin, real tmax, real time) const {
    const real kEpsilon = 1e-8; 

    glm::vec3 p0p1 = p1 - p0; 
    glm::vec3 p0p2 = p2 - p0; 
    glm::vec3 pvec = glm::cross(r.Direction(), p0p2);
    real det = glm::dot(p0p1, pvec);

    // ray and triangle are parallel if det is close to 0
    if (std::abs(det) < kEpsilon) return false; 

    real invDet = 1 / det; 

    glm::vec3 tvec = r.Origin() - p0; 
    real u = glm::dot(tvec, pvec) * invDet; 
    if (u < 0 || u > 1) return false; 

    glm::vec3 qvec = glm::cross(tvec, p0p1); 
    real v = glm::dot(r.Direction(), qvec) * invDet; 
    if (v < 0 || u + v > 1) return false; 

    real t = glm::dot(p0p2, qvec) * invDet; 

    return (t >= tmin && t <= tmax);
}