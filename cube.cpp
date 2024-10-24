#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif


#include <cstdlib>
#include <cstdio>
#include <jpeglib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "PrimitiveSphere.h"
#include "PrimitiveTorus.h"
#include "PrimitiveCylindre.h"

// Keyboard and mouse interactions
char presse;
int anglex,angley,xold,yold;
float zoomFactor = 1.0f; //Var pour suivre le niveau de zoom avec la molette

//Primitive Objects
PrimitiveSphere pSphereBody = PrimitiveSphere(1,32,32);
PrimitiveSphere eyeLeft = PrimitiveSphere(1,32,32);
PrimitiveSphere eyeRight = PrimitiveSphere(1,32,32);
PrimitiveSphere pupilLeft = PrimitiveSphere(1,32,32);
PrimitiveSphere pupilRight = PrimitiveSphere(1,32,32);

PrimitiveTorus eyelidLeft = PrimitiveTorus(1,0.1,32,32);
PrimitiveTorus eyelidRight = PrimitiveTorus(1,0.1,32,32);

PrimitiveCylindre topFin = PrimitiveCylindre(0.5,32,0.1);


//TODO Classe pour faire des pyramides

//Images and Textures
std::vector<unsigned char> imageSoleil; GLuint t_soleil;

void drawBody() {
    float SCALE_X_FACTOR = 1.15;
    GLdouble planEquation[] = {-0.9, 0.0, 0.0, SCALE_X_FACTOR * 0.86}; // EQ: −0.9x+0.0y+0.0z+0.99=0 Le vecteur normal est perpendiculaire a x

    // Active le clipping
    glEnable(GL_CLIP_PLANE0);
    glClipPlane(GL_CLIP_PLANE0, planEquation);

        glPushMatrix();
            // Dessine l'extérieur de la sphère (orange)
            glEnable(GL_CULL_FACE);          // Active le culling des faces
                glCullFace(GL_FRONT);             // Cache les faces arrières (intérieures)
                glColor3f(0.91f, 0.63f, 0.11f);  // Couleur orange pour l'extérieur
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, t_soleil);
                    glScalef(SCALE_X_FACTOR, 1.05f, 1.0f);
                    pSphereBody.draw();
                glDisable(GL_TEXTURE_2D);

                // Dessine l'intérieur de la sphère (noir)
                glCullFace(GL_BACK);            // Cache les faces avant (extérieures)
                glColor3f(0.0f, 0.0f, 0.0f);     // Couleur noire pour l'intérieur
                pSphereBody.draw();              // Redessine la sphère
            // Désactive les options activées
            glDisable(GL_CULL_FACE);
        glPopMatrix();

    glDisable(GL_CLIP_PLANE0);
}
void drawEyes(){
    float bodyRadius = pSphereBody.getRadius(); // Rayon du corps principal
    float radius = 0.4f * bodyRadius; // Rayon des yeux
    float distance = bodyRadius *0.8f; // Distance des yeux par rapport au rayon, du corps
    float pupilRadius = 0.6f * radius;
    float pupilOffset = 0.8f * radius;

    //Œil gauche
    glPushMatrix();

        glTranslatef(distance * cos(M_PI/4), // longitude (position horizontal)
                     distance * sin(M_PI/6), // latitude (position hauteur)
                     distance * sin(M_PI/4)); // profondeur
        glColor3f(0.82,0.77,0.69);
        glScalef(radius,radius,radius);
        eyeLeft.draw();

        //Paupière gauche
        glPushMatrix();
            glColor3f(0.58,0.34,0.31);
            glTranslatef(0.4f*radius,0.4f*radius,0.4f*radius);
            glRotatef(135, 1, -1, 0);
            eyelidLeft.draw();
        glPopMatrix();

        //Pupille gauche
        glPushMatrix();
            glColor3f(0.1,0.1,0.1);
            glTranslatef(pupilOffset,pupilOffset,pupilOffset);
            glScalef(pupilRadius/radius, pupilRadius/radius, pupilRadius/radius);
            pupilLeft.draw();
        glPopMatrix();


    glPopMatrix();

    //Œil droit
    glPushMatrix();
        glTranslatef(distance * cos(-M_PI/4), // longitude
                     distance * sin(M_PI/6), // latitude
                     distance * sin(-M_PI/4));
        glColor3f(0.82,0.77,0.69);
        glScalef(radius,radius,radius);
        eyeRight.draw();

        //Paupière droite
        glPushMatrix();
            glColor3f(0.58,0.34,0.31);
            glTranslatef(0.4f*radius,0.4f*radius,-0.4f*radius);
            glRotatef(135, -1, 1, 0);
            eyelidRight.draw();
        glPopMatrix();

        //Pupille droite
        glPushMatrix();
            glColor3f(0.1,0.1,0.1);
            glTranslatef(pupilOffset,pupilOffset,pupilOffset/2);
            glScalef(pupilRadius/radius,pupilRadius/radius,pupilRadius/radius);
            pupilRight.draw();
        glPopMatrix();
    glPopMatrix();
}
void drawTopFin(){
    glPushMatrix();
        glColor3f(0.84f, 0.55f, 0.02f);
        glTranslatef(0.0,pSphereBody.getRadius(),0.0);
        glRotatef(90,1.0,0.0,0.0);
        topFin.draw();
    glPopMatrix();
}
#include <GL/glut.h>

