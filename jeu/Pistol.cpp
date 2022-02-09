#include "Pistol.h"

#include "Vector3D.h"
#include "Zombie.h"

int Pistol::m_tourParTir = PISTOL_NBTOURPARTIR;

Pistol::Pistol() : Arme(1, PISTOL_DEGAT, 1) {}

bool Pistol::tir(std::vector<Zombie*>& z, Vector3D const& c, Vector3D const& d, int i, float distance_Mur)
{
	bool touche = 0, tue = 0;

	if ((i % m_tourParTir) || i == -1) return tue;


	unsigned int k = 0;
	float alpha, beta;
	Vector3D perso_zombie(0, 1, 1);
	float distance_PersoZombie = 0;

	while (k < z.size() && !touche)	// actuellement touche ne sert a rien mais il faudra utiliser la methode sur une liste triée de zombie, et là elle nous servira
	{
		// Vecteur allant du personnage au zombie
		perso_zombie = Vector3D(c, z[k]->getCoord());

		// Si le zombie est deja mort ou si il y a un mur entre le zombie et le joueur
		if ((distance_PersoZombie = perso_zombie.length()) > distance_Mur)break;											// Quand on triera la liste il faudra mettre la condition dans le while
		//Angle CentreZombie/Perso/ExtremiteZombie
		alpha = atan((PERSO_X) / (2 * distance_PersoZombie * MUR_X)) * 57.29;
		// Normalisation du vecteur 
		perso_zombie.normalize();
		// Calcul angle direction joueur et joueur_zombie
		beta = acos(d.dot(perso_zombie)) * 57.29;//perso_zombie.getVx()*d.getVx() + perso_zombie.getVy()*d.getVy() + perso_zombie.getVz()*d.getVz());//d.dot(perso_zombie));	
		// Si zombie actuel est dans la ligne de tire
		if (alpha >= beta)	// Si zombie dans ligne de tire et zombie plus proche que le zombie courant
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

	return tue;	// retourne 0 si aucun zombie touché / la distance négative si un zombie touché / la distance positive si un zombie tué
}

void Pistol::affichage(float x, float y, float z) const
{
	glPushMatrix();
	glScalef(0.2, 0.2, 0.2);
	glTranslatef(x, -y, z);
	//dessiner pistol
	glPushMatrix();
	glTranslatef(0, 0, -10);
	dessiner_cube(0, 0.8, 1, 4.6, 0.5, 0.5, 0.5, 0);
	glTranslatef(0, -0.7, 1.5);
	dessiner_cube(0, 0.8, 0.4, 1.2, 0.6, 0.6, 0.6, 0);
	glTranslatef(0, -0.5, 0.2);
	dessiner_cube(0, 0.8, 0.6, 1.2, 0.7, 0.7, 0.7, 0);
	glTranslatef(0, -0.7, 0.2);
	dessiner_cube(0, 0.8, 0.8, 1.2, 0.7, 0.7, 0.7, 0);
	glTranslatef(0, -0.5, 0);
	dessiner_cube(0, 0.8, 0.2, 1, 0.5, 0.5, 0.5, 0);
	glTranslatef(0, 1, -1.3);
	dessiner_cube(0, 0.4, 0.2, 1.2, 0.8, 0.8, 0.8, 0);
	glTranslatef(0, 0.4, -0.7);
	dessiner_cube(0, 0.4, 1, 0.2, 0.8, 0.8, 0.8, 0);
	glTranslatef(0, 0.2, 0.6);
	dessiner_cube(0, 0.4, 0.6, 0.2, 1, 1, 1, 0);
	glTranslatef(0, -0.2, -0.2);
	dessiner_cube(0, 0.4, 0.2, 0.2, 1, 1, 1, 0);
	glTranslatef(0, 0.6, 2);
	dessiner_cube(0, 0.4, 0.2, 0.2, 0.5, 0.5, 0.5, 0);
	glTranslatef(0, 1, -0.6);
	dessiner_cube(0, 0.4, 0.2, 0.2, 1, 1, 1, 0);
	glTranslatef(0, 0, -4);
	dessiner_cube(0, 0.4, 0.2, 0.2, 0.5, 0.5, 0.5, 0);
	glTranslatef(0, -0.2, -0.2);
	dessiner_cube(0, 0.4, 0.2, 0.2, 0.5, 0.5, 0.5, 0);
	glTranslatef(0, -0.6, 0);
	dessiner_cube(0, 0.4, 0.2, 0.2, 0.5, 0.5, 0.5, 0);
	glTranslatef(0.2, 0.3, 0);
	dessiner_cube(0, 0.2, 0.4, 0.2, 0.5, 0.5, 0.5, 0);
	glTranslatef(-0.4, 0, 0);
	dessiner_cube(0, 0.2, 0.4, 0.2, 0.5, 0.5, 0.5, 0);
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
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)((Arme_string + "PISTOL").c_str()));

	glPopMatrix();
}


int Pistol::GetNbTourparTir() const
{
	return m_tourParTir;
}


/////// A COPIER DANS LES AUTRES ARMES QUAND FINIT
