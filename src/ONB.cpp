#include "ONB.hpp"

ONB::ONB(const vector3& a, const vector3& b, const vector3& c) {
    U=a;
    V=b;
    W=c;
}

void ONB::Set(const vector3& u, const vector3& v, const vector3& w) {
    U=u;
    V=v;
    W=w;
}

void ONB::InitFromU(const vector3& u) {
    vector3 n(1, 0, 0);
    vector3 m(0, 1, 0);
    U = glm::normalize(u);
    V = glm::cross(U, n);

    if(glm::length(V) < ONB_EPSILON) V = glm::cross(U, m);

    W = glm::cross(U, V);
}
void ONB::InitFromV(const vector3& v) {
    vector3 n(1, 0, 0);
    vector3 m(0, 1, 0);
    V = glm::normalize(v);
    U = glm::cross(V, n);

    if(glm::length2(V) < ONB_EPSILON) V = glm::cross(V, m);

    W = glm::cross(U, V);
}
void ONB::InitFromW(const vector3& w) {
	vector3 n(1.0f, 0.0f, 0.0f);
	vector3 m(0.0f, 1.0f, 0.0f);

	W = glm::normalize(w);
	U = glm::cross(W, n);

	if (glm::length2(U) < ONB_EPSILON) U = glm::cross(W, m);
	
    V = glm::cross(W, U);
    
}

void ONB::InitFromUV(const vector3& u, const vector3& v) {
    U = glm::normalize(u);
    W = glm::normalize(glm::cross(u, v));
    V = glm::cross(W, U);
}

void ONB::InitFromVU(const vector3& v, const vector3& u) {
    V = glm::normalize(v);
    W = glm::normalize(glm::cross(u, v));
    V = glm::cross(V, W);
}

void ONB::InitFromUW(const vector3& u, const vector3& w) {
    U = glm::normalize(u);
    V = glm::normalize(glm::cross(w, u));
    U = glm::cross(U, V);

}
void ONB::InitFromWU(const vector3& w, const vector3& u) {
    W = glm::normalize(w);
    V = glm::normalize(glm::cross(w, u));
    U = glm::cross(V, W);
}

void ONB::InitFromVW(const vector3& v, const vector3& w) {
    V = glm::normalize(v);
    U = glm::normalize(glm::cross(v, w));
    W = glm::cross(U, V);
}
void ONB::InitFromWV(const vector3& w, const vector3& v) {
    W = glm::normalize(w);
    U = glm::normalize(glm::cross(v, w));
    V = glm::cross(W, U);
}

bool operator==(const ONB& o1, const ONB& o2) {
    return (o1.U == o2.U && o1.V == o2.V && o1.W == o2.W);
}
