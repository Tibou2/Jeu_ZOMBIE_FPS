#include "Carte.h"

#include "Zombie.h"
#include "Joueur.h"
#include "Vector3D.h"
#include "LoadTexture.h"

enum {
	RIEN,
	MUR,
	PORTE,
	JOUEUR,
	ZOMBIE
};

std::string Point_de_vie = "POINT DE VIE : ";
std::string Score_string = "SCORE : ";

Carte::Carte(std::string nfichier) // Les premieres nombres dans fichier texte sont le nombre de ligne et le nombre de colonne		m_carte[ligne_ou_z][colonne_ou_x]
{
	std::ifstream flux(nfichier);
	std::vector<std::string> cps;
	int indexCp = 0;

	if (flux)
	{
		int nbL, nbC;
		string f;
		std::vector<int> ligne;

		flux >> f; nbL = stoi(f);
		flux >> f; nbC = stoi(f);
		flux >> f; indexCp = stoi(f);

		for (int i = 0; i < nbL; i++)
		{
			for (int j = 0; j < nbC; j++)
			{
				flux >> f;
				if (f.size() == 1)
				{
					if (stoi(f) < 3)ligne.push_back(stoi(f));
					else if (stoi(f) == 3) { m_joueur = new Joueur("j1", Vector3D(i * MUR_X, 0, j * MUR_X), Vector3D(1, 0, 0)); ligne.push_back(0); }
					else if (stoi(f) == 4) { m_zombies.push_back(new Zombie(Vector3D(i * MUR_X, 0, j * MUR_X), Vector3D(1, 0, 0))); ligne.push_back(0); }
				}
				else
				{
					//On enregistre le checkpoint
					cps.push_back(f + "-" + std::to_string(i) + "/" + std::to_string(j));
					ligne.push_back(2);
				}
			}
			m_carte.push_back(ligne);
			ligne.clear();
		}
	}
	else { std::cout << "Erreur de lecture de fichier carte" << std::endl; }


	extractCheckPoints(cps);

	for (unsigned int i = 0; i < m_zombies.size(); i++)
	{
		m_zombies[i]->setCp(&m_checkPoints[indexCp]);
	}
}


/*
											FONCTION extractCheckPoints
Description :
recuperer et lier les checkpoints a partir de la liste de chaine de caractere resultant de la lecture de la carte
*/
void Carte::extractCheckPoints(std::vector<std::string> cps)
{
	unsigned int i, j;
	checkPoint cp;
	string str, coords;
	double x, z;

	i = 0;
	while (!cps.empty())
	{
		for (j = 0; j < cps.size(); j++)
		{
			if (cps[j][0] - '0' == i)
			{
				cp.id = cps[j];
				m_checkPoints.push_back(cp);
				cps.erase(cps.begin() + j);
				break;
			}
		}
		i++;
	}

	for (i = 0; i < m_checkPoints.size(); i++)
	{
		str = m_checkPoints[i].id;
		m_checkPoints[i].id = str[0];

		coords = str.substr(str.find('-') + 1, str.size());

		x = atof(coords.substr(0, coords.find('/')).c_str()) * MUR_X;
		z = atof(coords.substr(coords.find('/') + 1, coords.size()).c_str()) * MUR_X;

		str.erase(str.find('-'), str.size());

		m_checkPoints[i].coordonnees = Vector3D(x, 0, z);


		for (j = 1; j < str.size(); j++)
		{
			if (str[j] == '1')
			{
				m_checkPoints[i].autresCheckPoints.push_back(&m_checkPoints[j - 1]);
			}
		}
	}

}

