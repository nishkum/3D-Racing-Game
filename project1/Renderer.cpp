/*
 * Renderer.cpp
 *
 *  Created on: Sep 3, 2013
 *      Author: cs1120239
 */
#include "Renderer.h"
#include <iostream>
using namespace std;

GLMmodel* objToLoad;
//initialize all object parameters
GLMmodel* initObjRender(char* objName,float scale){
	objToLoad = glmReadOBJ(objName);
	glmScale(objToLoad, scale);
	glmFacetNormals(objToLoad);
//	glmVertexNormals( objToLoad , 90.0);
	return objToLoad;
}

//render the object
//paras are the parameters that need to be passed to glmDraw such as GLM_TEXTURE etc ..
void RenderObj(GLMmodel* o , unsigned int bike_tex , unsigned int paras){
	/*
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, bike_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	*/
	glmDraw( o , paras );
}




