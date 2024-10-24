//
// Created by erwan on 24/10/2024.
//

#include "Point.h"
#include <cstdio>  // Pour la fonction printf

// Constructeur par défaut initialisant les coordonnées à 0
Point::Point() : x(0), y(0), z(0) {}

// Constructeur paramétré initialisant les coordonnées à des valeurs spécifiques
Point::Point(float xVal, float yVal, float zVal) : x(xVal), y(yVal), z(zVal) {}

// Fonction utilitaire pour afficher les coordonnées du point
void Point::print() const {
    printf("Point(x: %.2f, y: %.2f, z: %.2f)\n", x, y, z);
}