#include <GL/glut.h>

void drawBackFin() {
    const int num_points = 20; // Nombre de points pour la courbure
    GLfloat baseWidth = 1.0f;  // Largeur de la base
    GLfloat topWidth = 0.4f;   // Largeur du sommet
    GLfloat height = 1.0f;     // Hauteur totale de la nageoire
    GLfloat depth = 0.2f;      // Profondeur 3D de la nageoire (épaisseur)
    GLfloat curvature = 0.2f;  // Facteur de courbure (ajuster pour plus ou moins de courbure)

    // Points de la base avant
    GLfloat baseVerticesFront[num_points][3];
    // Points de la base arrière (décalé par la profondeur)
    GLfloat baseVerticesBack[num_points][3];
    // Points du sommet avant
    GLfloat topVerticesFront[num_points][3];
    // Points du sommet arrière
    GLfloat topVerticesBack[num_points][3];

    // Générer les points pour la base avant (face avant)
    for (int i = 0; i < num_points; ++i) {
        float t = (float)i / (float)(num_points - 1);           // Paramètre t variant de 0 à 1
        baseVerticesFront[i][0] = (1.0f - t) * (-baseWidth / 2) + t * (baseWidth / 2); // Coordonnée x (de gauche à droite)
        baseVerticesFront[i][1] = curvature * (t * t - t);      // Courbure appliquée sur la coordonnée y
        baseVerticesFront[i][2] = 0.0f;                         // Coordonnée z de la face avant (0 pour l'avant)
    }

    // Générer les points pour le sommet avant (face avant plus étroite)
    for (int i = 0; i < num_points; ++i) {
        float t = (float)i / (float)(num_points - 1);           // Paramètre t variant de 0 à 1
        topVerticesFront[i][0] = (1.0f - t) * (-topWidth / 2) + t * (topWidth / 2); // Coordonnée x pour le sommet (plus petit)
        topVerticesFront[i][1] = height + curvature * (t * t - t);   // Ajustement de y pour le sommet avec courbure et hauteur
        topVerticesFront[i][2] = 0.0f;                          // Coordonnée z du sommet (0 pour l'avant)
    }

    // Générer les points pour la base arrière (face arrière)
    for (int i = 0; i < num_points; ++i) {
        baseVerticesBack[i][0] = baseVerticesFront[i][0];        // Même x que la base avant
        baseVerticesBack[i][1] = baseVerticesFront[i][1];        // Même courbure y que la base avant
        baseVerticesBack[i][2] = depth;                         // Coordonnée z décalée par la profondeur
    }

    // Générer les points pour le sommet arrière (face arrière)
    for (int i = 0; i < num_points; ++i) {
        topVerticesBack[i][0] = topVerticesFront[i][0];         // Même x que le sommet avant
        topVerticesBack[i][1] = topVerticesFront[i][1];         // Même courbure y que le sommet avant
        topVerticesBack[i][2] = depth;                          // Coordonnée z décalée par la profondeur
    }

    // Dessiner les faces latérales entre la base et le sommet (GL_QUAD_STRIP)
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < num_points; ++i) {
        // Points du bord supérieur (sommet avant et arrière)
        glVertex3f(topVerticesFront[i][0], topVerticesFront[i][1], topVerticesFront[i][2]);
        glVertex3f(topVerticesBack[i][0], topVerticesBack[i][1], topVerticesBack[i][2]);
        // Points du bord inférieur (base avant et arrière)
        glVertex3f(baseVerticesFront[i][0], baseVerticesFront[i][1], baseVerticesFront[i][2]);
        glVertex3f(baseVerticesBack[i][0], baseVerticesBack[i][1], baseVerticesBack[i][2]);
    }
    glEnd();

    // Dessiner la face avant (base avant connectée au sommet avant)
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < num_points; ++i) {
        glVertex3f(baseVerticesFront[i][0], baseVerticesFront[i][1], baseVerticesFront[i][2]);
        glVertex3f(topVerticesFront[i][0], topVerticesFront[i][1], topVerticesFront[i][2]);
    }
    glEnd();

    // Dessiner la face arrière (base arrière connectée au sommet arrière)
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < num_points; ++i) {
        glVertex3f(baseVerticesBack[i][0], baseVerticesBack[i][1], baseVerticesBack[i][2]);
        glVertex3f(topVerticesBack[i][0], topVerticesBack[i][1], topVerticesBack[i][2]);
    }
    glEnd();

    // Dessiner les bases pour fermer les deux côtés
    glBegin(GL_QUADS);
    // Base inférieure (devant et derrière)
    glVertex3f(baseVerticesFront[0][0], baseVerticesFront[0][1], baseVerticesFront[0][2]);
    glVertex3f(baseVerticesFront[num_points - 1][0], baseVerticesFront[num_points - 1][1], baseVerticesFront[num_points - 1][2]);
    glVertex3f(baseVerticesBack[num_points - 1][0], baseVerticesBack[num_points - 1][1], baseVerticesBack[num_points - 1][2]);
    glVertex3f(baseVerticesBack[0][0], baseVerticesBack[0][1], baseVerticesBack[0][2]);

    // Base supérieure (devant et derrière)
    glVertex3f(topVerticesFront[0][0], topVerticesFront[0][1], topVerticesFront[0][2]);
    glVertex3f(topVerticesFront[num_points - 1][0], topVerticesFront[num_points - 1][1], topVerticesFront[num_points - 1][2]);
    glVertex3f(topVerticesBack[num_points - 1][0], topVerticesBack[num_points - 1][1], topVerticesBack[num_points - 1][2]);
    glVertex3f(topVerticesBack[0][0], topVerticesBack[0][1], topVerticesBack[0][2]);
    glEnd();
}




