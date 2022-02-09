#ifndef PERSONNAGE_HEADER
#define PERSONNAGE_HEADER


#include "ceti.h"

#include"Vector3D.h"
class Carte;

class Personnage {

protected:
	int m_vie;
	Vector3D m_coord;
	Vector3D m_direction;
	bool m_touche; //Pour savoir si le perseonnage (Zombie où joueur) est touché ou pas

public:
	Personnage(Vector3D c, Vector3D d);

	bool estAttaque(int degats);

	int getPdv() const;
	Vector3D getCoord() const;
	Vector3D getDirection() const;
	bool getTouche() const;

	void setCoord(Vector3D v);
	void setDirection(Vector3D v);
	void setTouche(bool newTouche);

	virtual void dessiner(int joueur_ou_zombie);

};

void dessiner_personnage(int joueur_ou_zombie, bool touche_ou_non);


#endif
