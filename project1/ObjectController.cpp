/*
 * Objectcontroller.cpp
 *
 *  Created on: Aug 10, 2013
 *      Author: cs1120239
 */
#include "ObjectController.h"
#include <iostream>
using namespace std;

//the number of checkpoints/bonuses collected
//defined in main
int checkPoints = 0;

int objx,objz;
float objy;
float t_height;
float t_height_old;
vector t_normal;
bool if_inair = false;
float turnBike = 0;
extern bool keys[];
extern float score;

//increases the speed of the object
void speedUp(){
	if (keys[0]){
		obj->speed += obj->accel*dt;
		if (obj->speed > obj->MAXSPEED) obj->speed = obj->MAXSPEED;
	}
}

//decreases the speed of the object
void speedDown(){
	if (keys[1] && !if_inair){
		obj->speed -= 10*obj->accel*dt;
		if (obj->speed < 0.0f) obj->speed =0.0f;
	}
}

//handles the left move of the object
void handleLeft(){
	if (keys[2] && !if_inair){
		if (obj->speed!=0.0){
				obj->fi -=  5.0f*RAD_CONV ;
		}
		if(turnBike < 1.0) turnBike += 0.05;
	}
	else if (!keys[2] && turnBike > 0){
			turnBike -=0.05;
	}
}

//handles the right move of the object
void handleRight(){
	if (keys[3] && !if_inair){
		if (obj->speed!=0.0){
			obj->fi +=  5.0f*RAD_CONV ;
		}
		if(turnBike > -1.0 )turnBike -= 0.05;
	}
	else if (!keys[3] && turnBike < 0){
			turnBike +=0.05;
	}
}

extern float TERRAIN_HEIGHT;


/*!
 * Sets the average height of the Object according to s.y co-ords
 */
void computeHeights(){
	t_height_old = t_height;
	objx = obj->position.comp[0];
	objy = obj->position.comp[1];
	objz = obj->position.comp[2];
	if (objx - 2 <= 0 || objx +2 >= terrain->length || objz  - 2 <= 0 || objz + 2 >= terrain->width){

		t_height = -1.0*TERRAIN_HEIGHT;
	}
	else{
		t_height = (terrain->getHeight(objx,objz)
						+terrain->getHeight(objx+1,objz)
						+terrain->getHeight(objx,objz+1)
						+terrain->getHeight(objx+1,objz+1) )/4.0f;
	}
}

/*!
 * sets the normal of the Object according to s.y co-ords
 */
void computeNormals(){
	t_normal = (terrain->getNormal(objx,objz)+terrain->getNormal(objx+1,objz)+terrain->getNormal(objx,objz+1)+terrain->getNormal(objx+1,objz+1)).normalize();
}




//checks the collision of the bike with all static objects
bool checkstaticCollision(statObject* obj1){	///<checks collision between the obstacle passed as input and bike
	//treating xy plane as earth plane
	float x0,y0;
	x0=obj->position.comp[0];
	y0=-obj->position.comp[2];
	//find all the points of the static object with wich our dynamic obj is colliding
	float x1,y1,x2,y2,x3,y3,x4,y4;
	x1=obj1->positions[0][0];
	y1=-obj1->positions[0][2];
	x2=obj1->positions[1][0];
	y2=-obj1->positions[1][2];
	x3=obj1->positions[2][0];
	y3=-obj1->positions[2][2];
	x4=obj1->positions[3][0];
	y4=-obj1->positions[3][2];
	//construct line equatins with all those objects in counter-clockswise direction
	float l0,l1,l2,l3;
	l0=(y1-y2)*x0 + (x2-x1)*y0 - ((y1-y2)*x1+(x2-x1)*y1);
	l1=(y2-y3)*x0 + (x3-x2)*y0 - ((y2-y3)*x2+(x3-x2)*y2);
	l2=(y3-y4)*x0 + (x4-x3)*y0 - ((y3-y4)*x3+(x4-x3)*y3);
	l3=(y4-y1)*x0 + (x1-x4)*y0 - ((y4-y1)*x4+(x1-x4)*y4);
	//for  a point to be inside a convex polygon it should be to the left of all the edges oriented in counterslockwise direction 
	//even if w.r.to 1 edge it is right side return false
	if (l0<-0.2) return false;
	if (l1<-0.2) return false;
	if (l2<-0.2) return false;
	if (l3<-0.2) return false;
	//check to which line it is nearer to
	float mini = min(l0,min(l1,min(l2,l3)));
		//chnage te velocity of obj to 0 and turn it a little away from impact direction
	obj->position=obj->position-obj->getVelocity().normalize().scalarMult(2.0);
	if (l0 == mini) {
		if (obj->getVelocity().dotproduct(vector((x1-x2),0,-(y1-y2))) > 0) obj->fi -= COLLISION_TURN ;
		else obj->fi+= COLLISION_TURN;
	}
	else if(l1 == mini){
		if (obj->getVelocity().dotproduct(vector((x2-x3),0,-(y2-y3))) > 0) obj->fi-= COLLISION_TURN;
		else obj->fi+= COLLISION_TURN;
	}
	else if(l2 == mini){
		if (obj->getVelocity().dotproduct(vector((x3-x4),0,-(y3-y4))) > 0) obj->fi-= COLLISION_TURN;
		else obj->fi+= COLLISION_TURN;
		//obj->speed=obj->speed*0.1;
	}
	else {
		if (obj->getVelocity().dotproduct(vector((x4-x1),0,-(y4-y1))) > 0) obj->fi-= COLLISION_TURN;
		else obj->fi+= COLLISION_TURN;
	}
	obj->speed=0;

	return true;

}


