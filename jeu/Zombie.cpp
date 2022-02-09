#include "Zombie.h"
#include "Joueur.h"


const int Zombie::s_degats = 5;



Zombie::Zombie(Vector3D c, Vector3D d, checkPoint* cpCible) : Personnage(c, d), m_compteurAttaques(0), m_cpCible(cpCible) {}

bool Zombie::seDeplace(bool j, Joueur* joueur)
{
	Vector3D positionCible;
	if (!j)
	{
		if (Vector3D(m_coord, m_cpCible->coordonnees).length() < ZOMBIE_DISTANCEATTAQUE)
		{
			m_cpCible = m_cpCible->autresCheckPoints[rand() % m_cpCible->autresCheckPoints.size()];
		}
		positionCible = m_cpCible->coordonnees;
	}
	else
	{
		m_cpCible->coordonnees = joueur->getCoord();
	}


	bool tue = 0;

	Vector3D zombie_cible(m_coord, positionCible);
	m_direction = zombie_cible;
	m_direction.normalize();


	if (j == 0) { m_coord += COEFFICIENT_DISTANCE_DEPLACEMENT * m_direction; m_compteurAttaques = 0; }
	else
	{
		if (zombie_cible.length() < ZOMBIE_DISTANCEATTAQUE)
		{
			if (!((m_compteurAttaques++) % ZOMBIE_NBATTAQUEPARTOUR)) tue = Attaque(*joueur);
		}
		else
		{
			m_coord += COEFFICIENT_DISTANCE_DEPLACEMENT * m_direction;
		}
	}
	return tue;
}



bool Zombie::Attaque(Joueur& j) const
{
	return j.estAttaque(s_degats);
}


void Zombie::setCp(checkPoint* cp) { m_cpCible = cp; }
