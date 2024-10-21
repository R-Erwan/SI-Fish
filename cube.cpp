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
#include "PrimitiveSphere.h"

// Keyboard and mouse interactions
char presse;
int anglex,angley,xold,yold;
float zoomFactor = 1.0f; //Var pour suivre le niveau de zoom avec la molette

//Primitive Objects
PrimitiveSphere pSphereBody = PrimitiveSphere(1,30,30);

//Images and Textures
std::vector<unsigned char> imageSoleil; GLuint t_soleil;

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

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,t_soleil);
    pSphereBody.draw();
    glDisable(GL_TEXTURE_2D);

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
