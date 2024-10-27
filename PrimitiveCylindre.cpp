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

void PrimitiveCylindre::drawWithTextureOnDisque(GLuint textureId) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Disque supérieur avec texture
    glBegin(GL_POLYGON);
    for (int i = 0; i < step; ++i) {
        Point p = vertices[indices[i]];

        // Calcul de la coordonnée de texture (u, v) en fonction de l'angle
        float u = 0.5f + 0.5f * cos((i * 2 * M_PI) / step); // u varie entre 0 et 1
        float v = 0.5f + 0.5f * sin((i * 2 * M_PI) / step); // v varie entre 0 et 1

        glTexCoord2f(u, v);
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();

    // Disque inférieur avec texture
    glBegin(GL_POLYGON);
    for (int i = 0; i < step; ++i) {
        Point p = vertices[indices[i + step]];

        // Même calcul pour le disque inférieur
        float u = 0.5f + 0.5f * cos((i * 2 * M_PI) / step);
        float v = 0.5f + 0.5f * sin((i * 2 * M_PI) / step);

        glTexCoord2f(u, v);
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);

    // Faces latérales
    glBegin(GL_QUADS);
    for (int i : indiceslat) {
        Point p = vertices[i];  // Utilisation correcte d'indiceslat
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();
}

//TODO function drawWithTexturePerFace
//TODO function drawWithTextureRound

float PrimitiveCylindre::getRadius() {
    return radius;
}

int PrimitiveCylindre::getStep() {
    return step;
}

int PrimitiveCylindre::getHeight() {
    return height;
}
