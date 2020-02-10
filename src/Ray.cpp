#include "Ray.hpp"

Ray::Ray(){}

Ray::Ray(vector3 origin, vector3 direction) {
    SetOrigin(origin);
    SetDirection(direction);
}

Ray::Ray(const Ray& r) {
    SetOrigin(r.origin);
    SetDirection(r.direction);
}

vector3 Ray::Origin() const {
    return origin;
}

vector3 Ray::Direction() const {
    return direction;
}

vector3 Ray::InvDirection() const {
    return invDirection;
}

void Ray::SetDirection(vector3 direction) {
    this->direction = direction;

    invDirection = 1.0 / direction;

    posneg[0] = (direction.x > 0 ? 0 : 1);
    posneg[1] = (direction.y > 0 ? 0 : 1);
    posneg[2] = (direction.z > 0 ? 0 : 1);
} 

void Ray::SetOrigin(vector3 origin) {
    this->origin = origin;
} 

vector3 Ray::PointAt(real t) const {
    return origin + t * direction;
}
