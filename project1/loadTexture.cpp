/*!
 * LoadTexture.cpp
 *
 *  Created on: Aug 9, 2013
 *      Author: cs1120239
 * 
 * Loads the Texture and returns the OPENGL TexId
 * 
 */
#include <GL/glut.h>
#include "loadTexture.h"
#include <string>
using namespace std;

GLuint loadTexture(char * filename){
	Image* tex;
	GLuint texId;
	string file = filename;
	size_t foundBMP = file.find(".bmp");
	if (foundBMP!=string::npos){
		tex =readBMP(filename);

	}
	else{
		tex = new Image();
		tex->imagedata = (unsigned char*)tga_load(filename, &tex->width, &tex->height, TGA_TRUECOLOR_24);

	}
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,tex->width, tex->height, 0, GL_RGB,GL_UNSIGNED_BYTE,tex->imagedata);
	delete tex;
	return texId;
}
