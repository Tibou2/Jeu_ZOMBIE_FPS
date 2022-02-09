#ifndef LOADTEXTURE_H
#define LOADTEXTURE_H

#include "ceti.h"

class LoadTexture
{
public:
	static GLuint LoadTextureImagFile(const char* Filename, bool Fast);
	static void FreeCreatedTexture(GLuint texture);

};


#endif
