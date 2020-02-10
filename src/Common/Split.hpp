#pragma once

#include "Shape/Shape.hpp"
#include "BoundingBox.hpp"

//Routine that splits a list around a given axis and a pivot value
int Split(Shape** list, int listSize, real pivotVal, int axis) {
    BoundingBox bbox;
    real centroid;
    int retVal = 0;
    
    for(int i=0; i<listSize; i++) {
        bbox = list[i]->GetBoundingBox();
        centroid = (bbox.Min()[axis] + bbox.Max()[axis]) * 0.5;

        if(centroid < pivotVal) {
            Shape* temp = list[i];
            list[i] = list[retVal];
            list[retVal] = temp;
            retVal++;
        }
    }

    if(retVal == 0 || retVal == listSize) retVal = listSize / 2;

    return retVal;
}