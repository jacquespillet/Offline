#include "BVH.hpp"

BVH::BVH() {}

//Main constructor - called once when the tree is created
BVH::BVH(Shape** shapes, int listSize) {
    if(listSize == 1) *this = BVH(shapes[0], shapes[0]);
    if(listSize == 2) *this = BVH(shapes[0], shapes[1]);

    //Get the bounding box surrounding all the shapes in the list
    bbox = shapes[0]->GetBoundingBox();
    for(int i=0; i<listSize; i++) {
        bbox = Surround(bbox, shapes[i]->GetBoundingBox());
    }

    //Get the pivot value and the mid point of the shapes
    vector3 pivot = (bbox.Max() + bbox.Min()) * 0.5;
    int midPoint = Split(shapes, listSize, pivot.x, 0);

    //build subtrees
    left  = BuildBranch(shapes, midPoint, 1); 
    right = BuildBranch(&shapes[midPoint], listSize - midPoint, 1); 
}

//Leaf constructor
BVH::BVH(Shape* _shape1,Shape* _shape2) {
    this->left = _shape1;
    this->right = _shape2;
    this->bbox = Surround(_shape1->GetBoundingBox(),_shape2->GetBoundingBox());
}

//Leaf constructor
BVH::BVH(Shape* _shape1,Shape* _shape2, const BoundingBox& _bbox) {
    this->left = _shape1;
    this->right = _shape2;
    this->bbox = _bbox;
}

BoundingBox BVH::GetBoundingBox() const {
    return bbox;
}    

bool BVH::Hit(Ray r, real tmin, real tmax, real time, HitPoint& hit) const {
    if(!bbox.RayIntersects(r, tmin, tmax)) return false;

    bool hit1 = false;
    bool hit2 = false;
    hit.t = tmax;

    hit1 = right->Hit(r, tmin, tmax, time, hit);
    hit2 = left->Hit(r, tmin, tmax, time, hit);

    return (hit1 || hit2);
}

bool BVH::ShadowHit(Ray r, real tmin, real tmax, real time) const {
    if(!bbox.RayIntersects(r, tmin, tmax)) return false;
    
    if(right->ShadowHit(r, tmin, tmax, time)) return true;
    return left->ShadowHit(r, tmin, tmax, time);
}


//Build a branch
Shape* BVH::BuildBranch(Shape** shapes, int listSize, int axis) {
    if(listSize == 1) return shapes[0];
    if(listSize == 2) return new BVH(shapes[0], shapes[1]);

    //Get the bounding box surrounding all the shapes in the list
    BoundingBox bbox = shapes[0]->GetBoundingBox();
    for(int i=1; i<listSize; i++) {
        bbox = Surround(bbox, shapes[i]->GetBoundingBox());
    }

    //Find pivot point of the list
    vector3 pivot = (bbox.Max() + bbox.Min()) * 0.5;
    int midPoint = Split(shapes, listSize, pivot[axis], axis);

    //Buidl subtrees
    Shape* left = BuildBranch(shapes, midPoint, (axis+1)%3);
    Shape* right = BuildBranch(&shapes[midPoint], listSize - midPoint, (axis+1)%3);

    //Return the constructed BVH
    return new BVH(left, right, bbox);
}
