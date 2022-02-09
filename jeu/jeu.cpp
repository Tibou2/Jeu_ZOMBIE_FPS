//
//  main.cpp
//  ANREC_OGL_CubeTexture
//
//  Created by Jean-Marie Normand on 21/09/15.
//  Copyright (c) 2015 Centrale Innovation. All rights reserved.
//


// jeu.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

#include "ceti.h"

#include "Arme.h"
#include "Joueur.h"
#include "Zombie.h"
#include "Carte.h"
#include "Camera.h"

// Taille de la fenêtre
int windowW = 600;
int windowH = 480;
float focale = 65.0f;
float n = 0.1f;
float f = 250.0f;

int iter = 0;

float epsilon = 12;

//définir les sommets d'un cube de coté 1
vertex cube[8] = {
    {-0.5,-0.5,-0.5,0.76,0.69,0.56},
    {0.5,-0.5,-0.5,0.76,0.69,0.56},
    {0.5,0.5,-0.5,0.76,0.69,0.56},
    {-0.5,0.5,-0.5,0.76,0.69,0.56},
    {-0.5,0.5,0.5,0.76,0.69,0.56},
    {-0.5,-0.5,0.5,0.76,0.69,0.56},
    {0.5,-0.5,0.5,0.76,0.69,0.56},
    {0.5,0.5,0.5,0.76,0.69,0.56}
};

int face[6][4] = {
    {0,1,2,3},
    {3,4,7,2},
    {2,1,6,7},
    {7,4,5,6},
    {6,1,0,5},
    {5,4,3,0}
};

//coordonne des texture s,t
textureCoord texture_Coord[6][4] = {
   { {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f} }, // premiere face
   { {0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f} }, // seconde face
   { {0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f} }, // troisieme face
   { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} }, // quatrieme face
   { {0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f} }, // cinquieme face
   { {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f} } // sixieme face
};

std::string Arme_string = "ARME COURANTE : ";
std::string nbr_munition_string = "NOMBRE DE MUNITION : ";



// VARIABLES DES CLASSES PERSO/ARME/CARTE
Carte carte("map.txt");

int tir = -1; //-1 : tir pas/ 1 : commence a tirer / 2 : tir

// angle de rotation (coordonnees spheriques) pour calculer le vecteur vision de la camera, on ne prend pas en compte l'angle theta
//on se déplace suivant x et z et la rotation ne se fait que par rapport à y
float anglePhi = 0.0f;


// Camera viewing vectors
Vector3D forwardView;
Vector3D rightView;
// On garde le vecteur "up" du monde : 0 1 0


// "FPS" modes
Vector3D forwardMove;
Vector3D rightMove;

// Camera position
Vector3D camPos;
Vector3D targetPos;
Vector3D upWorld;
Camera cam;
Camera camFixe;

// Sensibilite de deplacement
float moveSensitivity;
float mouseRotSensitivity;


// increments de deplacement
// remis a 0 quand on appuis sur rien
float deltaMove = 0;
float deltaStrafe = 0.0f;

std::string nom;


// Déclarations des fonctions de rappel (callbacks)
GLvoid affichage();
GLvoid redimensionner(int w, int h);
GLvoid clavier(unsigned char key, int xx, int yy);
GLvoid clavierUp(unsigned char key, int x, int y);
GLvoid deplacementSouris(int x, int y);


// Déclaration d'autres fonctions
void dessiner_viseur();


