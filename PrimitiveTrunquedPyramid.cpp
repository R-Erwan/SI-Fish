//
// Created by erwan on 25/10/2024.
//

#include "PrimitiveTrunquedPyramid.h"

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
    // Base inférieure
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; ++i) {
        glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
    }
    glEnd();

    // Base supérieure
    glBegin(GL_QUADS);
    for (int i = 4; i < 8; ++i) {
        glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
    }
    glEnd();

    // Faces latérales
    for (int i = 0; i < 4; ++i) {
        int index1 = i;
        int index2 = (i + 1) % 4;

        glBegin(GL_QUADS);
        glVertex3f(vertices[index1].x, vertices[index1].y, vertices[index1].z);
        glVertex3f(vertices[index1 + 4].x, vertices[index1 + 4].y, vertices[index1 + 4].z);
        glVertex3f(vertices[index2 + 4].x, vertices[index2 + 4].y, vertices[index2 + 4].z);
        glVertex3f(vertices[index2].x, vertices[index2].y, vertices[index2].z);
        glEnd();
    }
}

void PrimitiveTrunquedPyramid::drawWithTexOnLatFace(GLuint texId) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);


        // Base inférieure
        glBegin(GL_QUADS);
        for (int i = 0; i < 4; ++i) {
            glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
        }
        glEnd();

        // Base supérieure
        glBegin(GL_QUADS);
        for (int i = 4; i < 8; ++i) {
            glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
        }
        glEnd();

        // Faces latérales
        for (int i = 0; i < 4; ++i) {
            int index1 = i;
            int index2 = (i + 1) % 4;

            glBegin(GL_QUADS);
            glTexCoord2f(0,0);
            glVertex3f(vertices[index1].x, vertices[index1].y, vertices[index1].z);
            glTexCoord2f(0,1);
            glVertex3f(vertices[index1 + 4].x, vertices[index1 + 4].y, vertices[index1 + 4].z);
            glTexCoord2f(1,1);
            glVertex3f(vertices[index2 + 4].x, vertices[index2 + 4].y, vertices[index2 + 4].z);
            glTexCoord2f(1,0);
            glVertex3f(vertices[index2].x, vertices[index2].y, vertices[index2].z);
            glEnd();
        }
    glDisable(GL_TEXTURE_2D);
}

float PrimitiveTrunquedPyramid::getHeight() {
    return height;
}