//checks the collision of the bike with all the tree objects
bool checktreeCollision(treeObject* obj1){			///<checks collision between the tree passed as input and bike

	//treating xy plane as earth plane
	float x0,y0;
	x0=obj->position.comp[0];
	y0=-obj->position.comp[2];

	float x1,y1,x2,y2,x3,y3,x4,y4;
	x1=obj1->positions[0][0];
	y1=-obj1->positions[0][2];
	x2=obj1->positions[1][0];
	y2=-obj1->positions[1][2];
	x3=obj1->positions[2][0];
	y3=-obj1->positions[2][2];
	x4=obj1->positions[3][0];
	y4=-obj1->positions[3][2];
	float l0,l1,l2,l3;
	l0=(y1-y2)*x0 + (x2-x1)*y0 - ((y1-y2)*x1+(x2-x1)*y1);
	l1=(y2-y3)*x0 + (x3-x2)*y0 - ((y2-y3)*x2+(x3-x2)*y2);
	l2=(y3-y4)*x0 + (x4-x3)*y0 - ((y3-y4)*x3+(x4-x3)*y3);
	l3=(y4-y1)*x0 + (x1-x4)*y0 - ((y4-y1)*x4+(x1-x4)*y4);

	if (l0<-0.1) return false;
	if (l1<-0.1) return false;
	if (l2<-0.1) return false;
	if (l3<-0.1) return false;

	float mini = min(l0,min(l1,min(l2,l3)));

	obj->position=obj->position-obj->getVelocity().normalize().scalarMult(2.0);
	if (l0 == mini) {
		if (obj->getVelocity().dotproduct(vector((x1-x2),0,-(y1-y2))) > 0) obj->fi -= COLLISION_TURN ;
		else obj->fi+= COLLISION_TURN;
	}
	else if(l1 == mini){
		if (obj->getVelocity().dotproduct(vector((x2-x3),0,-(y2-y3))) > 0) obj->fi-= COLLISION_TURN;
		else obj->fi+= COLLISION_TURN;
	}
	else if(l2 == mini){
		if (obj->getVelocity().dotproduct(vector((x3-x4),0,-(y3-y4))) > 0) obj->fi-= COLLISION_TURN;
		else obj->fi+= COLLISION_TURN;
		//obj->speed=obj->speed*0.1;
	}
	else {
		if (obj->getVelocity().dotproduct(vector((x4-x1),0,-(y4-y1))) > 0) obj->fi-= COLLISION_TURN;
		else obj->fi+= COLLISION_TURN;
	}
	obj->speed=0;

	return true;

}


//checks the collision of the bike with all bonus markers
bool checkbonusCollision(bonusObject* obj1){	///<checks collision between the bonus passed as input and bike

	//treating xy plane as earth plane
	float x0,y0;
	x0=obj->position.comp[0];
	y0=-obj->position.comp[2];
	float x1,y1,x2,y2,x3,y3,x4,y4;
	x1=obj1->positions[0][0];
	y1=-obj1->positions[0][2];
	x2=obj1->positions[1][0];
	y2=-obj1->positions[1][2];
	x3=obj1->positions[2][0];
	y3=-obj1->positions[2][2];
	x4=obj1->positions[3][0];
	y4=-obj1->positions[3][2];
	float l0,l1,l2,l3;
	l0=(y1-y2)*x0 + (x2-x1)*y0 - ((y1-y2)*x1+(x2-x1)*y1);
	l1=(y2-y3)*x0 + (x3-x2)*y0 - ((y2-y3)*x2+(x3-x2)*y2);
	l2=(y3-y4)*x0 + (x4-x3)*y0 - ((y3-y4)*x3+(x4-x3)*y3);
	l3=(y4-y1)*x0 + (x1-x4)*y0 - ((y4-y1)*x4+(x1-x4)*y4);

	if (l0<-0.3) return false;
	if (l1<-0.3) return false;
	if (l2<-0.3) return false;
	if (l3<-0.3) return false;

	return true;

}

