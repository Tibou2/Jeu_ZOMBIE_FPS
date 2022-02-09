#ifndef JOUEUR_HEADER
#define JOUEUR_HEADER

#include "ceti.h"
#include "Personnage.h"

class Arme;
class Zombie;

class Joueur : public Personnage {

protected:
	std::vector<Arme*> m_armes;
	int m_armeCourante;
	int m_score;
	std::string m_nom;

public:
	Joueur(std::string nom, Vector3D c, Vector3D d);

	bool Attaque(std::vector<Zombie*>& z, int i, float distance_Mur);		//retourne les points gagnés

	void changeArme(bool haut);
	void recharge(int nbMuni);

	int getScore() const;
	//int getArmeCourante() const;
	Arme* getArme() const;
	std::string getNom() const;
	std::vector<Arme*> getArmes();
};


#endif