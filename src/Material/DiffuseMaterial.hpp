#pragma once

#include "Common/CommonIncludes.hpp"
#include "Material.hpp"

class DiffuseMaterial : public Material {
public: 
    DiffuseMaterial(rgb albedo) : albedo(albedo) {}

    virtual rgb AmbientResponse(const ONB& onb, const vector3& incident);

    virtual bool ExplicitBrdf(const ONB& onb, const vector3& outGoing0, const vector3& outGoing1, rgb& albedo, real& brdfValue);

    virtual bool DiffuseDirection(const ONB& onb, const vector3& incident, const vector2& random, rgb& outAlbedo, vector3& outGoing, real& pdf);

private: 
    rgb albedo;
};
