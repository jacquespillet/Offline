#pragma once

#include "Common/CommonIncludes.hpp"
#include "ONB.hpp"

class Ray;

class Camera {
public: 
    Camera();
    Camera(const Camera& orig);
    Camera(vector3 lookfrom, vector3 lookat, vector3 up, real fovy, real aspectRatio, real aperture, real focusDistance, real t0, real t1);
    Ray GetRay(real s, real t, real xi1, real xi2);

private:
    vector3 position;
    vector3 lowerLeft;
    vector3 horizontal;
    vector3 vertical;

    vector3 u, v, w;
    
    real lensRadius;

    real time0, time1;
};
