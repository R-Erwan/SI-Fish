//
// Created by erwan on 25/10/2024.
//

#include "PrimitiveTrunquedPyramid.h"
#include <cmath>

PrimitiveTrunquedPyramid::PrimitiveTrunquedPyramid(float w, float l, float h, float offX, float offY)
: widthBase(w), lenghtBase(l), height(h), offsetX(offX), offsetY(offY) {
    calc();
}

void PrimitiveTrunquedPyramid::calc() {
    vertices.clear();

    //Calcul des sommets (vertices)
    //Rectangle de la base
    vertices.push_back({widthBase/2,0.0,lenghtBase/2});
    vertices.push_back({widthBase/2,0.0,-lenghtBase/2});
    vertices.push_back({-widthBase/2,0.0,-lenghtBase/2});
    vertices.push_back({-widthBase/2,0.0, lenghtBase/2});

    //Rectangle supérieur
    vertices.push_back({widthBase/2 - offsetX, height, lenghtBase/2 - offsetY});
    vertices.push_back({widthBase/2 - offsetX, height, -lenghtBase/2 + offsetY});
    vertices.push_back({-widthBase/2 + offsetX, height, -lenghtBase/2 + offsetY});
    vertices.push_back({-widthBase/2 + offsetX, height, lenghtBase/2 - offsetY});

}

void PrimitiveTrunquedPyramid::draw() {
    // Base inférieure (dans le sens trigonométrique)
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);  // Normale dirigée vers le bas
    glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
    glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
    glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
    glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
    glEnd();

    // Base supérieure (dans le sens trigonométrique)
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);  // Normale dirigée vers le haut
    glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
    glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
    glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
    glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
    glEnd();

    // Faces latérales (sens trigonométrique pour chaque quad)
    for (int i = 0; i < 4; ++i) {
        int index1 = i;
        int index2 = (i + 1) % 4;


        // Calcul de la normale pour la face latérale
        Point vec1 = {vertices[index2].x - vertices[index1].x, vertices[index2].y - vertices[index1].y, vertices[index2].z - vertices[index1].z};
        Point vec2 = {vertices[index1 + 4].x - vertices[index1].x, vertices[index1 + 4].y - vertices[index1].y, vertices[index1 + 4].z - vertices[index1].z};
        Point normal = {
                vec1.y * vec2.z - vec1.z * vec2.y,
                vec1.z * vec2.x - vec1.x * vec2.z,
                vec1.x * vec2.y - vec1.y * vec2.x
        };
        float length = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
        normal.x /= length;
        normal.y /= length;
        normal.z /= length;

        glBegin(GL_QUADS);
        glNormal3f(normal.x, normal.y, normal.z);  // Appliquer la normale calculée
        glVertex3f(vertices[index1].x, vertices[index1].y, vertices[index1].z);
        glVertex3f(vertices[index2].x, vertices[index2].y, vertices[index2].z);
        glVertex3f(vertices[index2 + 4].x, vertices[index2 + 4].y, vertices[index2 + 4].z);
        glVertex3f(vertices[index1 + 4].x, vertices[index1 + 4].y, vertices[index1 + 4].z);
        glEnd();
    }
}

void PrimitiveTrunquedPyramid::drawWithTexOnLatFace(GLuint texId) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);

    // Base inférieure
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);  // Normale dirigée vers le bas
    glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
    glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
    glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
    glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
    glEnd();

    // Base supérieure
    glBegin(GL_QUADS);

    glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
    glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
    glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
    glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);
    glEnd();

    // Faces latérales avec coordonnées de texture
    for (int i = 0; i < 4; ++i) {
        int index1 = i;
        int index2 = (i + 1) % 4;

        // Calcul de la normale pour la face latérale
        Point vec1 = {vertices[index2].x - vertices[index1].x, vertices[index2].y - vertices[index1].y, vertices[index2].z - vertices[index1].z};
        Point vec2 = {vertices[index1 + 4].x - vertices[index1].x, vertices[index1 + 4].y - vertices[index1].y, vertices[index1 + 4].z - vertices[index1].z};
        Point normal = {
                vec1.y * vec2.z - vec1.z * vec2.y,
                vec1.z * vec2.x - vec1.x * vec2.z,
                vec1.x * vec2.y - vec1.y * vec2.x
        };
        float length = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
        normal.x /= length;
        normal.y /= length;
        normal.z /= length;

        glBegin(GL_QUADS);
        glNormal3f(normal.x, normal.y, normal.z);  // Appliquer la normale calculée
        glTexCoord2f(0, 0);
        glVertex3f(vertices[index1].x, vertices[index1].y, vertices[index1].z);
        glTexCoord2f(1, 0);
        glVertex3f(vertices[index2].x, vertices[index2].y, vertices[index2].z);
        glTexCoord2f(1, 1);
        glVertex3f(vertices[index2 + 4].x, vertices[index2 + 4].y, vertices[index2 + 4].z);
        glTexCoord2f(0, 1);
        glVertex3f(vertices[index1 + 4].x, vertices[index1 + 4].y, vertices[index1 + 4].z);
        glEnd();
    }

    glDisable(GL_TEXTURE_2D);
}

float PrimitiveTrunquedPyramid::getHeight() {
    return height;
}

