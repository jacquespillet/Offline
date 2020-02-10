#include "Instance.hpp"

Instance::Instance(const glm::mat4& transform, const glm::mat4& inverse, Shape* _prim) : M(transform), N(inverse), prim(_prim) {}

Instance::Instance(const glm::mat4& transform, Shape* _prim)  : M(transform), prim(_prim){
    N = glm::inverse(transform);
}


bool Instance::Hit(Ray r, real tmin, real tmax, real time, HitPoint& hit) const {
    vector3 no = N * glm::vec4(r.Origin(), 1);
    vector3 nd = N * glm::vec4(r.Direction(), 0);

    Ray tRay(no, nd);

    if(prim->Hit(tRay, tmin, tmax, time, hit)) {
        hit.p = M * glm::vec4(hit.p, 1);
        vector3 normal = glm::transpose(N) * vector4(hit.uvw.W, 0);
        ONB uvw;
        uvw.InitFromW(normal);
        hit.uvw = uvw;

        return true;
    } else return false;
}

bool Instance::ShadowHit(Ray r, real tmin, real tmax, real time) const {
    vector3 no = N * glm::vec4(r.Origin(), 1);
    vector3 nd = N * glm::vec4(r.Direction(), 0);

    Ray tRay(no, nd);
    return prim->ShadowHit(tRay, tmin, tmax, time);
}


BoundingBox Instance::GetBoundingBox() const {
    BoundingBox bbox = prim->GetBoundingBox();
    vector3 min = bbox.Min();
    vector3 max = bbox.Max();

    min = M * vector4(min, 1);
    max = M * vector4(max, 1);

    return BoundingBox(glm::min(min, max), glm::max(min, max));
}