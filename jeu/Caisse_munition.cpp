#include "Caisse_munition.h"
#include "LoadTexture.h"


int i = 0;

Caisse_munition::Caisse_munition(int type_munition, int nb_munition, Vector3D Coord, bool dispo)
{
	m_type_munition = type_munition;//0 : pour le Uzi, 1 : pour le shotgun
	m_nb_munition = nb_munition;//un nombre aléatoire entre 
	m_Coord = Coord;//le centre de la gravité de la boite de munition
	m_dispo = dispo;//disponible ou pas, il nous sère à afficher ou non la boite de munition
}

void Caisse_munition::setCaisse_coord(Vector3D newCoord) { m_Coord = newCoord; }
void Caisse_munition::setDispo(bool newDispo) { m_dispo = newDispo; }
void Caisse_munition::setType_caisse(int newType) { m_type_munition = newType; }

Vector3D Caisse_munition::getCoord() { return m_Coord; }
bool Caisse_munition::getDispo() { return m_dispo; }
int Caisse_munition::getNb_Munition() { return m_nb_munition; }
int Caisse_munition::getType_munition() { return m_type_munition; }

void Caisse_munition::affichage()
{
	GLuint Uzi_recharge = LoadTexture::LoadTextureImagFile("texture_carte\\Uzi.jpg", 0);
	GLuint Shotgun_recharge = LoadTexture::LoadTextureImagFile("texture_carte\\shotgun.jpg", 0);

	switch (m_type_munition)
	{
	case 0:
		glPushMatrix();
		glTranslatef(m_Coord.getVx(), m_Coord.getVy() + 1.25, m_Coord.getVz());
		dessiner_cube(Uzi_recharge, 1.5, 1.5, 1.5, 1, 0, 0, 0);
		glPopMatrix();
		LoadTexture::FreeCreatedTexture(Uzi_recharge);

		break;
	case 1:
		glPushMatrix();
		glTranslatef(m_Coord.getVx(), m_Coord.getVy() + 1.25, m_Coord.getVz());
		dessiner_cube(Shotgun_recharge, 1.5, 1.5, 1.5, 1, 0, 0, 0);
		glPopMatrix();
		LoadTexture::FreeCreatedTexture(Shotgun_recharge);

		break;
	}
}