void Carte::Affichage()const
{
	static unsigned int i = 0;
	GLuint Sol = LoadTexture::LoadTextureImagFile("texture_carte\\sol.jpg", 0);
	GLuint Mur = LoadTexture::LoadTextureImagFile("texture_carte\\mur.jpg", 0);
	GLuint Plafond = LoadTexture::LoadTextureImagFile("texture_carte\\plafond.jpg", 0);

	// AFFICHAGE DU SOL
	glPushMatrix();
	glTranslatef((m_carte[0].size() / 2) * MUR_X, -CARTE_Y / 2, (m_carte.size() / 2) * MUR_X);
	dessiner_cube(Sol, m_carte.size() * MUR_X, CARTE_Y, m_carte.size() * MUR_X, 1, 1, 0, MUR);
	// AFFICHAGE DU PLAFOND
	glTranslatef(0, MUR_Y, 0);
	dessiner_cube(Plafond, m_carte[0].size() * MUR_X, CARTE_Y, m_carte.size() * MUR_X, 1, 1, 0, MUR);
	glPopMatrix();
	LoadTexture::FreeCreatedTexture(Sol);
	LoadTexture::FreeCreatedTexture(Plafond);

	// MURS et PORTES
	for (unsigned int i = 0; i < m_carte.size(); i++)												//IL FAUDRA D'AUTRES VALEURS POUR SIGNALER OU PEUT APPARAITRE LE JOUEUR ET LES ZOMBIES
	{
		for (unsigned int j = 0; j < m_carte[i].size(); j++)
		{
			if (m_carte[i][j] == 1)															//1 pour Murs
			{
				glPushMatrix();
				glTranslatef(MUR_X / 2 + j * MUR_X, MUR_Y / 2, MUR_X / 2 + i * MUR_X);
				dessiner_cube(Mur, MUR_X, MUR_Y, MUR_X, 0, 1, 0, MUR);
				glPopMatrix();
			}
			else if (m_carte[i][j] == 2 || m_carte[i][j] == 'a')														//2 pour porte
			{
				glPushMatrix();
				glTranslatef(MUR_X / 2 + j * MUR_X, MUR_Y - PORTE_Y / 2, MUR_X / 2 + i * MUR_X);
				dessiner_cube(Mur, MUR_X, PORTE_Y, MUR_X, 1, 1, 0, PORTE);
				glPopMatrix();
			}
		}
	}

	LoadTexture::FreeCreatedTexture(Mur);

	//affichage du joueur et des zombie

	m_joueur->dessiner(JOUEUR);

	for (int i = 0; i < m_caisse_munition.size(); i++)
	{
		if (m_caisse_munition[i]->getDispo())
		{
			m_caisse_munition[i]->affichage();
		}
	}

	Vector3D zombie_perso;
	Vector3D positionCible;
	float distanceZombieMur = 1000;

	for (unsigned int j = 0; j < m_zombies.size(); j++)
	{
		if (m_zombies[j]->getPdv() > 0)
		{
			if (!(i % ZOMBIE_NBDEPLACEMENTPARTOUR))
			{
				// On test d'abord si le zombie peut voir le joueur en regardant s'il ya un mur entre les deux
				zombie_perso = Vector3D(m_zombies[j]->getCoord(), m_joueur->getCoord());
				distanceZombieMur = MurEntreZombieEtJoueur(m_zombies[j]->getCoord(), zombie_perso);
				if (((distanceZombieMur < zombie_perso.length()) ? m_zombies[j]->seDeplace(0) : m_zombies[j]->seDeplace(1, m_joueur)))exit(0);
			}
			m_zombies[j]->dessiner(ZOMBIE);
			m_zombies[j]->setTouche(0);
		}

	}
	i++;

	//affichage des information du jeu
	glLoadIdentity();
	gluLookAt(0, 0, 2, 0, 0, 1, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0, -1.0, 0.5f);
	glOrtho(0.0, windowW, 0.0, windowH, n, f);

	//afiicher les points de vie
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);  //RGBA values of text color
	glRasterPos2i(TEXTEX, TEXTEY);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)((Point_de_vie + to_string(m_joueur->getPdv())).c_str()));

	//afficher le score
	glRasterPos2i(TEXTEX, TEXTEY - MARGINY);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)((Score_string + to_string(m_joueur->getScore())).c_str()));

	//afficher un message au joueur qu'il y a des caisse de munitions disponibles
	for (int i = 0; i < m_caisse_munition.size(); i++)
	{
		if (m_caisse_munition[i]->getDispo())
		{
			//afficher le nom de l'arme courante
			glTranslatef(0, 1.0, 0.0f);
			glRasterPos2i(TEXTE_ARMEX, TEXTE_ARMEY + 10 * MARGINY);
			glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)("CAISSES DE MUNITION DISPONIBLE"));
		}
	}

	glPopMatrix();

}




