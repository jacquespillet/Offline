#include "MetalMaterial.hpp"

MetalMaterial::MetalMaterial(rgb _albedo, real _phongExponent) : albedo(_albedo), phongExponent(_phongExponent) {}

rgb MetalMaterial::AmbientResponse(const ONB& onb, const vector3& incident) {
    return albedo;
}

bool MetalMaterial::SpecularDirection(const ONB& onb, const vector3& incident,  const vector2& random, rgb& outAlbedo, vector3& outGoing, real& pdf) {
    real pi = 3.14159265359;
    real phi = 2 * pi * random.x;
    real cosTheta = pow(1 - random.y, 1 / (phongExponent+1));
    real sinTheta = sqrt(1 - cosTheta * cosTheta);

    real x = cos(phi) * sinTheta;
    real y = sin(phi) * sinTheta;
    real z = cosTheta;

    ONB basis;
    vector3 w = incident - 2 * glm::dot(incident, onb.W) * onb.W;
    basis.InitFromW(w);

    outAlbedo = albedo;
    outGoing = x * basis.U + y * basis.V + z * basis.W;
    
    return glm::dot(outGoing, onb.W) > 0;
}
