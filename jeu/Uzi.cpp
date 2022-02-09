#include "Uzi.h"

#include "Vector3D.h"
#include "Zombie.h"

int Uzi::m_tourParTir = UZI_NBTOURPARTIR;

Uzi::Uzi() : Arme(0, UZI_DEGAT, UZI_NB_BALLEINIT) {}

bool Uzi::tir(std::vector<Zombie*>& z, Vector3D const& c, Vector3D const& d, int i, float distance_Mur)
{
	bool touche = 0, tue = 0;

	if (m_nbMunitions && (!(i % m_tourParTir)))
	{
		unsigned int k = 0;
		float alpha, beta;
		Vector3D perso_zombie(0, 1, 1);
		m_nbMunitions--;

		float distance_PersoZombie = 0;


		while (k < z.size() && !touche)
		{
			// Vecteur allant du personnage au zombie
			perso_zombie = Vector3D(c, z[k]->getCoord());

			// Si le zombie est deja mort ou si il y a un mur entre le zombie est le joueur
			if ((distance_PersoZombie = perso_zombie.length()) > distance_Mur)break;										// Quand on triera la liste il faudra mettre la condition dans le while

			alpha = atan((PERSO_X) / (2 * distance_PersoZombie * MUR_X)) * 57.29;

			// Normalisation du vecteur 
			perso_zombie.normalize();

			beta = acos(d.dot(perso_zombie)) * 57.29;//perso_zombie.getVx()*d.getVx() + perso_zombie.getVy()*d.getVy() + perso_zombie.getVz()*d.getVz());//d.dot(perso_zombie));	

			if (alpha >= beta)		//ATTENTION AU SIGNE
			{
				touche = true;
				z[k]->setTouche(touche);
				if (tue = z[k]->estAttaque(m_degats))
				{
					z.erase(z.begin() + k);
				}
			}
			k++;
		}

	}

	return tue;	// retourne 0 si aucun zombie touché / la distance négative si un zombie touché / la distance positive si un zombie tué

}


int Uzi::GetNbTourparTir()  const
{
	return m_tourParTir;
}

void Uzi::affichage(float x, float y, float z) const
{
	glPushMatrix();
	glScalef(0.2, 0.2, 0.2);
	glTranslatef(x, -y, z);
	//dessin UZI
	glTranslatef(0, 0, -10);
	dessiner_cube(0, 0.8, 1, 4.6, 0.3, 0.3, 0.3, 0);
	glTranslatef(0, -1.5, 0.9);
	dessiner_cube(0, 0.6, 2, 1.8, 0.4, 0.4, 0.4, 0);
	glTranslatef(0, -2.25, 0);
	dessiner_cube(0, 0.4, 2.5, 0.9, 0.4, 0.4, 0.4, 0);
	glTranslatef(0, 2.25, -1.35);
	dessiner_cube(0, 0.2, 0.2, 1.2, 0.4, 0.4, 0.4, 0);
	glTranslatef(0, 0.5, -0.75);
	dessiner_cube(0, 0.2, 1.2, 0.2, 0.4, 0.4, 0.4, 0);
	glRotatef(-20, 0, 0, 1);
	glTranslatef(0, 0.2, 0.6);
	dessiner_cube(0, 0.15, 0.7, 0.15, 0.4, 0.4, 0.4, 0);
	glRotatef(20, 0, 0, 1);
	glTranslatef(-0.35, 1.4, 2.45);
	dessiner_cube(0, 0.2, 0.2, 1, 0.4, 0.4, 0.4, 0);
	glTranslatef(0.55, 0, 0);
	dessiner_cube(0, 0.2, 0.2, 1, 0.4, 0.4, 0.4, 0);
	glTranslatef(-0.275, -0.075, -3);
	dessiner_cube(0, 0.15, 0.15, 0.3, 0.3, 0.3, 0.3, 0);
	glTranslatef(0, 0, -1);
	dessiner_cube(0, 0.15, 0.8, 0.15, 0.5, 0.5, 0.5, 0);
	glTranslatef(0, -0.5, -0.3);
	dessiner_cube(0, 0.4, 0.4, 0.2, 0.5, 0.5, 0.5, 0);
	glTranslatef(0, 0, -0.25);
	dessiner_cube(0, 0.2, 0.2, 0.3, 0.5, 0.5, 0.5, 0);
	glPopMatrix();
	glPopMatrix();

	//afficher les information de l'arme
	glLoadIdentity();
	gluLookAt(0, 0, 2, 0, 0, 1, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0, -1.0, 0.5f);
	glOrtho(0.0, windowW, 0.0, windowH, n, f);

	//afficher le nom de l'arme courante
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);  //RGBA values of text color
	glRasterPos2i(TEXTEX, TEXTEY - 2 * MARGINY);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)((Arme_string + "UZI").c_str()));

	//afficher le nombre de munition
	glRasterPos2i(TEXTEX, TEXTEY - 3 * MARGINY);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)((nbr_munition_string + to_string(m_nbMunitions)).c_str()));

	//afficher un message pas de munition quand le nombre de munition est à 0
	if (m_nbMunitions == 0)
	{
		glRasterPos2i(TEXTEX + MARGINX, TEXTEY - 2 * MARGINY);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)("PAS DE MUNITIONS"));
	}

	glPopMatrix();
}