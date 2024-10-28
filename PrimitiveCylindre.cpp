#include "PrimitiveCylindre.h"
#include <cmath>

PrimitiveCylindre::PrimitiveCylindre(float r, int p, float h) : radius(r), step(p), height(h) {
    calcCylindre();
}

void PrimitiveCylindre::calcCylindre() {
    vertices.clear();
    indices.clear();
    normals.clear();

    // Calcul des sommets (vertices)
    //Disque supérieur
    for (int i = 0; i < step; ++i) {
        Point p;
        p.x = radius * cos((i * 2 * M_PI) / step);
        p.y = height / 2;
        p.z = radius * sin((i * 2 * M_PI) / step);
        vertices.push_back(p);

        normals.push_back({0.0f,1.0f,0.0f});
    }

    //Disque inférieur
    for (int i = 0; i < step; ++i) {
        Point p;
        p.x = radius * cos((i * 2 * M_PI) / step);
        p.y = -height / 2;
        p.z = radius * sin((i * 2 * M_PI) / step);
        vertices.push_back(p);

        normals.push_back({0.0f, -1.0f, 0.0f});

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
        indiceslat.push_back(index2);
        indiceslat.push_back(index2 + step);
        indiceslat.push_back(index1 + step);

        // Calcul de la normale pour chaque sommet de la face latérale
        float nx = cos((i * 2 * M_PI) / step);
        float nz = sin((i * 2 * M_PI) / step);
        normals.push_back({nx, 0.0f, nz});  // Normale pour chaque sommet
    }
}

void PrimitiveCylindre::draw() {
    // Disque supérieur
    glBegin(GL_POLYGON);
    for (int i = 0; i < step; ++i) {
        Point p = vertices[indices[i]];
        glNormal3f(normals[i].x,normals[i].y,normals[i].z);
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();

    // Disque inférieur
    glBegin(GL_POLYGON);
    for (int i = 0; i < step; ++i) {
        Point p = vertices[indices[i + step]];
        glNormal3f(normals[i + step].x,normals[i + step].y,normals[i + step].z);
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();

    // Faces latérales
    glBegin(GL_QUADS);
    for (int i = 0; i < indiceslat.size(); i += 4) {
        for (int j = 0; j < 4; ++j) {
            glNormal3f(normals[i / 4 + step * 2].x, normals[i / 4 + step * 2].y, normals[i / 4 + step * 2].z);  // Normale
            Point p = vertices[indiceslat[i + j]];
            glVertex3f(p.x, p.y, p.z);
        }
    }
    glEnd();
}

void PrimitiveCylindre::drawWithTextureOnDisque(GLuint textureId) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Disque supérieur avec texture
    glBegin(GL_POLYGON);
    for (int i = step - 1; i > 0; --i) {
        Point p = vertices[indices[i]];

        // Calcul de la coordonnée de texture (u, v) en fonction de l'angle
        float u = 0.5f + 0.5f * cos((i * 2 * M_PI) / step); // u varie entre 0 et 1
        float v = 0.5f + 0.5f * sin((i * 2 * M_PI) / step); // v varie entre 0 et 1
        glNormal3f(normals[i].x,normals[i].y,normals[i].z);
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
        glNormal3f(normals[i + step].x,normals[i + step].y,normals[i + step].z);
        glTexCoord2f(u, v);
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);

    // Faces latérales
    glBegin(GL_QUADS);
    for (int i : indiceslat) {
        Point p = vertices[i];
        glNormal3f(normals[i / 4 + step * 2].x, normals[i / 4 + step * 2].y, normals[i / 4 + step * 2].z);  // Normale
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
