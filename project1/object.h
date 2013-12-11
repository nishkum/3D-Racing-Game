/*!
 * object.h
 *
 *  Created on: Aug 10, 2013
 *      Author: cs1120239
 * 
 * Contains the classes of all objects : bike, obstacles, trees, bonus
 * Object Controller deals the physics between these objects
 * 
 */

#ifndef OBJECT_H_
#define OBJECT_H_
#include "vector.h"

extern float TERRAIN_SCALE;///<Scale to which terrain has to be scaled
class object{
	public:
		//teta and fi in RAD
	
		float teta;		///<Angle of Object with the Y axis in RAD 
		float fi;		///<Angle of projectin of the Object on XY plane with the X axis in RAD 
		float speed;	///<Speed of the Object
		float accel;	///<Acceleraton of Object
		vector position;///<position of Object in vector form
		vector normal;	///<UPNormal of object
		object(float,float,float,float,float,float);///< Constructer object(float x,float y,float z,float max_speed,float teta,float fi)
		/*!Default constructor sets the initial values to 
		* teta=0.0f;
		*speed=0.0f;
		*fi=0.0f;
		*accel=0.0f;
		*position=0.0f,0.0f,0.0f);
		*normal=(0.0f,1.0f,0.0f);
		*MAXSPEED = 100.0f;
		*/
		object(); 
		float MAXSPEED;
		vector getVelocity();///<retuns velocity of the object
};
/*!
 * Class containing the static obstacles
 * 
 */
class statObject{
	public:
		statObject(float pos[][3] , float cent[]);
		static statObject** ObjArray;
		static int totalObjects;
		float positions[4][3];		///<all positions should be filled only in counterclockwise diretion
		float centre[3];
};


/*!
 * Class containing the bonus Objects
 * 
 */
class bonusObject{
	public:
		bonusObject(float pos[][3] , float cent[]);
		static bonusObject** bonusObjArray;
		static int totalbonusObjects;
		float positions[4][3];	///<all positions should be filled only in counterclockwise diretion
		float centre[3];
		bool beenhit;
};

/*!
 * Class containing the trees in track
 * 
 */
class treeObject{
	public :
		treeObject(float pos[][3] , float cent[]);
		static treeObject** treeObjArray;
		static int totalTreeObjects;
		float positions[4][3];	///<all positions should be filled only in counterclockwise diretion
		float centre[3];
};

void cleanstaticObjects();///<Cleans the memory after the game ends
#endif /* OBJECT_H_ */
