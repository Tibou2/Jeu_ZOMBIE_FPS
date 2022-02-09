#ifndef CARTE_HEADER
#define CARTE_HEADER

#include <fstream>

#include "ceti.h"
#include "Caisse_munition.h"

class Zombie;
class Joueur;
class Vector3D;

//#include "Caisse_munition.h"


class Carte {
private:
	Joueur* m_joueur;
	std::vector<Zombie*> m_zombies;
	std::vector<std::vector<int>> m_carte;
	std::vector<checkPoint> m_checkPoints;
	vector<Caisse_munition*> m_caisse_munition;

public:
	Carte(std::string nfichier);

	void extractCheckPoints(std::vector<std::string> cps);


	void Affichage() const;

	bool attaque(int& i);

	float MurEntreZombieEtJoueur(Vector3D position, Vector3D direction) const;

	void triZombies();

	Vector3D TrouverLaBonnePorte(float distanceZombieMur, Vector3D position) const;

	std::vector<Vector3D> TrouverLeChemin(Vector3D caseCoord, int dernierMvmt, int sens) const;

	float LongueurChemin(std::vector<Vector3D> const& chemin) const;


	Joueur* getJoueur() const;
	std::vector<Zombie*> getZombies();
	std::vector<std::vector<int>> getCarte();
	vector<Caisse_munition*> getCaisse_munition() const;

};

Vector3D IntersectionDroites(Vector3D u, Vector3D a, bool vertical, float coord);




#endif
