#include "Joueur.h"

#include "Arme.h"
#include "Uzi.h"
#include "Pistol.h"
#include "Shotgun.h"
#include "Zombie.h"

Joueur::Joueur(std::string nom, Vector3D c, Vector3D d) : Personnage(c, d), m_nom(nom), m_score(0), m_armeCourante(0)
{
	m_armes.push_back(new Pistol());
	m_armes.push_back(new Uzi());
	m_armes.push_back(new Shotgun());
}

bool Joueur::Attaque(std::vector<Zombie*>& z, int i, float distance_Mur) 		// Il faudra penser a trier les zombies selon leur éloingment avant // Retournera la distance entre joueur et zombie negative si pas tué et positive si tué
{

	bool tue = m_armes[m_armeCourante]->tir(z, m_coord, m_direction, i, distance_Mur);
	m_score += (100 * tue);

	if (tue && !(m_score % 1000) && m_score <= 2000) {
		for (unsigned int i = 0; i < m_armes.size(); i++)
		{
			if (!m_armes[i]->getDispo())
			{
				m_armes[i]->setDispo();
				break;
			}
		}
	}
	return tue;
}

// Fonction appelée par la rotation de la molette de la souris, si on fait rouler vers le haut haut=1 sinon haut=0, il faut s'assurer de la disponibilité de l'arme		
void Joueur::changeArme(bool haut)
{
	string nomArme;
	do {
		m_armeCourante++;
		m_armeCourante %= ARMES_NB;
	} while (!m_armes[m_armeCourante]->getDispo());

}

void Joueur::recharge(int nbMuni)
{
	m_armes[m_armeCourante]->recharge(nbMuni);
}

int Joueur::getScore() const { return m_score; }

Arme* Joueur::getArme() const
{
	return m_armes[m_armeCourante];
}

std::string Joueur::getNom() const { return m_nom; }

std::vector<Arme*> Joueur::getArmes() { return m_armes; }
