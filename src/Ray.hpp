#pragma once

#include "Common/CommonIncludes.hpp"

class Ray {
public : 
    Ray();
    Ray(const glm::vec3& origin, const glm::vec3& direction);
    Ray(const Ray& r);

    glm::vec3 Origin() const;
    glm::vec3 Direction() const;
    glm::vec3 PointAt(real t) const;

private:
    glm::vec3 origin;
    glm::vec3 direction;
};
