//
// Created by erwan on 24/10/2024.
//

#ifndef SI_FISH_POINT_H
#define SI_FISH_POINT_H


class Point {
public:
    float x, y, z;  // Coordonnées dans l'espace 3D

    // Constructeurs
    Point();  // Constructeur par défaut
    Point(float x, float y, float z);  // Constructeur paramétré

    // Méthodes utilitaires pour l'display et les opérations
    void print() const;
};


#endif //SI_FISH_POINT_H
