//
// Created by erwan on 21/10/2024.
//

#ifndef SI_FISH_PRIMITIVESPHERE_H
#define SI_FISH_PRIMITIVESPHERE_H

#include <vector>
#include <GL/glut.h>

struct Point {
    float x, y, z;
};

class PrimitiveSphere {
private:
    float radius;
    int meridians, parallels;

    std::vector<Point> vertices;  // Liste des sommets de la sphère
    std::vector<GLint> indices;   // Indices pour dessiner les faces

    void calcSphere();  // Méthode privée pour calculer les sommets et indices

public:
    PrimitiveSphere(float r, int m, int p);  // Constructeur

    void draw();  // Méthode pour dessiner la sphère
};


#endif //SI_FISH_PRIMITIVESPHERE_H
