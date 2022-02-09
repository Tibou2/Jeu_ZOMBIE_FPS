#ifndef ARME_HEADER
#define ARME_HEADER



#include "ceti.h"

class Personnage;
class Zombie;
class Vector3D;
class Caisse_munition;



class Arme {
protected:
	bool m_dispo;
	int m_degats;
	int m_nbMunitions;


public:
	Arme(bool dispo, int degats, int nbMunitions);

	virtual void affichage(float x, float y, float z) const = 0;

	virtual bool tir(std::vector<Zombie*>& z, Vector3D const& c, Vector3D const& d, int i, float distance_Mur) = 0;
	void recharge(int nbMuni);

	int getMunition();
	int getDegats();
	bool getDispo() const;

	void setDispo();
};

#endif