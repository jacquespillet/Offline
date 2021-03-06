#pragma once

#include "Common/CommonIncludes.hpp"
#include "Material.hpp"


class MetalMaterial : public Material {
public: 
    MetalMaterial(rgb _albedo, real _phongExponent);

    virtual rgb AmbientResponse(const ONB& onb, const vector3& incident);

    virtual bool SpecularDirection(const ONB& onb, const vector3& incident, const vector2& random, rgb& outAlbedo, vector3& outGoing, real& pdf);
    virtual bool DiffuseDirection(const ONB& onb, const vector3& incident, const vector2& random, rgb& outAlbedo, vector3& outGoing, real& pdf, real& brdf);

private: 
    real phongExponent;
    rgb albedo;
};
