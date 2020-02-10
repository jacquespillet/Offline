#pragma once

#include "Common/CommonIncludes.hpp"

class ONB {
public: 
    ONB(){}
    ONB(const vector3& a, const vector3& b, const vector3& c);


    void Set(const vector3& u, const vector3& v, const vector3& w);

    void InitFromU(const vector3& u);
    void InitFromV(const vector3& v);
    void InitFromW(const vector3& w);

    void InitFromUV(const vector3& u, const vector3& v);
    void InitFromVU(const vector3& v, const vector3& u);

    void InitFromUW(const vector3& u, const vector3& w);
    void InitFromWU(const vector3& w, const vector3& u);

    void InitFromVW(const vector3& v, const vector3& w);
    void InitFromWV(const vector3& w, const vector3& v);

    friend bool operator==(const ONB& o1, const ONB& o2);

    
    vector3 U, V, W;

private:
    real ONB_EPSILON = 0.01;

};