// Callback de redimensionnement de la fenêtre
GLvoid redimensionner(int w, int h) {

    // On evite une division par 0
    // la fenetre ne peut avoir une largeur de 0
    if (h == 0)
        h = 1;

    // Calcul du ratio
    float ratio = (w * 1.0) / h;

    // On passe en mode "matrice de projection"
    glMatrixMode(GL_PROJECTION);

    // on charge la matrice identite
    glLoadIdentity();

    // on definit le viewport pour prendre toute la fenetre
    glViewport(0, 0, w, h);

    // on definit la projection perspective
    gluPerspective(65.0f, ratio, n, f);

    // on repasse en mode "matrice modelview"
    glMatrixMode(GL_MODELVIEW);

    //afficher le curseur en milieu de l'écran
    glutPostRedisplay();
    glutWarpPointer(w / 2, h / 2);
}
// Definition de la fonction d'affichage
GLvoid affichage()
{
    // On efface les tampons de couleur et de profondeur
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // On passe en matice modelview
    glMatrixMode(GL_MODELVIEW);

    if ((carte.getJoueur()->getArmes()[1]->getDispo() && (iter < 20)) || (carte.getJoueur()->getArmes()[2]->getDispo() && (iter < 40)))
    {
        //afficher un message au joueur pour lui dire qu'une nouvelle arme est débloqué
        //afficher les information de l'arme
        glLoadIdentity();
        gluLookAt(0, 0, 2, 0, 0, 1, 0, 1, 0);
        glPushMatrix();
        glTranslatef(0.0, 0.0, 0.5f);
        glOrtho(0.0, windowH, 0.0, windowH, n, f);

        //afficher le nom de l'arme courante
        glColor4f(1.0f, 1.0f, 1.0f, 0.5f);  //RGBA values of text color
        glRasterPos2i(TEXTE_ARMEX, TEXTE_ARMEY);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)("NOUVELLE ARME DISPONIBLE"));
        glPopMatrix();

        iter++;
    }

    //afficher un message au joueur pour qu'il sait quant est ce qu'il peut recharger son arme
    for (int i = 0; i < carte.getCaisse_munition().size(); i++)
    {
        if ((carte.getCaisse_munition()[i]->getDispo()) && ((carte.getJoueur()->getCoord() - carte.getCaisse_munition()[i]->getCoord()).length() <= epsilon) && (carte.getJoueur()->getArmes()[carte.getCaisse_munition()[i]->getType_munition() + 1]->getDispo()))
        {
            glLoadIdentity();
            gluLookAt(0, 0, 2, 0, 0, 1, 0, 1, 0);
            glPushMatrix();
            glTranslatef(0, 0.0, 0.5f);
            glOrtho(0.0, windowH, 0.0, windowH, n, f);

            //afficher le nom de l'arme courante
            glColor4f(1.0f, 1.0f, 1.0f, 0.5f);  //RGBA values of text color
            glRasterPos2i(TEXTE_ARMEX - 60, TEXTE_ARMEY);
            glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)("IL Y A DES MUNITIONS, RECHARGEZ VOTRE ARME !!"));

            if (carte.getJoueur()->getArme() != carte.getJoueur()->getArmes()[carte.getCaisse_munition()[i]->getType_munition() + 1])
            {
                glRasterPos2i(TEXTE_ARMEX - 40, TEXTE_ARMEY - 3 * MARGINY);
                glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)("ARME NON COMPATIBLE, CHANGEZ D'ARME !!"));
            }

            glPopMatrix();
        }
    }

    // on charge la matrice identite
    glLoadIdentity();

    camFixe.camLookAt();
    dessiner_viseur();
    carte.getJoueur()->getArme()->affichage(ARME_X, ARME_Y, ARME_Z);

    glLoadIdentity();
    camFixe.camLookAt();
    cam.cameraMovement(deltaMove, deltaStrafe, carte.getJoueur(), carte);
    cam.camLookAt();
    carte.Affichage();

    if (tir >= 0)
    {
        carte.attaque(tir);
    }


    glFlush();
    glutSwapBuffers();
}
// Fonction de gestion du clavier (touche enfoncee)
GLvoid clavier(unsigned char key, int xx, int yy) {
    unsigned int iterator1 = 0;
    // Quelle touchea ete appuyee ?
    switch (key) {
    case 'a':
    case 'A':
        tir = 0;
        break;
        //Q et S on strafe
    case 'q':
    case 'Q':
        deltaStrafe -= moveSensitivity;
        break;
    case 'd':
    case 'D':
        deltaStrafe += moveSensitivity;
        break;

        // Z et S avance/recule
    case 'z':
    case 'Z':
        deltaMove += moveSensitivity;
        break;
    case 's':
    case 'S':
        deltaMove -= moveSensitivity;
        break;
    case 32:
        carte.getJoueur()->changeArme(1);
        break;
    case 'r':
    case 'R':
        while (iterator1 < carte.getCaisse_munition().size())
        {
            if ((carte.getCaisse_munition()[iterator1]->getDispo()) && ((carte.getJoueur()->getCoord() - carte.getCaisse_munition()[iterator1]->getCoord()).length() <= epsilon) && (carte.getJoueur()->getArmes()[carte.getCaisse_munition()[iterator1]->getType_munition() + 1]->getDispo()))
            {
                if (carte.getJoueur()->getArme() == carte.getJoueur()->getArmes()[carte.getCaisse_munition()[iterator1]->getType_munition() + 1])
                {
                    carte.getJoueur()->recharge(carte.getCaisse_munition()[iterator1]->getNb_Munition());
                    carte.getCaisse_munition()[iterator1]->setDispo(0);
                }
            }
            iterator1++;
        }
        break;
        // ESCAPE on termine l'application
    case 27:
        exit(0);
        break;
    }
}
// Fonction de gestion du clavier (touche relachee)
GLvoid clavierUp(unsigned char key, int x, int y) {

    // Que faire uand une touche est relachee
    switch (key) {

        // On arrete de strafer
    case 'q':
    case 'd':
    case 'Q':
    case 'D':
    case 'A':
    case'a':
        tir = -1;
        deltaStrafe = 0;
        break;

        // On arrete d'avance/reculer
    case 'z':
    case 's':
    case 'Z':
    case 'S':
        deltaMove = 0;
        break;
    }
}
GLvoid deplacementSouris(int x, int y)
{
    cam.deplacementSouris(x, y, carte.getJoueur());
}

