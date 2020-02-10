#include "BoundingBox.hpp"


BoundingBox::BoundingBox(const vector3& a, const vector3& b) {
    this->pp[0] = a;
    this->pp[1] = b;
}

vector3 BoundingBox::Min() const {
    return pp[0];
}

vector3 BoundingBox::Max() const {
    return pp[1];
}

