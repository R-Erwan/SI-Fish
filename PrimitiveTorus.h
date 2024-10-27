//
// Created by erwan on 24/10/2024.
//

#ifndef SI_FISH_PRIMITIVETORUS_H
#define SI_FISH_PRIMITIVETORUS_H

#include <vector>
#include "Point.h"

class PrimitiveTorus {
    public:
        PrimitiveTorus(float R, float r, int n, int m);  // Grand rayon, petit rayon, nombre de cercles, nombre de segments
        void draw();
        int getMeridians() const;
        int getParallels() const;

    private:
        void calcTorus();
        float bigRadius;    // Grand rayon (rayon du cercle principal)
        float smallRadius;  // Petit rayon (rayon du tube)
        int meridians;      // Nombre de segments du cercle principal
        int parallels;      // Nombre de segments du tube
        std::vector<Point> vertices;
        std::vector<int> indices;
        std::vector<Point> normals;
};


#endif //SI_FISH_PRIMITIVETORUS_H