/**
 * Dessine les axes x y et z dans la scène.
 */
void drawAxes(){
    glPushMatrix();
    // Dessin des axes
    glBegin(GL_LINES);
    // Axe X en rouge
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0, 0, 0.0);
    glVertex3f(3, 0, 0.0);
    glEnd();

    // Axe Y en vert
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, 0, 0.0);
    glVertex3f(0, 3, 0.0);
    glEnd();

    // Axe Z en bleu
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, 0.0);
    glVertex3f(0, 0, 3.0);
    glEnd();
    glPopMatrix();
}
/**
 * Fonction principal, qui dessine toutes les figures.
 */
void affichage()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Déplacement souris.
    glRotatef(angley, 1.0, 0.0, 0.0);
    glRotatef(anglex, 0.0, 1.0, 0.0);

    // Appliquer le facteur de zoom
    glScalef(zoomFactor, zoomFactor, zoomFactor);

    drawAxes();

    drawBody();
    drawEyes();
    drawTopFin();
//drawBackFin();

    glFlush();
    glutSwapBuffers();
}

//Textures Loaders
/**
 * Charge une image dans un tableau
 * @param fichier fichier ou chercher l'image
 * @param width largeur de l'image
 * @param height hauteur de l'image
 * @param image tableau ou stocké l'image
 */
void loadJpegImage(const char *fichier, int width, int height, std::vector<unsigned char>& image) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *file;
    unsigned char *ligne;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

#ifdef __WIN32
    if (fopen_s(&file, fichier, "rb") != 0) {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier %s\n", fichier);
        exit(1);
    }
#elif __GNUC__
    if ((file = fopen(fichier, "rb")) == 0) {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier %s\n", fichier);
        exit(1);
    }
