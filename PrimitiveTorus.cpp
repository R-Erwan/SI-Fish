//
// Created by erwan on 24/10/2024.
//

#include "PrimitiveTorus.h"
#include <cmath>
#include <GL/gl.h>

PrimitiveTorus::PrimitiveTorus(float R, float r, int m, int p)
        : bigRadius(R), smallRadius(r), meridians(m), parallels(p) {
    calcTorus();  // Calcul des sommets à l'initialisation
}

void PrimitiveTorus::calcTorus() {
    vertices.clear();
    indices.clear();
    normals.clear();

    // Calcul des sommets
    for (int i = 0; i < parallels; ++i) {
        float theta = i * 2.0 * M_PI / parallels;  // Angle pour chaque parallèle
        for (int j = 0; j < meridians; ++j) {
            float phi = j * 2.0 * M_PI / meridians;  // Angle pour chaque méridien
            Point p;
            p.x = (bigRadius + smallRadius * cos(theta)) * cos(phi);
            p.y = (bigRadius + smallRadius * cos(theta)) * sin(phi);
            p.z = smallRadius * sin(theta);
            vertices.push_back(p);
            // Calcul de la normale au sommet
            Point n;
            n.x = cos(theta) * cos(phi);
            n.y = cos(theta) * sin(phi);
            n.z = sin(theta);
            normals.push_back(n);

        }
    }

    // Calcul des indices pour dessiner les quads avec l'ordre dans le sens trigonométrique
    for (int i = 0; i < parallels; ++i) {
        for (int j = 0; j < meridians; ++j) {
            int next_i = (i + 1) % parallels;
            int next_j = (j + 1) % meridians;

            // Inverser l'ordre des indices pour le sens trigonométrique
            indices.push_back(i * meridians + j);
            indices.push_back(i * meridians + next_j);
            indices.push_back(next_i * meridians + next_j);
            indices.push_back(next_i * meridians + j);
        }
    }
}

void PrimitiveTorus::draw() {
    glBegin(GL_QUADS);
    for (int idx : indices) {
        glNormal3f(normals[idx].x,normals[idx].y,normals[idx].z);
        glVertex3f(vertices[idx].x, vertices[idx].y, vertices[idx].z);
    }
    glEnd();
}

int PrimitiveTorus::getMeridians() const {
    return meridians;
}

int PrimitiveTorus::getParallels() const {
    return parallels;
}