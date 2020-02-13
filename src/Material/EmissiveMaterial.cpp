#include "EmissiveMaterial.hpp"

EmissiveMaterial::EmissiveMaterial(rgb color, real intensity) : color(color), intensity(intensity) {}

bool EmissiveMaterial::Emits() const {
    return true;
}

rgb EmissiveMaterial::EmittedRadiance(const ONB& onb, const vector3& outGoing) { 
    return intensity * color; 
}