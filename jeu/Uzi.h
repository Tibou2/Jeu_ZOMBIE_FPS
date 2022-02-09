#ifndef UZI_HEADER
#define UZI_HEADER

#include "Arme.h"

class Zombie;

class Uzi : public Arme {
private:
	static int m_tourParTir;
public:
	Uzi();

	virtual bool tir(std::vector<Zombie*>& z, Vector3D const& c, Vector3D const& d, int i, float distance_Mur);

	virtual void affichage(float x, float y, float z) const;


	int GetNbTourparTir() const;

};

#endif