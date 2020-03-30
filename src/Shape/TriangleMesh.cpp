#include "TriangleMesh.hpp"

#include "Common/ModelLoader.hpp"

TriangleMesh::TriangleMesh(const std::string& fileName) {
    color = vector3(0, 0, 1);
    LoadModel(fileName, &vertices, &normals, &uv, &triangles);

    min=glm::vec3(std::numeric_limits<real>::max());
    max=glm::vec3(-std::numeric_limits<real>::max());

    for(int i=0; i<vertices.size(); i++) {
        min = glm::min(vertices[i], min);
        max = glm::max(vertices[i], max);
    }

    std::cout << glm::to_string(min) << std::endl;
    std::cout << glm::to_string(max) << std::endl;
}

BoundingBox TriangleMesh::GetBoundingBox() const {
    BoundingBox bb( min, max);
    return bb;
}

bool TriangleMesh::RayTriangleIntersect( 
    const Ray& r, 
    const vector3 &v0, const vector3 &v1, const vector3 &v2, 
    real &t, real &u, real &v) const 
{ 
    const real kEpsilon = 1e-8; 

    vector3 v0v1 = v1 - v0; 
    vector3 v0v2 = v2 - v0; 
    vector3 pvec = glm::cross(r.Direction(), v0v2);
    real det = glm::dot(v0v1, pvec);

    // ray and triangle are parallel if det is close to 0
    if (std::abs(det) < kEpsilon) return false; 

    real invDet = 1 / det; 

    vector3 tvec = r.Origin() - v0; 
    u = glm::dot(tvec, pvec) * invDet; 
    if (u < 0 || u > 1) return false; 

    vector3 qvec = glm::cross(tvec, v0v1); 
    v = glm::dot(r.Direction(), qvec) * invDet; 
    if (v < 0 || u + v > 1) return false; 

    t = glm::dot(v0v2, qvec) * invDet; 

    return true; 
}  

void TriangleMesh::GetSurfaceProperties( 
    const uint32_t &triIndex, 
    const vector2 &uv, 
    vector3 &hitNormal, 
    vector3 &hitTangent, 
    vector3 &hitBitangent, 
    vector2 &hitTextureCoordinates) const 
{ 
    const vector3 n0 = this->normals[triangles[triIndex]]; 
    const vector3 n1 = this->normals[triangles[triIndex + 1]]; 
    const vector3 n2 = this->normals[triangles[triIndex + 2]]; 
    hitNormal = (1 - uv.x - uv.y) * n0 + uv.x * n1 + uv.y * n2;

    // texture coordinates
    const vector2 st0 = this->uv[triangles[triIndex]]; 
    const vector2 st1 = this->uv[triangles[triIndex + 1]]; 
    const vector2 st2 = this->uv[triangles[triIndex + 2]]; 
    hitTextureCoordinates = (1 - uv.x - uv.y) * st0 + uv.x * st1 + uv.y * st2; 

    // const vector3 t0 = this->tangents[triangles[triIndex]]; 
    // const vector3 t1 = this->tangents[triangles[triIndex + 1]]; 
    // const vector3 t2 = this->tangents[triangles[triIndex + 2]]; 
    // hitTangent = (1 - uv.x - uv.y) * t0 + uv.x * t1 + uv.y * t2; 

    // const vector3 b0 = this->bitangents[triangles[triIndex]]; 
    // const vector3 b1 = this->bitangents[triangles[triIndex + 1]]; 
    // const vector3 b2 = this->bitangents[triangles[triIndex + 2]]; 
    // hitBitangent = (1 - uv.x - uv.y) * b0 + uv.x * b1 + uv.y * b2;
}

bool TriangleMesh::Hit(Ray r, real tmin, real tmax, real time, HitPoint& hit) const {
    if(GetBoundingBox().RayIntersects(r, tmin, tmax)) {
        bool isect = false;
        vector2 uv;

        vector3 hitNormal;
        vector3 hitTangent;
        vector3 hitBitangent;
        vector2 hitUv;


        real tNear = 999999;
        for (uint32_t i = 0; i < triangles.size(); i+=3) { 
            const vector3 &v0 = vertices[triangles[i]]; 
            const vector3 &v1 = vertices[triangles[i + 1]]; 
            const vector3 &v2 = vertices[triangles[i + 2]]; 
            real t = tNear, u, v; 
            if (RayTriangleIntersect(r, v0, v1, v2, t, u, v) && t < tNear) { 
                tNear = t; 
                uv.x = u; 
                uv.y = v; 
                isect = true; 
                GetSurfaceProperties(i, uv, hitNormal, hitTangent, hitBitangent, hitUv);
            }
        }            
        
        
        if(isect && tNear > tmin && tNear < tmax)  {
            vector3 hitPosition = r.PointAt(tNear);
            
            // vector2 uv = GetUv(hitPosition);
            ONB uvw;
            uvw.InitFromW(hitNormal);

            hit.t = tNear;    
            hit.p = hitPosition;
            hit.uvw = uvw;
            hit.color = uvw.U;
            hit.material = material;

            return true;
        }
        return false;
    } else return false;
    // return false;
}

bool TriangleMesh::ShadowHit(Ray r, real tmin, real tmax, real time) const {
    bool isect = false;
    vector2 uv;

    vector3 hitNormal;
    vector3 hitTangent;
    vector3 hitBitangent;
    vector2 hitUv;

    
    real tNear = std::numeric_limits<real>::max();
    
    for (uint32_t i = 0; i < triangles.size(); i+=3) { 
        const vector3 &v0 = vertices[triangles[i]]; 
        const vector3 &v1 = vertices[triangles[i + 1]]; 
        const vector3 &v2 = vertices[triangles[i + 2]]; 
        real t = tNear, u, v; 
        if (RayTriangleIntersect(r, v0, v1, v2, t, u, v)) { 
            return true;
        }
    }                
    
    return false;
}