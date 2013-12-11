/*
 * Terrain.h
 *
 *  Created on: Aug 6, 2013
 *      Author: cs1120239
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_
#include "vector.h"

class Terrain{
	public :
		Terrain(int w,int l);
		~Terrain();
		void setHeight( int , float , int );
		float getHeight(int ,int );
		int getWidth();
		int getLength();
		float** twodpointer;
		int width,length;
        vector** normals;
		void computenormals();
		vector getNormal(int,int);
};


#endif /* TERRAIN_H_ */