bool Carte::attaque(int& i)
{
	bool tuer = 0;
	int x, z;
	if (!m_zombies.empty())
	{
		float distanceJoueur_Mur;
		cout << m_zombies.size() << endl;
		//On cherche le mur le plus proche dans la ligne de mire
		distanceJoueur_Mur = MurEntreZombieEtJoueur(m_joueur->getCoord(), m_joueur->getDirection());
		if (!distanceJoueur_Mur)distanceJoueur_Mur = 2000;
		// On trie les zombies du plus pres au plus loin
		triZombies();
		// On appelle la fonction d'attaque qui va se gérer
		tuer = m_joueur->Attaque(m_zombies, i, distanceJoueur_Mur);
		i++;
	}
	if (tuer && m_joueur->getScore() % 400 == 0)
	{
		srand((unsigned int)time(0));
		int type_munition = rand() % 2;
		int nbr_munition;
		if (type_munition == 0)
		{
			nbr_munition = UZI_NB_BALLEINIT;
		}
		else
		{
			nbr_munition = SHOTGUN_NB_BALLEINIT;
		}
		do
		{
			x = rand() % (m_carte[0].size());
			z = rand() % (m_carte.size());
		} while (m_carte[x][z] == MUR);
		m_caisse_munition.push_back(new Caisse_munition(type_munition, nbr_munition, Vector3D(x, 0, z), 1));
	}
	return tuer;
}

/*
											FONCTION triZombies
Description :
Tri les zombies du plus proche au plus eloigné avec la methode du tri a bulle
*/
void Carte::triZombies()
{
	unsigned i;
	bool inversion;
	Zombie* zombie;

	do
	{
		inversion = 0;

		for (i = 0; i < m_zombies.size() - 1; i++)
		{
			if (Vector3D(m_zombies[i]->getCoord(), m_joueur->getCoord()).length() > Vector3D(m_zombies[i + 1]->getCoord(), m_joueur->getCoord()).length())
			{
				zombie = m_zombies[i];
				m_zombies[i] = m_zombies[i + 1];
				m_zombies[i + 1] = zombie;
				inversion = 1;
			}
		}
	} while (inversion);
}

/*
											FONCTION MurEntreZombieEtJoueur
Description :
Cette fonction renvoit la distance jusqu'au mur le plus proche.
*/
float Carte::MurEntreZombieEtJoueur(Vector3D position, Vector3D direction) const//A appeler initialement avec la position du joueur
{
	direction.normalize();
	const double& ux = direction.getVx();		//u est une reference vers la x du vecteur directeur du joueur (c'est pour faciliter la lecture/ecriture)
	const double& uz = direction.getVz();		//u est une reference vers la z du vecteur directeur du joueur (c'est pour faciliter la lecture/ecriture)

	const double& Ax = position.getVx();		//u est une reference vers la x du vecteur directeur du joueur (c'est pour faciliter la lecture/ecriture)
	const double& Az = position.getVz();		//u est une reference vers la z du vecteur directeur du joueur (c'est pour faciliter la lecture/ecriture)

	Vector3D intersectionAvecLigneVerticale, intersectionAvecLigneHorizontale;
	int ligneHorizontal, ligneVertical;
	float distanceALaLigneVerticale = (ux == 0), distanceALaLigneHorizontale = (uz == 0), distanceMur = 0;


	// On cherche les prochaines lignes horizontales et verticale dans le sens de la direction du joueur
	ligneHorizontal = floor(Ax / MUR_X) + (uz > 0);
	ligneVertical = floor(Az / MUR_X) + (ux > 0);

	// Tant qu'on pas trouvé le mur
	while (!distanceMur)// && (ligneVertical + ((ux > 0) * 2 - 1)  >-1) && (ligneHorizontal + ((uz > 0) * 2 - 1) >-1) && (ligneHorizontal+((uz > 0) * 2 - 1) <m_carte.size()) && (ligneVertical + ((ux > 0) * 2 - 1) < m_carte[0].size()))
	{



		// On recherche l'intersection et on calcule la distance du joueur a ces intersections
		if (!distanceALaLigneVerticale)
		{
			intersectionAvecLigneVerticale = IntersectionDroites(direction, position, 1, ligneVertical * MUR_X);
			distanceALaLigneVerticale = Vector3D(position, intersectionAvecLigneVerticale).length();
		}
		if (!distanceALaLigneHorizontale)
		{
			intersectionAvecLigneHorizontale = IntersectionDroites(direction, position, 0, ligneHorizontal * MUR_X);
			distanceALaLigneHorizontale = Vector3D(position, intersectionAvecLigneHorizontale).length();
		}

		// On cherche quelle distance est la plus proche et on regarde s'il y a un mur à cet endroit
		if (distanceALaLigneVerticale * (uz != 0) < distanceALaLigneHorizontale * (ux != 0))
		{
			// Cette méthode marche presque toujours bien, mais afin de parer un bug qu'on a pas réussi a résoudre on doit rajouter cette condition (de meme quelques lignes plus tard)
			if (ligneHorizontal - (ux < 0) < 0 || ligneHorizontal - (ux < 0) > m_carte.size() || ligneVertical - (ux < 0) < 0 || ligneVertical - (ux < 0) > m_carte[0].size()) return 1000;
			distanceMur = distanceALaLigneVerticale * (m_carte[ligneHorizontal - (ux < 0)][ligneVertical - (ux < 0)] == MUR);		// -1 ??
			ligneVertical += ((ux > 0) * 2 - 1);
			distanceALaLigneVerticale = 0;
		}
		else
		{
			//quelques lignes plus tard
			if (ligneHorizontal - (ux > 0) < 0 || ligneHorizontal - (ux > 0) > m_carte.size() || ligneVertical - (ux > 0) < 0 || ligneVertical - (ux > 0) > m_carte.size()) return 1000;
			distanceMur = distanceALaLigneHorizontale * (m_carte[ligneHorizontal - (ux > 0)][ligneVertical - (ux > 0)] == MUR);		//floor(intersectionVerticale.getVz()) / MUR_X
			ligneHorizontal += ((uz > 0) * 2 - 1);
			distanceALaLigneHorizontale = 0;
		}
	}

	return distanceMur;
}






