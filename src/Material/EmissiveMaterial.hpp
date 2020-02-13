#pragma once

#include "Common/CommonIncludes.hpp"
#include "Material.hpp"

class EmissiveMaterial : public Material {
public: 
    EmissiveMaterial(rgb color, real intensity);

    virtual bool Emits() const;

    virtual rgb EmittedRadiance(const ONB& onb, const vector3& outGoing);

private: 
    rgb color;
    real intensity;
};
