#include "Vague.h"
#include "Zombie.h"

Vague::Vague(int nb_init, vector<Zombie> horde_init, int niveau_init)
{
	m_nb = nb_init;
	m_horde = horde_init;
	m_niveau = niveau_init;
}

int Vague::getNb() { return m_nb; }
int Vague::getNiveau() { return m_niveau; }

void Vague::setNb(int NewNb) { m_nb = NewNb; }
void Vague::setNiveau(int NewNiveau) { m_niveau = NewNiveau; }