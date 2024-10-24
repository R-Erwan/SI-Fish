//
// Created by erwan on 24/10/2024.
//

#ifndef SI_FISH_PRIMITIVECYLINDRE_H
#define SI_FISH_PRIMITIVECYLINDRE_H

#include <vector>
#include <GL/glut.h>
#include "Point.h"

class PrimitiveCylindre {
private:
    float radius;
    int step;
    float height;

    std::vector<Point> vertices; // step * 2
    std::vector<GLint> indices; // step * 2
    std::vector<GLint> indiceslat; // step * 4

    void calcCylyndre();

public:
    PrimitiveCylindre(float r, int p, float h);
    void draw();

    float getRadius();
    int getStep();
    int getHeight();

};


#endif //SI_FISH_PRIMITIVECYLINDRE_H
