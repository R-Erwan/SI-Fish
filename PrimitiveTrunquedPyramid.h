//
// Created by erwan on 25/10/2024.
//

#ifndef SI_FISH_PRIMITIVETRUNQUEDPYRAMID_H
#define SI_FISH_PRIMITIVETRUNQUEDPYRAMID_H

#include <vector>
#include <GL/glut.h>
#include "Point.h"

class PrimitiveTrunquedPyramid {
private:
    float widthBase;
    float lenghtBase;
    float height;
    float offsetX;
    float offsetY;

    std::vector<Point> vertices;
    void calc();

public:
    PrimitiveTrunquedPyramid(float w, float l, float h, float offX, float offY);
    void draw();
    void drawWithTexOnLatFace(GLuint texId);
    float getHeight();
};


#endif //SI_FISH_PRIMITIVETRUNQUEDPYRAMID_H
