#include "PrimitiveSphere.h"  // Inclusion du header correspondant
#include <cmath>      // Pour les calculs mathématiques comme sin et cos

PrimitiveSphere::PrimitiveSphere(float r, int m, int p) :radius(r), meridians(m),parallels(p) {
    calcSphere();  // Calcul des coordonnées des sommets à l'initialisation
}

void PrimitiveSphere::calcSphere() {
    vertices.clear();  // Réinitialisation des vecteurs
    indices.clear();
    normals.clear();

    // Logique de calcul des sommets (vertices) et des indices (indices)
    for (int i = 0; i < parallels; ++i) {
        for (int j = 0; j < meridians; ++j) {
            Point p;
            p.x = radius * cos(j*((2.0*M_PI)/meridians)) * cos(i*((M_PI)/(parallels-1)) - (M_PI / 2));
            p.y = radius * sin(j*((2.0*M_PI)/meridians)) * cos(i*((M_PI)/(parallels-1)) - (M_PI / 2));
            p.z = radius * sin(i*(M_PI)/(parallels-1) - (M_PI / 2));
            vertices.push_back(p);

            Point normal;
            normal.x = p.x / radius;
            normal.y = p.y / radius;
            normal.z = p.z / radius;
            normals.push_back(normal);
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
                int vertexIndex = indices[idx];
                u = static_cast<float>(vertexIndex % meridians) / meridians; // Coordonnée U
                v = static_cast<float>(vertexIndex / meridians) / (parallels-1); // Coordonnée V

                glNormal3f(normals[vertexIndex].x, normals[vertexIndex].y, normals[vertexIndex].z);
                glTexCoord2f(u,v);
                glVertex3f(vertices[vertexIndex].x, vertices[vertexIndex].y, vertices[vertexIndex].z);
                idx++;
            }
        }
        u = static_cast<float>(indices[idx] % meridians) / meridians; // Coordonnée U
        v = static_cast<float>(indices[idx] / meridians) / (parallels-1); // Coordonnée V
        glNormal3f(normals[indices[idx]].x, normals[indices[idx]].y, normals[indices[idx]].z);
        glTexCoord2f(u,v);
        glVertex3f(vertices[indices[idx]].x, vertices[indices[idx]].y, vertices[indices[idx]].z);
        idx++;

        u = 1;
        v = j / (parallels-1);
        glNormal3f(normals[indices[idx]].x, normals[indices[idx]].y, normals[indices[idx]].z);
        glTexCoord2f(u,v);
        glVertex3f(vertices[indices[idx]].x, vertices[indices[idx]].y, vertices[indices[idx]].z);
        idx++;

        u = 1;
        v = (j+1) / (parallels-1);
        glNormal3f(normals[indices[idx]].x, normals[indices[idx]].y, normals[indices[idx]].z);
        glTexCoord2f(u,v);
        glVertex3f(vertices[indices[idx]].x, vertices[indices[idx]].y, vertices[indices[idx]].z);
        idx++;

        u = static_cast<float>(indices[idx] % meridians) / meridians; // Coordonnée U
        v = static_cast<float>(indices[idx] / meridians) / (parallels-1); // Coordonnée V
        glNormal3f(normals[indices[idx]].x, normals[indices[idx]].y, normals[indices[idx]].z);
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

