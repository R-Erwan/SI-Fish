//
// Created by erwan on 21/10/2024.
//

#ifndef SI_FISH_PRIMITIVESPHERE_H
#define SI_FISH_PRIMITIVESPHERE_H

#include <vector>
#include <GL/glut.h>
#include "Point.h"

class PrimitiveSphere {
private:
    float radius;
    int meridians, parallels;

    std::vector<Point> vertices;  // Liste des sommets de la sphère
    std::vector<GLint> indices;   // Indices pour dessiner les faces
    std::vector<Point> normals;

    void calcSphere();  // Méthode privée pour calculer les sommets et indices

public:
    PrimitiveSphere(float r, int m, int p);  // Constructeur
    void draw();

    int getMeridians() const;
    int getParallels() const;
    float getRadius() const;// Méthode pour dessiner la sphère
};


#endif //SI_FISH_PRIMITIVESPHERE_H