/*
											FONCTION IntersectionDroites
Description :
Cette fonction retourne le point d'intersection entre deux droite dont une est soit horizontale soit verticale

*/
Vector3D IntersectionDroites(Vector3D u, Vector3D a, bool vertical, float coord)
{
	Vector3D intersection;
	intersection.setVy(a.getVy());

	if (vertical)
	{
		intersection.setVx(coord);
		intersection.setVz(((u.getVx() * a.getVz() - u.getVz() * a.getVx()) + coord * u.getVz()) / u.getVx());
	}
	else
	{
		intersection.setVz(coord);
		intersection.setVx(((u.getVx() * a.getVz() - u.getVz() * a.getVx()) + coord * u.getVx()) / u.getVz());
	}

	return intersection;
}


/*
											FONCTION TrouverLaPorte
Description :
Fonction qui permet au zombie de trouver la porte qui lui permettra d'atteindre le joueur lorsque un mur les sépare
*/
//Vector3D Carte::TrouverLaBonnePorte(float distanceZombieMur, Vector3D positionZombie) const
//{
//	Vector3D position = positionZombie, positionJoueur = m_joueur->getCoord(), positionPorte, zombie_joueur = (Vector3D(positionZombie, positionJoueur)).normalize(), caseCoordonnees;
//	vector<Vector3D> chemin1, chemin2;
//	position.setVx(positionZombie.getVx() + distanceZombieMur * zombie_joueur.getVx());
//	position.setVz(positionZombie.getVz() + distanceZombieMur * zombie_joueur.getVz());
//
//
//	caseCoordonnees.setVy(0);
//
//	//SI ligne verticale
//	if (abs(position.getVx() / MUR_X - round(position.getVx() / MUR_X)) < abs(position.getVz() / MUR_X - round(position.getVz() / MUR_X)))
//	{
//		/*ligneVertical = round(position.getVx() / MUR_X) - (zombie_joueur.getVx() < 0);
//		ligneHorizontal = floor(position.getVz() / MUR_X);*/
//
//		caseCoordonnees.setVx(round(position.getVx() / MUR_X) - (zombie_joueur.getVx() < 0));
//		caseCoordonnees.setVz(floor(position.getVz() / MUR_X));
//
//		chemin1 = TrouverLeChemin(caseCoordonnees, 1, 1);		//PEUT ETRE PASSER LES PROCHAINES COORDONNEES
//		chemin2 = TrouverLeChemin(caseCoordonnees, 3, -1);
//	}
//	else
//	{
//		/*ligneHorizontal = round(position.getVz() / MUR_X) - (zombie_joueur.getVz() < 0);
//		ligneVertical = floor(position.getVx() / MUR_X);*/
//
//		caseCoordonnees.setVx(floor(position.getVx() / MUR_X));
//		caseCoordonnees.setVz(round(position.getVz() / MUR_X) - (zombie_joueur.getVz() < 0));
//
//		chemin1 = TrouverLeChemin(caseCoordonnees, 0, 1);
//		chemin2 = TrouverLeChemin(caseCoordonnees, 2, -1);
//	}
//
//	// Nous avons ici les deux chemins en partant dans un sens et l'autre du mur, il faut maintenant savoir lequel est le plus rapide
//
//	positionPorte = (LongueurChemin(chemin1) < LongueurChemin(chemin2)) ? chemin1[0] : chemin2[0];
//
//
//
//	return positionPorte;
//}


