/*!
 * ObjectController.h
 *
 *  Created on: Aug 17, 2013
 *      Author: cs1120245
 */

///<Handles all physics related things 
#ifndef OBJECTCONTROLLER_H_
#define OBJECTCONTROLLER_H_

#include "object.h"
#include "Terrain.h"
#include "vector.h"
#include <math.h>
#include <iostream>
using namespace std;

extern float TERRAIN_SCALE;
const float RAD_CONV = M_PI/180;	///<Degree to Radians conversion 
const float DEG_CONV = 180/M_PI;	///<Radians to degree conversion
const float dt = 0.025f;		 	///<Time after which physics is updated
const float G= 5.0f*TERRAIN_SCALE;
extern object* obj;
extern Terrain* terrain;
const float COLLISION_TURN = 5.0f*RAD_CONV;

void speedUp();						///<Increases the speed appropriately

void speedDown();					///<Decreases the speed appropriately

void handleLeft();					///<Handles the left move of the object

void handleRight();					///<Handles the right move of the object

void autoUpdateObj();				///<controlls the whole physics of the object,updates the object according to terrain 

void detectCollision();				///< calls check collision for required objects

bool checkstaticCollision(statObject* obj1);	///<checks collision between the obstacle passed as input and bike

bool checktreeCollision(treeObject* obj1);		///<checks collision between the tree passed as input and bike

bool checkbonusCollision(bonusObject* obj1);	///<checks collision between the bonus passed as input and bike

#endif /* OBJECTCONTROLLER_H_ */
