#include "DiffSpecMaterial.hpp"

DiffSpecMaterial::DiffSpecMaterial(Material* d, Material* s, real r0) {
    this->diffMat = d;
    this->specMat = s;
    this->r0 = r0;
}

rgb DiffSpecMaterial::AmbientResponse(const ONB& onb, const vector3& incident) {
    real cosine = glm::dot(incident, onb.W);
    if(cosine < 0) cosine = -cosine;

    real temp1 = 1 - cosine;
    real r = r0 + (1-r0) * temp1 * temp1 * temp1 * temp1 * temp1;
    real p = (r + 0.5)/2;

    real rand = (real)std::rand() / (real)RAND_MAX;

    if(rand <= p) {
        return specMat->AmbientResponse(onb, incident);
    } else {
        return diffMat->AmbientResponse(onb, incident);
    }
}

bool DiffSpecMaterial::ExplicitBrdf(const ONB& onb, const vector3& outGoing0, const vector3& outGoing1, rgb& albedo, real& brdfValue) {
    return 1;
}

bool DiffSpecMaterial::DiffuseDirection(const ONB& onb, const vector3& incident, const vector2& random, rgb& outAlbedo, vector3& outGoing, real& pdf, real& brdf) {
    real cosine = glm::dot(incident, onb.W);
    if(cosine < 0) cosine = -cosine;

    real temp1 = 1 - cosine;
    real r = r0 + (1-r0) * temp1 * temp1 * temp1 * temp1 * temp1;
    real p = (r + 0.5)/2;

    real rand = (real)std::rand() / (real)RAND_MAX;

    if(rand <= p) {
        brdf = r / p;
        real dummyBrdf;
        return specMat->DiffuseDirection(onb, incident, random, outAlbedo, outGoing, pdf, dummyBrdf);
    } else {
        brdf = (1 - r) / (1 - p);
        real dummyBrdf;
        return diffMat->DiffuseDirection(onb, incident, random, outAlbedo, outGoing, pdf, dummyBrdf);
    }
}
