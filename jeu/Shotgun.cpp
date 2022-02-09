#include "Shotgun.h"

#include "Vector3D.h"
#include "Zombie.h"


int Shotgun::m_tourParTir = SHOTGUN_NBTOURPARTIR;

Shotgun::Shotgun() : Arme(0, SHOTGUN_DEGAT, SHOTGUN_NB_BALLEINIT), m_portee(SHOTGUN_PORTEE) {}


bool Shotgun::tir(std::vector<Zombie*>& z, Vector3D const& c, Vector3D const& d, int i, float distance_Mur)
{
	bool tue = 0;
	if (m_nbMunitions && (!(i % m_tourParTir)))
	{
		cout << "dans la boucle" << endl;
		unsigned int k = 0, touche = 0;
		float alpha, beta[3];
		Vector3D perso_zombie(0, 1, 1);
		Vector3D directionBalle(0, 1, 1);
		float distance_PersoZombie = 0;
		m_nbMunitions = m_nbMunitions - 3;

		bool touches[3] = { 0,0,0 };


		while (k < z.size() && touche < 3)
		{
			// Vecteur allant du personnage au zombie
			perso_zombie = Vector3D(c, z[k]->getCoord());

			// Si le zombie est deja mort ou si il y a un mur entre le zombie est le joueur
			if ((distance_PersoZombie = perso_zombie.length()) > distance_Mur || (distance_PersoZombie > m_portee))break;											// Quand on triera la liste il faudra mettre la condition dans le while

			alpha = atan(PERSO_X / (2 * distance_PersoZombie)) * 57.29;	//Angle CentreZombie/Perso/ExtremiteZombie    		//Non prise en compte de la direction du zombie
			perso_zombie.normalize();

			for (int l = -1; l <= 1; l++)
			{
				if (touches[l + 1])continue;
				//directionBalle = d.rotation(l * SHOTGUN_ANGLE);
				beta[l + 1] = (acos(d.dot(perso_zombie)) * 57.29) + SHOTGUN_ANGLE * l;//perso_zombie.getVx()*d.getVx() + perso_zombie.getVy()*d.getVy() + perso_zombie.getVz()*d.getVz());//d.dot(perso_zombie));	

				if (alpha >= beta[l + 1])		//ATTENTION AU SIGNE
				{
					cout << "touche avec la balle " << l << endl;
					touches[l + 1] = true;
					touche++;
					z[k]->setTouche(1);
					if (z[k]->estAttaque(m_degats))
					{
						tue = 1;
						z.erase(z.begin() + k);
						k--;
						break;
					}
				}
			}
			k++;
		}
	}

	return tue;
}


void Shotgun::affichage(float x, float y, float z) const
{
	glPushMatrix();
	glScalef(0.2, 0.2, 0.2);
	glTranslatef(x, -y, z);
	//dessiner shotgun
	glPushMatrix();
	glTranslatef(0, 0, -10);
	dessiner_cube(0, 1, 0.5, 7, 0.3, 0.3, 0.3, 0);
	glTranslatef(0, -0.5, 0.25);
	dessiner_cube(0, 1, 0.5, 6.5, 0.3, 0.3, 0.3, 0);
	glTranslatef(0, -0.35, -1);
	dessiner_cube(0, 1.8, 0.8, 1.5, 0.54, 0.27, 0.074, 0);
	glTranslatef(0, 0, 4.05);
	dessiner_cube(0, 0.3, 0.3, 0.3, 0, 0, 0, 0, 0);
	glTranslatef(0, -0.3, -0.45);
	dessiner_cube(0, 0.3, 0.3, 0.6, 0.2, 0.2, 0.2, 0);
	glTranslatef(0, 0.3, -0.45);
	dessiner_cube(0, 0.3, 0.3, 0.3, 0.2, 0.2, 0.2, 0);
	glTranslatef(0, 0, 0.6);
	dessiner_cube(0, 0.3, 0.3, 0.3, 0.8, 0.8, 0.8, 0);
	glTranslatef(0, 0.4, 0.55);
	dessiner_cube(0, 1, 0.6, 0.2, 0.54, 0.27, 0.074, 0);
	glTranslatef(0, -0.1, 0.225);
	dessiner_cube(0, 1, 0.4, 0.2, 0.54, 0.27, 0.074, 0);
	glTranslatef(0, -0.2, 0.3);
	dessiner_cube(0, 1, 0.4, 0.4, 0.54, 0.27, 0.074, 0);
	glTranslatef(0, 0.05, 0.35);
	dessiner_cube(0, 1, 0.5, 0.3, 0.54, 0.27, 0.074, 0);
	glTranslatef(0, -0.05, 0.525);
	dessiner_cube(0, 1, 0.6, 0.8, 0.54, 0.27, 0.074, 0);
	glTranslatef(0, 1.05, -6.85);
	dessiner_cube(0, 1.5, 0.1, 0.2, 0.2, 0.2, 0.2, 0);
	glTranslatef(0.7, 0.15, 0);
	dessiner_cube(0, 0.1, 0.2, 0.2, 0.2, 0.2, 0.2, 0);
	glTranslatef(-1.4, 0, 0);
	dessiner_cube(0, 0.1, 0.2, 0.2, 0.2, 0.2, 0.2, 0);
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
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)((Arme_string + "SHOTGUN").c_str()));

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

int Shotgun::GetNbTourparTir()  const
{
	return m_tourParTir;
}
