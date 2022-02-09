#ifndef VAGUE_HEADER
#define VAGUE_HEADER

#include "ceti.h"

class Zombie;

class Vague
{
private:
	int m_nb;
	vector<Zombie> m_horde;
	int m_niveau;

public:
	Vague(int nb_init, vector<Zombie> horde_init, int niveau_init);

	int getNiveau();
	int getNb();

	void setNiveau(int NewNiveau);
	void setNb(int NewNb);

};


#endif