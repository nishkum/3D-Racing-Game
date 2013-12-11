/*
 * Terrain_Generation.cpp
 *
 *  Created on: Aug 6, 2013
 *      Author: cs1120239
 */

#include "LoadBMP.h"
#include "terrain_Generation.h"

Terrain* gen_Terrain(char* filename,float height){
	Image* image = readBMP(filename);
	int w = image->width;
	int h = image->height;
	Terrain* terrain = new Terrain(w,h);

	/*
	 * Actually tx of terrain will range from 0 to h-1
	 * and tz of terrain will range from 0 to w-1
	 */
	for(int tx=0;tx<h;tx++){
		for(int tz=0;tz<w;tz++){
			unsigned char color = image->imagedata[3*(tz*w+tx)];
			float y = height*((color/255.0f)-0.5f);
			terrain->setHeight(tx,y,tz);
		}
	}
    delete image;

	terrain->computenormals();

	return terrain;
}
