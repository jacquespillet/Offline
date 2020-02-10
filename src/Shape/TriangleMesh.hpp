#pragma once

#include "Shape.hpp"
#include "Common/CommonIncludes.hpp"
#include "BoundingBox.hpp"

class TriangleMesh : public Shape {
public : 
    TriangleMesh(const std::string& fileName);
    BoundingBox GetBoundingBox() const;
    
    bool Hit(Ray r, real tmin, real tmax, real time, HitPoint& hit) const;
    bool ShadowHit(Ray r, real tmin, real tmax, real time) const;


private: 
    void GetSurfaceProperties(const uint32_t &triIndex,  const vector2 &uv, vector3 &hitNormal,vector3 &hitTangent,vector3 &hitBitangent, vector2 &hitTextureCoordinates) const;
    bool RayTriangleIntersect(const Ray& r,  const vector3 &v0, const vector3 &v1, const vector3 &v2, real &t, real &u, real &v) const;

    vector3 color;

    vector3 min, max;

    std::vector<vector3> vertices;
    std::vector<int> triangles;
    std::vector<vector2> uv;
    std::vector<vector3> normals;
};
