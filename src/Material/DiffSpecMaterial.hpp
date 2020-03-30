#pragma once

#include "Common/CommonIncludes.hpp"
#include "Material.hpp"

class DiffSpecMaterial : public Material {
public: 
    DiffSpecMaterial(){}
    DiffSpecMaterial(Material* d, Material* s, real r0=0.05);

    virtual rgb AmbientResponse(const ONB& onb, const vector3& incident);

    virtual bool ExplicitBrdf(const ONB& onb, const vector3& outGoing0, const vector3& outGoing1, rgb& albedo, real& brdfValue);

    virtual bool DiffuseDirection(const ONB& onb, const vector3& incident, const vector2& random, rgb& outAlbedo, vector3& outGoing, real& pdf, real& brdf);

private: 
    real r0;
    Material* diffMat;    
    Material* specMat;    
};
