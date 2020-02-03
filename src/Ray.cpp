#include "Ray.hpp"

Ray::Ray(){}

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction) {
    this->origin = origin;
    this->direction = direction;
}

Ray::Ray(const Ray& r) {
    this->origin = r.origin;
    this->direction = r.direction;
}

glm::vec3 Ray::Origin() const {
    return origin;
}

glm::vec3 Ray::Direction() const {
    return direction;
}

glm::vec3 Ray::PointAt(real t) const {
    return origin + t * direction;
}