#endif

    jpeg_stdio_src(&cinfo, file);
    jpeg_read_header(&cinfo, TRUE);

    if (cinfo.image_width != width || cinfo.image_height != height) {
        fprintf(stdout, "Erreur : l'image doit être de taille %d x %d\n", width, height);
        exit(1);
    }
    if (cinfo.jpeg_color_space == JCS_GRAYSCALE) {
        fprintf(stdout, "Erreur : l'image doit être de type RGB\n");
        exit(1);
    }

    jpeg_start_decompress(&cinfo);

    // Redimensionner le vecteur pour accueillir l'image
    image.resize(3 * width * height); // 3 canaux RGB
    ligne = image.data(); // Obtenir un pointeur vers les données du vecteur

    while (cinfo.output_scanline < cinfo.output_height) {
        ligne = image.data() + 3 * width * cinfo.output_scanline; // Pointer vers la ligne courante
        jpeg_read_scanlines(&cinfo, &ligne, 1);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(file); // Fermer le fichier
}
void loadTextures(){
    loadJpegImage("../soleil.jpg",128,128,imageSoleil);
    glGenTextures(1,&t_soleil);
    glBindTexture(GL_TEXTURE_2D,t_soleil);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, imageSoleil.data());
}

//Other Functions
void clavier(unsigned char touche,int x,int y)
{
    switch (touche)
    {
        case 'p': /* affichage du carre plein */
        {
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            glutPostRedisplay();
            break;
        }
        case 'f': /* affichage en mode fil de fer */
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glutPostRedisplay();
            break;
        }
        case 's' : /* Affichage en mode sommets seuls */
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            glutPostRedisplay();
            break;
        }
        case 'd':
        {
            glEnable(GL_DEPTH_TEST);
            glutPostRedisplay();
            break;
        }
        case 'D':
        {
            glDisable(GL_DEPTH_TEST);
            glutPostRedisplay();
            break;
        }
        case 'a'://Les faces à l'envers s'affichent en fil de fer
        {
            glPolygonMode(GL_FRONT, GL_FILL);
            glPolygonMode(GL_FRONT, GL_LINE);
            glutPostRedisplay();
            break;
        }
        case 'q' : /*la touche 'q' permet de quitter le programme */
        {
            exit(0);
        }
    }
}
void reshape(int x,int y)
{
    if (x<y)
        glViewport(0,(y-x)/2,x,x);
    else
        glViewport((x-y)/2,0,y,y);
}
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        presse = 1;
        xold = x;
        yold = y;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        presse = 0;
    }

    // Gestion de la molette : zoom avant et arrière
    if (button == 3) // Molette vers le haut (zoom avant)
    {
        zoomFactor += 0.02f;
        if (zoomFactor > 3.0f) // Limite de zoom avant
            zoomFactor = 3.0f;
        glutPostRedisplay();
    }
    else if (button == 4) // Molette vers le bas (zoom arrière)
    {
        zoomFactor -= 0.02f;
        if (zoomFactor < 0.1f) // Limite de zoom arrière
            zoomFactor = 0.1f;
        glutPostRedisplay();
    }
}
void mousemotion(int x,int y)
{
    if (presse) /* si le bouton gauche est presse */
    {
        /* on modifie les angles de rotation de l'objet
       en fonction de la position actuelle de la souris et de la derniere
       position sauvegardee */
        anglex=anglex+(x-xold);
        angley=angley+(y-yold);
        glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
    }

    xold=x; /* sauvegarde des valeurs courante de le position de la souris */
    yold=y;
}
void idle(){
    glutPostRedisplay();
}

//Main function
int main(int argc,char **argv)
{
    /* initialisation de glut et creation
       de la fenetre */
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(400,0);
    glutInitWindowSize(750,750);
    glutCreateWindow("Synthese d'Image");

    /* Initialisation d'OpenGL */
    glClearColor(0.9,0.9,0.9,1.0);
    glColor3f(1.0,1.0,1.0);
    glPointSize(6.0);
    glEnable(GL_DEPTH_TEST);

    /* enregistrement des fonctions de rappel */
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    glutMotionFunc(mousemotion);

//    loadTextures();

    /* Entree dans la boucle principale glut */
    glutMainLoop();
    return 0;
}
