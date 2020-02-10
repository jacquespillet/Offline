#include "Ray.hpp"

Ray::Ray(){}

Ray::Ray(vector3 origin, vector3 direction) {
    this->origin = origin;
    this->direction = direction;
}

Ray::Ray(const Ray& r) {
    this->origin = r.origin;
    this->direction = r.direction;
}

vector3 Ray::Origin() const {
    return origin;
}

vector3 Ray::Direction() const {
    return direction;
}

vector3 Ray::PointAt(real t) const {
    return origin + t * direction;
}
