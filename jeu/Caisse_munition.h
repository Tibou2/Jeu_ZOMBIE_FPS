#ifndef CAISSE_MUNITION_HEADER
#define CAISSE_MUNITION_HEADER

#include "ceti.h"




class Caisse_munition
{
private:
	int m_type_munition;
	int m_nb_munition;
	Vector3D m_Coord;
	bool m_dispo;

public:
	Caisse_munition(int type_munition, int nb_munition, Vector3D Coord, bool dispo);

	void setCaisse_coord(Vector3D newCoord);
	void setDispo(bool newDispo);
	void setType_caisse(int newType);

	Vector3D getCoord();
	bool getDispo();
	int getNb_Munition();
	int getType_munition();

	void affichage();

};


#endif