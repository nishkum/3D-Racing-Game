/*!
 * loadTexture.h
 *
 * Loads the Texture and returns the OPENGL TexId
 *  Created on: Sep 4, 2013
 *      Author: cs1120239
 */

#ifndef LOADTEXTURE_H_
#define LOADTEXTURE_H_
#include "LoadBMP.h"
#include "libtarga.h"

//the following are defined in loadTexture.cpp
GLuint loadTexture(char * filename);

#endif /* LOADTEXTURE_H_ */
