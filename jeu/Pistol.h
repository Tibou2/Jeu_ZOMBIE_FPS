#ifndef PISTOL_HEADER
#define PISTOL_HEADER


#include "Arme.h"

class Zombie;




class Pistol : public Arme {
private:
	static int m_tourParTir;
public:
	Pistol();

	virtual void affichage(float x, float y, float z) const;

	virtual bool tir(std::vector<Zombie*>& z, Vector3D const& c, Vector3D const& d, int i, float distance_Mur);

	int GetNbTourparTir() const;

};

#endif