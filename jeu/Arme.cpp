#include "Arme.h"

#include "Vector3D.h"
#include "Zombie.h"
#include "Personnage.h"

Arme::Arme(bool dispo, int degats, int nbMunitions) : m_dispo(dispo), m_degats(degats), m_nbMunitions(nbMunitions) {
}

void Arme::recharge(int nbMuni) { m_nbMunitions += nbMuni; }

int Arme::getMunition() { return m_nbMunitions; }

int Arme::getDegats() { return m_degats; }

bool Arme::getDispo() const { return m_dispo; }

void Arme::setDispo() { m_dispo = 1; }
