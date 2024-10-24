#include "PrimitiveCylindre.h"
#include <cmath>

PrimitiveCylindre::PrimitiveCylindre(float r, int p, float h) : radius(r), step(p), height(h) {
    calcCylyndre();
}

void PrimitiveCylindre::calcCylyndre() {
    vertices.clear();
    indices.clear();

    // Calcul des sommets (vertices)
    //Disque supérieur
    for (int i = 0; i < step; ++i) {
        Point p;
        Point p2;
        p.x = radius * cos((i * 2 * M_PI) / step);
        p.y = height / 2;
        p.z = radius * sin((i * 2 * M_PI) / step);
        vertices.push_back(p);
    }

    //Disque inférieur
    for (int i = 0; i < step; ++i) {
        Point p;
        p.x = radius * cos((i * 2 * M_PI) / step);
        p.y = -height / 2;
        p.z = radius * sin((i * 2 * M_PI) / step);
        vertices.push_back(p);

    }

    // Logique des indices pour les disques supérieur et inférieur
    for (int i = 0; i < step * 2; ++i) {
        indices.push_back(i);
    }

    // Indices des faces latérales
    for (int i = 0; i < step; ++i) {
        int index1 = i % step;
        int index2 = (i + 1) % step;

        indiceslat.push_back(index1);
        indiceslat.push_back(index1 + step);
        indiceslat.push_back(index2 + step);
        indiceslat.push_back(index2);
    }
}

void PrimitiveCylindre::draw() {
    // Disque supérieur
    glBegin(GL_POLYGON);
    for (int i = 0; i < step; ++i) {
        Point p = vertices[indices[i]];
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();

    // Disque inférieur
    glBegin(GL_POLYGON);
    for (int i = 0; i < step; ++i) {
        Point p = vertices[indices[i + step]];
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();

    // Faces latérales
    glBegin(GL_QUADS);
    for (int i : indiceslat) {
        Point p = vertices[i];  // Utilisation correcte d'indiceslat
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();
}

float PrimitiveCylindre::getRadius() {
    return radius;
}

int PrimitiveCylindre::getStep() {
    return step;
}

int PrimitiveCylindre::getHeight() {
    return height;
}
