/*
 * object.cpp
 *
 *  Created on: Aug 10, 2013
 *      Author: cs1120239
 */
#include "object.h"
#include <math.h>
#include <iostream>
using namespace std;

object::object(float x ,float y,float z,float max,float yangle,float xzangle){	///< Constructer object(float x,float y,float z,float max_speed,float teta,float fi)
	//teta and fi in RAD
	teta = yangle;
	speed = 0.5f*TERRAIN_SCALE;
	fi = xzangle;
	accel = 10.0f*TERRAIN_SCALE;
	position.setCoords(x,y,z);
	normal.setCoords(-cos(teta)*cos(fi),sin(teta),-cos(teta)*sin(fi));
	MAXSPEED = max;
}
/*!Default constructor sets the initial values to 
* teta=0.0f;
*speed=0.0f;
*fi=0.0f;
*accel=0.0f;
*position=0.0f,0.0f,0.0f);
*normal=(0.0f,1.0f,0.0f);
*MAXSPEED = 100.0f;
*/
object::object(){
	teta=0.0f;
	speed=0.0f;
	fi=0.0f;
	accel=0.0f;
	position.setCoords(0.0f,0.0f,0.0f);
	normal.setCoords(0.0f,1.0f,0.0f);
	MAXSPEED = 100.0f;
}

vector object::getVelocity(){
	return vector( speed*sin(teta)*cos(fi) , speed*cos(teta) , speed*sin(teta)*sin(fi) );
}

int statObject::totalObjects = 0 ;			///<Initialises no. of obstacles to 0
statObject** statObject::ObjArray = new statObject*[100];
int bonusObject::totalbonusObjects = 0;		///<initialises no. of bonus to 0
bonusObject** bonusObject::bonusObjArray = new bonusObject*[100];
int treeObject::totalTreeObjects = 0;		///<initilises no. of trees to 0
treeObject** treeObject::treeObjArray = new treeObject*[100];


statObject::statObject(float pos[4][3] , float cent[]){	///<COnstuctor for adding obstacles (float_array position_array,flaot centre)
	for(int i=0;i<4;i++){
		for(int j=0;j<3;j++){
			positions[i][j] = pos[i][j];
		}
	}
	ObjArray[totalObjects] = this;
	totalObjects++;
	centre[0] = cent[0];
	centre[1] = cent[1];
	centre[2] = cent[2];
}

bonusObject::bonusObject(float pos[4][3] , float cent[]){	///<COnstuctor for adding bonus (float_array position_array,flaot centre)
	for(int i=0;i<4;i++){
		for(int j=0;j<3;j++){
			positions[i][j] = pos[i][j];
		}
	}
	bonusObjArray[totalbonusObjects] = this;
	totalbonusObjects++;
	centre[0] = cent[0];
	centre[1] = cent[1];
	centre[2] = cent[2];
	beenhit = false;
}

treeObject::treeObject(float pos[4][3] , float cent[]){	///<COnstuctor for adding trees (float_array position_array,flaot centre)
	for(int i=0;i<4;i++){
		for(int j=0;j<3;j++){
			positions[i][j] = pos[i][j];
		}
	}
	treeObjArray[totalTreeObjects] = this;
	totalTreeObjects++;
	centre[0] = cent[0];
	centre[1] = cent[1];
	centre[2] = cent[2];
}

///<Cleans up memory after game is finished
void cleanstaticObjects(){
	delete statObject::ObjArray;
	delete bonusObject::bonusObjArray;
	delete treeObject::treeObjArray;
}
