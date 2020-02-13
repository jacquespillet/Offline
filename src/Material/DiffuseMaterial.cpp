#include "DiffuseMaterial.hpp"


rgb DiffuseMaterial::AmbientResponse(const ONB& onb, const vector3& incident) {
    return albedo;
}

bool DiffuseMaterial::ExplicitBrdf(const ONB& onb, const vector3& outGoing0, const vector3& outGoing1, rgb& outAlbedo, real& brdfValue) {
    brdfValue = 0.31830988618;
    outAlbedo = brdfValue * albedo;
    return true;
}

bool DiffuseMaterial::DiffuseDirection(const ONB& onb, const vector3& incident, const vector2& random, rgb& outAlbedo, vector3& outGoing, real& pdf) {
    real pi = 3.14159265359;
    real phi = 2 * pi * random.x;
    real r = sqrt(random.y);
    real x = r * cos(phi);
    real y = r * sin(phi);
    real z = sqrt(1 - x*x - y*y);
    
    outAlbedo = albedo;
    outGoing = glm::normalize(x * onb.U + y * onb.V + z * onb.W);

    float cosine = glm::dot(outGoing,onb.W);
    if(cosine < 0) cosine=0;
    pdf = cosine / pi;

    return true;
}