statObject* stob;
treeObject* trob;
bonusObject* bonob;


//this function detects if any collision happened with static objects , tree objects and bonus markers
void detectCollision(){		///< calls check collision for required objects
	int i=0;
	int j = statObject::totalObjects;
	while(i<j){
		stob = statObject::ObjArray[i];
		if ( checkstaticCollision(stob) ){
			score-=100;
			return;
		}
		i++;
	}
	i=0;
	j = treeObject::totalTreeObjects;
	while(i<j){
		trob = treeObject::treeObjArray[i];
		if ( checktreeCollision(trob) ){
			score-=100;
			return ;
		}
		i++;
	}
	i=0;
	j = bonusObject::totalbonusObjects;
	while(i<j){
		bonob = bonusObject::bonusObjArray[i];
		if (bonob->beenhit) {
			i++;
			continue;
		}
		if ( checkbonusCollision(bonob) ){
			bonob->beenhit = true;
			checkPoints ++;
			score += 200;
			return ;
		}
		i++;
	}
}



//this function is called in every frame and handles all physics
void autoUpdateObj(){
	//update the score if it is in air
	if (if_inair) score+=3;
	//update score accoring to speed
	score += (obj->speed)*0.005;
	speedUp();
	speedDown();
	handleLeft();
	handleRight();
	computeHeights();
	
	//Check whether the object is going out of terrain and set back into terrain
	if (t_height < -1*(TERRAIN_HEIGHT/2.0)){
		if (objx - 2 <= 0){
			obj->position.comp[0] = 3;
			obj->fi = 0;
		}
		if (objz - 2 <= 0){
			obj->position.comp[2] = 3;
			obj->fi = M_PI/2.0;
		}
		if (objx + 2 >= terrain->length){
			obj->position.comp[0] = terrain->length - 3.0;
			obj->fi = M_PI;
		}
		if (objz + 2 >= terrain->width){
			obj->position.comp[2] = terrain->width - 3.0;
			obj->fi = M_PI*1.5;
		}
		obj->position.comp[1] = terrain->getHeight(obj->position.comp[0],obj->position.comp[2]);

		obj->speed = 0.0;
		if_inair = false;
	}
	else{
		computeNormals();
			//object in air
			if (t_height + 0.25 < objy) {
				if_inair = true;
				if(obj->teta < 110.0*RAD_CONV){
					obj->teta = obj->teta + 1.0f*RAD_CONV;
				}
				else {
					obj->teta = obj->teta + 0.3f*RAD_CONV;
				}
				obj->position = obj->position + obj->getVelocity().scalarMult(dt);
				obj->position.comp[1] -= G*0.1;
				if (t_height + 0.25 > obj->position.comp[1]) {
					obj->position.comp[1] =t_height+0.24 ;
				}
				computeHeights();
				//colliding with surface
				if (t_height + 0.25 > objy) {								
					if_inair = false;
					computeNormals();
					if(t_height >= t_height_old){
						obj->teta = asin(t_normal.dotproduct( vector(0.0f,1.0f,0.0f) ));
					}
					else {
						obj->teta = M_PI/2 + acos(t_normal.dotproduct( vector(0.0f,1.0f,0.0f) ));
					}
					obj->position.comp[1] = t_height;
				}
				//not colliding with surface
				else{}
			}
			//climbing a terrain
			else {															
				computeNormals();
				if(t_height >= t_height_old){
					obj->teta = asin(t_normal.dotproduct( vector(0.0f,1.0f,0.0f) ));
				}
				else {
					obj->teta = M_PI/2 + acos(t_normal.dotproduct( vector(0.0f,1.0f,0.0f) ));
				}
				obj->position.comp[1]=t_height;
				obj->position = obj->position + obj->getVelocity().scalarMult(dt);
				if (obj->teta < 70*RAD_CONV){
					obj->speed=obj->speed-G*cos(obj->teta)*dt;
				}
			}
			//apply friction to object
			if(keys[0]==false && keys[1]==false){
				if(obj->speed>=0){
					obj->speed -= dt*obj->accel;
					if(obj->speed<0)obj->speed = 0.0f;
				}
				else{
					obj->speed += dt*obj->accel;
					if(obj->speed>0)obj->speed = 0.0f;
				}
			}
			//detect collision with other objects
			detectCollision();
	}
}
