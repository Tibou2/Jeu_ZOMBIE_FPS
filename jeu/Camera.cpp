#include "Camera.h"
#include "Carte.h"

#include "Joueur.h"


float lastX = 400, lastY = 300;
bool firstMouse = true;

Camera::Camera(Vector3D CamPosinit, Vector3D forwardViewinit, Vector3D RightViewinit, Vector3D upWorldinit, float anglePhinit)
{
    camPos = CamPosinit;
    forwardView = forwardViewinit;
    RightView = RightViewinit;
    upWorld = upWorldinit;
    anglePhi = anglePhinit;
    moveSensitivity = 0.2;
    mouseRotSensitivity = 0.2;
}

void Camera::camLookAt()
{
    gluLookAt(camPos.getVx(),
        camPos.getVy(),
        camPos.getVz(),
        (camPos + forwardView).getVx(),
        (camPos + forwardView).getVy(),
        (camPos + forwardView).getVz(),
        upWorld.getVx(),
        upWorld.getVy(),
        upWorld.getVz());
}

void Camera::cameraMovement(float dM, float dS, Joueur* joueur, Carte carte)
{
    std::vector<std::vector<int>> v = carte.getCarte();
    Vector3D forwardMove = forwardView;
    Vector3D rightMove = -1 * RightView;
    Vector3D camPosintention = camPos;

    //controler les déplacements du joueur en fonction des murs, 
    //voir si le round de ses coordonnées x et z sont sur un mur ou pas en utilisant le vecteur carte initialisé dans la classe carte
    camPosintention += dS * rightMove;
    camPosintention += dM * forwardMove;
    if (v[round(camPosintention.getVz() / MUR_X)][round(camPosintention.getVx() / MUR_X)] == 0 || v[round(camPosintention.getVz() / MUR_X)][round(camPosintention.getVx() / MUR_X)] == 2 || v[round(camPosintention.getVz() / MUR_X)][round(camPosintention.getVx() / MUR_X)] == 4)
    {
        camPos = camPosintention;
        joueur->setCoord(camPos - Vector3D(0, PERSO_Y, 0));
    }
}

void Camera::deplacementSouris(int x, int y, Joueur* joueur)
{
    if (firstMouse)
    {
        lastX = x;
        firstMouse = false;
    }

    float xoffset = x - lastX;
    lastX = x;

    xoffset *= mouseRotSensitivity;

    anglePhi += xoffset;

    //condition pour voir si on arrive à la fin de l'écran
    //contiuer à ajouter ou soustracter l'angle phi pour que le joueur fait un tour complet sans s'arêter quand la souris arrive  au bout de l'écran
    if (xoffset == 0)
    {
        if (x <= 10)
        {
            anglePhi -= 20;
        }
        else if (x >= (600 - 10))
        {
            anglePhi += 20;
        }
    }

    forwardView.setVx(cos(anglePhi * 3.14 / 180));
    forwardView.setVz(sin(anglePhi * 3.14 / 180));

    // normalisation du vecteur forward
    forwardView.normalize();

    // Up ne change pas
    // et right est le cross product entre up et forward
    RightView = upWorld.crossProduct(forwardView);

    // Pour le mode "FPS" on force les deplacements a avoir lieu sur le plan de la camera !
    // Mise a jour des vecteurs forwardMove et rightMove
    Vector3D forwardMove = forwardView;
    Vector3D rightMove = -1 * RightView;

    //on change la direction du joueur selon la direction forwardView de la caméra
    joueur->setDirection(forwardView);
}