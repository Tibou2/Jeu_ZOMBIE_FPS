#ifndef CETI_HEADER
#define CETI_HEADER

#include <Windows.h>

// Fichiers d'en-têtes pour OpenGL et GLUT
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/freeglut.h>
#define GL_GLEXT_PROTOTYPES
#endif

#include <stdio.h> 
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include "Vector3D.h"

// JPEG Lib
#include "jpeglib.h"
#include "jerror.h"


//              PERSONNAGE CONSTANTES           //
/*#define PERSO_X 2
#define PERSO_Y 5
#define PERSO_Z 1.8

#define BUSTE_X 2  //Y
#define BUSTE_Y 2  //Y
#define BUSTE_Z 2  //Y

#define JAMBE_X 2	//Y
#define JAMBE_Y 2	//Y
#define JAMBE_Z 2	//Y

#define TETE_X 2	//Y
#define TETE_Y 2	//Y
#define TETE_Z 2	//Y

#define BRAS_X 1	//Y
#define BRAS_Y 2	//Y
#define BRAS_Z 1	//Y*/

// PERSONNAGE CONSTANTES
#define PERSO_X 2
#define PERSO_Y 5
#define PERSO_Z 2	

#define BUSTE_X 1  //X
#define BUSTE_Y 2  //Y
#define BUSTE_Z 1  //Z

#define JAMBE_X 0.25	//X
#define JAMBE_Y 2.5		//Y
#define JAMBE_Z 0.25	//Z

#define TETE_X 0.5	//X
#define TETE_Y 0.5	//Y
#define TETE_Z 0.5	//Z

#define BRAS_X 0.25	//X
#define BRAS_Y 2.5	//Y
#define BRAS_Z 0.25	//Z



// CARTE CONSTANTES
#define CARTE_X 30
#define CARTE_Z 20

#define CARTE_Y 1

#define MUR_Y 8
#define MUR_X 2

#define PORTE_Y 2

#define ORIGINE 0

//POSITION ARME CONSTANTE
#define ARME_X 2
#define ARME_Y 2
#define ARME_Z 0

#define ZOMBIE_NBDEPLACEMENTPARTOUR 1
#define COEFFICIENT_DISTANCE_DEPLACEMENT 0.05

#define ZOMBIE_NBATTAQUEPARTOUR 20
#define ZOMBIE_DISTANCEATTAQUE 2

#define ZOMBIE_DISTANCE_CHANGEMENT_CAP 1
/////////////////////////////////////////////////


//              CARTE CONSTANTES            //

/*#define CARTE_X 30
#define CARTE_Z 20

#define CARTE_Y 2

#define MUR_Y 8
#define MUR_X 3

#define PORTE_Y 2

#define ORIGINE 0
/////////////////////////////////////////////////*/

//              ARME CONSTANTES            //

//PISTOL
#define PISTOL_DEGAT 20
#define PISTOL_NBTOURPARTIR 20

//UZI
#define UZI_DEGAT 20
#define UZI_NBTOURPARTIR 5
#define UZI_NB_BALLEINIT 100


//SHOTGUN
#define SHOTGUN_DEGAT 20
#define SHOTGUN_NBTOURPARTIR 20
#define SHOTGUN_NB_BALLEINIT 12
#define SHOTGUN_ANGLE 12
#define SHOTGUN_PORTEE 12


// General
#define ARMES_NB 3

/*#define ARME_X -2
#define ARME_Y -2
#define ARME_Z 0*/

/////////////////////////////////////////////////

//Position des textes
#define TEXTEX -580 //X
#define TEXTEY  580 //Y

#define MARGINY 30 //Marge selon Y
#define MARGINX 780 //Marge selon X


#define TEXTE_ARMEX 100 //X
#define TEXTE_ARMEY 280 //Y


/////////////////////////////////////////////////
//structure données carte
typedef struct checkPoint checkPoint;
struct checkPoint
{
    std::string id;
    std::vector<checkPoint*> autresCheckPoints;
    Vector3D coordonnees;
};
//structure de donner pour le personnage

//structure de donnée pour stocké les coordonnée des sommets d'un cube et de ses couleurs
typedef struct
{
    float x;
    float y;
    float z;
    float r;
    float g;
    float b;
} vertex;

//structure donnée pour stocker les coordonnées du texture
typedef struct {
    float s;
    float t;
} textureCoord;

//définir les sommets d'un cube de coté 1
extern vertex cube[8];
//face des cubes
extern int face[6][4];

//coordonne des texture s,t
extern textureCoord texture_Coord[6][4];

extern std::string Arme_string;
extern std::string nbr_munition_string;

// Taille de la fenêtre
extern int windowW;
extern int windowH;
extern float focale;
extern float n;
extern float f;

//on dessine un parallélipipede en fonction d'une largeur, longueur et profondeur
void dessiner_cube(GLuint texture, float longueur, float largeur, float profondeur, float r, float g, float b, int type, bool touche_ou_non = 0);

#endif