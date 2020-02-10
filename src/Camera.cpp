#include "Camera.hpp"

#include "Ray.hpp"

Camera::Camera() {}

Camera::Camera(const Camera& orig) {
    position = orig.position;
    lowerLeft = orig.lowerLeft;
    horizontal = orig.horizontal;
    vertical = orig.vertical;
    u = orig.u;
    v = orig.v;
    w = orig.w;
    lensRadius = orig.lensRadius;
    time0 = orig.time0;
    time1 = orig.time1;
}

Camera::Camera(vector3 lookfrom, vector3 lookat, vector3 up, real fovy, real aspectRatio, real aperture, real focusDistance, real t0, real t1) {
    real pi = 3.14159265358979323846;

    time0 = t0;
    time1 = t1;
    lensRadius = aperture / 2.0;

    double theta = fovy * pi / 180;
    double halfHeight = std::tan(theta/2);
    double halfWidth = aspectRatio *  halfHeight;

    position = lookfrom;
    
    w = glm::normalize(position - lookat);
    u = glm::normalize(glm::cross(up, w));
    v = glm::cross(w, u);

    lowerLeft = position - halfWidth * focusDistance * u - halfHeight *focusDistance * v - focusDistance *w;
    horizontal = 2 * halfWidth * focusDistance * u;
    vertical = 2 * halfHeight * focusDistance *v;

    std::cout << glm::to_string(horizontal) << std::endl;
    std::cout << glm::to_string(vertical) << std::endl;
}

Ray Camera::GetRay(real s, real t, real xi1, real xi2) {
    vector3 rd = lensRadius * vector3(xi1, xi2, 0);
    vector3 offset =  rd.x * u  + rd.y * v;
    double time = time0 + ((double) rand() / (double) RAND_MAX) * (time1 - time0);

    vector3 direction = glm::normalize((lowerLeft + s * horizontal + t*vertical) - position - offset);    
    return Ray(position + offset, direction);
}