// Affichage plein écran
void draw()
{
    // code for rendering here
    glutSwapBuffers();   // swapping image buffer for double buffering
    glutPostRedisplay(); // redrawing. Omit this line if you don't want constant redraw
}

int main(int argc, char* argv[])
{
    // Initialisation de GLUT
    glutInit(&argc, argv);
    // Choix du mode d'affichage (ici RVB)
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    // Position initiale de la fenetre GLUT
    glutInitWindowPosition(200, 200);
    // Taille initiale de la fenetre GLUT
    glutInitWindowSize(windowW, windowH);
    // Creation de la fenetre GLUT
    glutCreateWindow("environnement jeu");
    //glutFullScreen();

    // Définition de la couleur d'effacement du framebuffer
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutSetCursor(GLUT_CURSOR_NONE);

    // on active le tampon de profondeur
    glEnable(GL_DEPTH_TEST);

    // Définition des fonctions de callbacks
    glutDisplayFunc(affichage);
    glutReshapeFunc(redimensionner);
    glutIdleFunc(affichage);

    // pour que l'on puisse rester appuye sur les touches
    glutIgnoreKeyRepeat(1);

    // Declaration des callbacks clavier
    glutKeyboardFunc(clavier);
    glutKeyboardUpFunc(clavierUp);

    // declarationdes callbacks souris
    glutPassiveMotionFunc(deplacementSouris);

    // on initialise la position de la camera
    camPos = carte.getJoueur()->getCoord() + Vector3D(0, PERSO_Y, 0);

    // on initialise les vecteurs 'view'
    forwardView = Vector3D(1, 0, 0);

    upWorld = Vector3D(0, 1, 0);
    rightView = Vector3D(1, 0, 0);

    // Pour le FPS mode
    forwardMove = Vector3D(0, 0, -1);
    rightMove = Vector3D(1, 0, 0);

    moveSensitivity = 0.7;

    cam = Camera(camPos, forwardView, rightView, upWorld, anglePhi);
    camFixe = Camera(Vector3D(0, 0, 0.5), Vector3D(0, 0, -1), rightView, upWorld, 0.0f);

    // Lancement de la boucle infinie GLUT
    glutMainLoop();

    return 0;
}



//on dessine un parallélipipede en fonction d'une largeur, longueur et profondeur
void dessiner_cube(GLuint texture, float longueur, float largeur, float profondeur, float r, float g, float b, int type, bool touche_ou_non)
{
    if (!touche_ou_non)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    for (int i = 0; i < 6; i++)
    {
        glBegin(GL_POLYGON);
        for (int j = 0; j < 4; j++)
        {
            // enabling blend
            glEnable(GL_BLEND);
            if (type == 0)
            {
                glColor3f(r, g, b);
            }
            else if (type == 1 || type == 2)
            {
                glColor3f(cube[face[i][j]].r, cube[face[i][j]].g, cube[face[i][j]].b);
            }
            // Texture
            glTexCoord2d(texture_Coord[i][j].s, texture_Coord[i][j].t);
            glVertex3f(longueur * cube[face[i][j]].x, largeur * cube[face[i][j]].y, profondeur * cube[face[i][j]].z);
        }
        glEnd();
    }

    glDisable(GL_TEXTURE_2D);
}

void dessiner_viseur()
{
    glPushMatrix();
    glScalef(0.005, 0.005, 0.005);
    glTranslatef(0, -1.5, 0);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    for (float i = 0; i <= 2 * 3.14 + 0.1; i += 0.1)
    {
        glVertex3f(sin(i) * 1, 1 + cos(i) * 1, 0.0f);
    }
    glEnd();
    glPopMatrix();
}