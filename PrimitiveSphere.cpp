#include "PrimitiveSphere.h"  // Inclusion du header correspondant
#include <cmath>      // Pour les calculs mathématiques comme sin et cos

PrimitiveSphere::PrimitiveSphere(float r, int m, int p) :radius(r), meridians(m),parallels(p) {
    calcSphere();  // Calcul des coordonnées des sommets à l'initialisation
}

void PrimitiveSphere::calcSphere() {
    vertices.clear();  // Réinitialisation des vecteurs
    indices.clear();

    // Logique de calcul des sommets (vertices) et des indices (indices)
    for (int i = 0; i < parallels; ++i) {
        for (int j = 0; j < meridians; ++j) {
            Point p;
            p.x = radius * cos(j*((2.0*M_PI)/meridians)) * cos(i*((M_PI)/(parallels-1)) - (M_PI / 2));
            p.y = radius * sin(j*((2.0*M_PI)/meridians)) * cos(i*((M_PI)/(parallels-1)) - (M_PI / 2));
            p.z = radius * sin(i*(M_PI)/(parallels-1) - (M_PI / 2));
            vertices.push_back(p);
        }
    }
    // Ajouter la logique pour remplir les indices ici
    for (int i = 0; i < parallels - 1; ++i) {
        for (int j = 0; j < meridians; ++j) {
            indices.push_back(j+(i*meridians));
            indices.push_back((j+1)%meridians + (i*meridians));
            indices.push_back(((j+1)%meridians)+meridians+(i*meridians));
            indices.push_back(j + meridians +(i*meridians));
        }
    }
}

void PrimitiveSphere::draw() {
    glBegin(GL_QUADS); // Utilisation de GL_QUADS pour dessiner des quadrilatères
    int idx = 0;
    float u, v;
    for (int j = 0; j <parallels-1; ++j) {
        for (int i = 0; i < meridians-1; ++i) {
            for (int k = 0; k < 4; ++k) {
                u = static_cast<float>(indices[idx] % meridians) / meridians; // Coordonnée U
                v = static_cast<float>(indices[idx] / meridians) / (parallels-1); // Coordonnée V
                glTexCoord2f(u,v);
                glVertex3f(vertices[indices[idx]].x, vertices[indices[idx]].y, vertices[indices[idx]].z);
                idx++;
            }
        }
        u = static_cast<float>(indices[idx] % meridians) / meridians; // Coordonnée U
        v = static_cast<float>(indices[idx] / meridians) / (parallels-1); // Coordonnée V
        glTexCoord2f(u,v);
        glVertex3f(vertices[indices[idx]].x, vertices[indices[idx]].y, vertices[indices[idx]].z);
        idx++;

        u = 1;
        v = j / (parallels-1);
        glTexCoord2f(u,v);
        glVertex3f(vertices[indices[idx]].x, vertices[indices[idx]].y, vertices[indices[idx]].z);
        idx++;

        u = 1;
        v = (j+1) / (parallels-1);
        glTexCoord2f(u,v);
        glVertex3f(vertices[indices[idx]].x, vertices[indices[idx]].y, vertices[indices[idx]].z);
        idx++;

        u = static_cast<float>(indices[idx] % meridians) / meridians; // Coordonnée U
        v = static_cast<float>(indices[idx] / meridians) / (parallels-1); // Coordonnée V
        glTexCoord2f(u,v);
        glVertex3f(vertices[indices[idx]].x, vertices[indices[idx]].y, vertices[indices[idx]].z);
        idx++;
    }
    glEnd();
}

// Retourne le nombre de méridiens
int PrimitiveSphere::getMeridians() const {
    return meridians;
}

// Retourne le nombre de parallèles
int PrimitiveSphere::getParallels() const {
    return parallels;
}

float PrimitiveSphere::getRadius() const {
    return radius;
}

