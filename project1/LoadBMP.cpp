/*!
 * LoadBMP.cpp
 *
 *  Created on: Aug 6, 2013
 *      Author: cs1120239
 */
#include <stdlib.h>
#include <stdio.h>
#include "LoadBMP.h"

Image::Image(int w,int h,unsigned char* data){
	this->width = w;
	this->height = h;
	this->imagedata = data;
}

Image::Image(){
	width = 0;
	height = 0;
}

Image::~Image(){
	delete[] this->imagedata;
}

//HAS TAKEN THE BELOW FUNCTION FROM AN OPEN SOURCE SITER - STACKOVERFLOW.COM


Image* readBMP(char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    unsigned char* data;

    int size = 3 * width * height;
    data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);

    for(i = 0; i < size; i += 3)
    {
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
    }

    /*
     * In the last part, the swap between every first and third pixel is done because
     * windows stores the color values as (B, G, R) triples, not (R, G, B).
     */

    return new Image(width,height,data);
}