/*
											FONCTION TrouverLeChemin		// TOUTES LES PORTES NE SONT PAS BONNES A PRENDRE, SI ACCES AU JOUEUR VIA PORTE -> STOP
Description :
Programme qui permet de trouver le chemin du zombie au joueur et qui renvoie les coordonnées de toutes les portes utilisée
on suit les murs, si on arrive sur un noeud on teste dans toutes les directions selon un sens données quand on a une porte on retourne ses coordonnées

Paramètres :
porteCoord : coordonnées a verifier actuellement
dernier mvmt : savoir dans quel sens il faut continuer le test; 0 = -x; 1 = -z; 2=x; 3 = z;
sens : -1 = sens trigo/ 1 = sens horaire
*/
//std::vector<Vector3D> Carte::TrouverLeChemin(Vector3D caseCoord, int dernierMvmt, int sens) const
//{
//	std::vector<Vector3D> Portes, PortesRetournee;
//	Vector3D caseTestee;
//
//	if (m_carte[caseCoord.getVz()][caseCoord.getVx()] == PORTE) Portes.push_back(Vector3D(caseCoord));
//	else
//	{
//		for (int i = dernierMvmt - sens; i <= dernierMvmt + sens; i += sens)
//		{
//			i += 4 * (i < 0); i %= 3;
//
//			caseTestee = caseCoord;
//
//			switch (i)
//			{
//			case 0:
//				caseTestee.setVx(caseTestee.getVx() - 1);
//				break;
//			case 1:
//				caseTestee.setVz(caseTestee.getVz() - 1);
//				break;
//			case 2:
//				caseTestee.setVx(caseTestee.getVx() + 1);
//				break;
//			case 3:
//				caseTestee.setVz(caseTestee.getVz() + 1);
//				break;
//			}
//
//			if (m_carte[caseTestee.getVz()][caseTestee.getVx()] == PORTE) Portes.push_back(Vector3D(caseTestee));
//			else if (m_carte[caseTestee.getVz()][caseTestee.getVx()] == MUR)
//			{
//				PortesRetournee = TrouverLeChemin(caseTestee, i, sens);
//				Portes.insert(Portes.end(), PortesRetournee.begin(), PortesRetournee.end());
//			}
//		}
//	}
//	return Portes;
//}

/*
											FONCTION LongueurChemin
Description :
Calcule la longueur d'un chemin calculé pour un zombie

Paramètres :
Le chemin
*/

//float Carte::LongueurChemin(std::vector<Vector3D> const& chemin) const
//{
//	float longueurChemin = 0;
//
//	for (unsigned int i = 0; i < chemin.size() - 1; i++)
//	{
//		longueurChemin += (Vector3D(chemin[i], chemin[i + 1])).length();
//	}
//	return longueurChemin;
//}


std::vector<Zombie*> Carte::getZombies() { return m_zombies; }
std::vector<std::vector<int>> Carte::getCarte() { return m_carte; }
Joueur* Carte::getJoueur() const { return m_joueur; }
vector<Caisse_munition*> Carte::getCaisse_munition() const { return m_caisse_munition; }