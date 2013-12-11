/*
 * Renderer.h
 *
 *  Created on: Sep 3, 2013
 *      Author: cs1120239
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include "glm.h"

//main calls this and all initialization of object is done
GLMmodel* initObjRender(char* , float scalef);

//main calls this function to render object
void RenderObj(GLMmodel* o,unsigned int bike_tex , unsigned int paras);///<renders object from the glmmodel and texture input given

#endif /* RENDERER_H_ */
