#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include "ceti.h"

class Joueur;
class Carte;

#include "Vector3D.h"


class Camera
{
private:
	//Attributs de la camera
	Vector3D camPos;
	Vector3D forwardView;
	Vector3D RightView;
	Vector3D upWorld;

	//Angle d'Euler, on n'utilise içi que phi puisqu'on on ne fait la rotation que suivant y
	float anglePhi;

	//Options de la camera
	float moveSensitivity;
	float mouseRotSensitivity;

public:
	Camera() :camPos(), forwardView(), RightView(), upWorld(), anglePhi(0), moveSensitivity(0.2), mouseRotSensitivity(0.1) {};
	Camera(Vector3D CamPosinit, Vector3D forwardViewinit, Vector3D RightViewinit, Vector3D upWorldinit, float anglePhinit);

	void camLookAt();
	void cameraMovement(float dM, float dS, Joueur* j, Carte carte);
	void deplacementSouris(int x, int y, Joueur* j);
};

#endif
