#include "Personnage.h"
#include "LoadTexture.h"
#include "Carte.h"


Personnage::Personnage(Vector3D c, Vector3D d) : m_vie(100), m_coord(c), m_direction(d), m_touche(0) {
}


bool Personnage::estAttaque(int degats) { return ((m_vie -= degats) <= 0); } 		// 1 si mort du Personnage


int Personnage::getPdv() const { return m_vie; }
Vector3D Personnage::getCoord() const { return m_coord; }
Vector3D Personnage::getDirection() const { return m_direction; }
bool Personnage::getTouche() const { return m_touche; }

void Personnage::setCoord(Vector3D v)
{
    m_coord = v;
}

void Personnage::setDirection(Vector3D v)
{
    m_direction = v;
}

void Personnage::setTouche(bool newTouche)
{
    m_touche = newTouche;
}

void Personnage::dessiner(int joueur_ou_zombie)
{
    float angle = asin(abs(m_direction.getVz())) * 180 / 3.14;
    float anglefinal = 0.0f;//angle du rotation du personnage par rapport à y
    //on fait des conditions pour savoir si l'angle est entre 0 et pi ou pi et 2*pi, 
    //la fct asin renvoie des valeur entre 0 et pi mais nou voulons des valeur entre 0 et 2*pi 
    //pour ca il faut savoir les signes des coordonnées x et z de la nouvemme direction et chnager l'angle en fonction de la signe
    if (m_direction.getVz() <= 0)
    {
        if (m_direction.getVx() >= 0)
        {
            anglefinal = 360.0f - angle;
        }
        else
        {
            anglefinal = 180.0f + angle;
        }
    }
    else
    {
        if (m_direction.getVx() >= 0)
        {
            anglefinal = angle;
        }
        else
        {
            anglefinal = 180.0f - angle;
        }
    }
    glPushMatrix();
    glTranslatef(m_coord.getVx(), m_coord.getVy(), m_coord.getVz());
    glRotatef(-anglefinal, 0, 1, 0);
    dessiner_personnage(joueur_ou_zombie, m_touche);
    glPopMatrix();
}

//on dessine un personnage en (0,0,0) et dans l'affichage on le fait translater vers sa position correcte
//ou on l'effectue une rotation selon sa direction
void dessiner_personnage(int joueur_ou_zombie, bool touche_ou_non)
{
    glPushMatrix();
    //faire une rotation de 90 degrée pour que le joueur soit dans la même direction que la caméra, on voit ses mains dans le bon sens
    glRotatef(90, 0, 1, 0);
    //dessiner la tête
    if (joueur_ou_zombie == 4)
    {
        GLuint tete = LoadTexture::LoadTextureImagFile("texture_zombie\\visage.jpg", 0);
        glPushMatrix();
        glTranslatef(0, PERSO_Y - TETE_Y / 2, 0);
        dessiner_cube(tete, TETE_X, TETE_Y, TETE_Z, 1, 0, 0, 0, touche_ou_non);
        glPopMatrix();
        LoadTexture::FreeCreatedTexture(tete);
    }

    //dessiner la ventre
    GLuint ventre = LoadTexture::LoadTextureImagFile("texture_zombie\\ventre.jpg", 0);
    glPushMatrix();
    glTranslatef(0, PERSO_Y - TETE_Y - BUSTE_Y / 2, 0);
    dessiner_cube(ventre, BUSTE_X, BUSTE_Y, BUSTE_Z, 1, 0, 0, 0, touche_ou_non);
    glPopMatrix();
    LoadTexture::FreeCreatedTexture(ventre);

    //dessiner les bras
    GLuint bras = LoadTexture::LoadTextureImagFile("texture_zombie\\bras.jpg", 0);
    glPushMatrix();//premier bras
    glTranslatef((-BUSTE_X - BRAS_X) / 2, 1 + PERSO_Y - TETE_Y - BRAS_Y / 2, BUSTE_Z);
    glRotatef(90, 1, 0, 0);
    dessiner_cube(bras, BRAS_X, BRAS_Y, BRAS_Z, 1, 0, 0, 0, touche_ou_non);
    glPopMatrix();
    glPushMatrix();//deuxième bras
    glTranslatef((BUSTE_X + BRAS_X) / 2, 1 + PERSO_Y - TETE_Y - BRAS_Y / 2, BUSTE_Z);
    glRotatef(90, 1, 0, 0);
    dessiner_cube(bras, BRAS_X, BRAS_Y, BRAS_Z, 1, 0, 0, 0, touche_ou_non);
    glPopMatrix();
    LoadTexture::FreeCreatedTexture(bras);

    //dessiner les jombes
    GLuint jombe = LoadTexture::LoadTextureImagFile("texture_zombie\\jombe.jpg", 0);
    glPushMatrix();//premiere jombe
    glTranslatef((-BUSTE_X + JAMBE_X) / 2 + JAMBE_X / 2, PERSO_Y - TETE_Y - BUSTE_Y - JAMBE_Y / 2, 0);
    dessiner_cube(jombe, JAMBE_X, JAMBE_Y, JAMBE_Z, 1, 0, 0, 0, touche_ou_non);
    glTranslatef(BUSTE_X - JAMBE_X - JAMBE_X, 0, 0);// deuxièle jombe
    dessiner_cube(jombe, JAMBE_X, JAMBE_Y, JAMBE_Z, 1, 0, 0, 0, touche_ou_non);
    glPopMatrix();
    glPopMatrix();
    LoadTexture::FreeCreatedTexture(jombe);

}