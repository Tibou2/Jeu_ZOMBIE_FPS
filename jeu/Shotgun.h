#ifndef SHOTGUN_HEADER
#define SHOTGUN_HEADER

#include "Arme.h"

class Zombie;

class Shotgun : public Arme {
private:
	int m_portee;
	static int m_tourParTir;

public:
	Shotgun();

	virtual void affichage(float x, float y, float z) const;

	virtual bool tir(std::vector<Zombie*>& z, Vector3D const& c, Vector3D const& d, int i, float distance_Mur);

	int GetNbTourparTir() const;
};

#endif