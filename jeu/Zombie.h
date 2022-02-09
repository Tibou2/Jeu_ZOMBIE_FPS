#ifndef ZOMBIE_HEADER
#define ZOMBIE_HEADER


#include "Personnage.h"

class Joueur;


class Zombie : public Personnage {

protected:
	static const int s_degats;
	int m_compteurAttaques;
	checkPoint* m_cpCible;

public:
	Zombie(Vector3D c, Vector3D d, checkPoint* cpCible = nullptr);

	bool seDeplace(bool j, Joueur* joueur = NULL);


	bool Attaque(Joueur& j) const; 		//if true le jeu s'arrete

	void setCp(checkPoint* cp);
};

#endif