/*
 * terrain.cpp
 *
 *  Created on: Aug 6, 2013
 *      Author: cs1120239
 */

#include "Terrain.h"
Terrain :: Terrain(int w,int l){
			width = w;
			length = l;

			/*
			*the array(twodpointer) if imagined in x-z4 plane has length along x axis
			*and width along z4 axis .
			*
			*i.e.   0<=x<=length-1
			*and    0<=z4<=width-1
			*
			*And also , each x along length has an array of length width
			*/
			twodpointer = new float*[l];

            //normals store the values of each of the normals - vector objects
            normals = new vector*[l];

			//initialize each element of twodpointer and normals as an array
			for(int i=0;i<l;i++){
				twodpointer[i] = new float[w];
				normals[i] = new vector[w];
			}
		}
		//Destructor
Terrain::~Terrain(){
			//free space occupied each element of twodpointer and normals
			for(int i=0;i<length;i++){
				delete[] twodpointer[i];
				delete[] normals[i];
			}

			//free space occupied by twodpointer ans normals array
			delete[] twodpointer;
			delete[] normals;
		}

void Terrain::setHeight(int x,float y,int z4){
			twodpointer[x][z4] = y;
		}

float Terrain::getHeight(int x,int z4){
			return twodpointer[x][z4];
		}

int Terrain::getWidth(){
			return width;
		}

int Terrain::getLength(){
			return length;
        }

void Terrain::computenormals(){
            //tempnormal is just to store the temporary value of the normals
            vector** tempnormal = new vector*[length];
            for(int i=0;i<length;i++){
                tempnormal[i] = new vector[width];
            }

            vector sum;
            vector up;
            vector down;
            vector left;
            vector right;
			//calculating normals for a point from the side vertices and the point
            for(int x=0;x<length;x++){
                for(int z4=0;z4<width;z4++){
                    //for point with x=x and z4=z4
                    sum.setCoords(0.0f,0.0f,0.0f);
                    up.setCoords(0.0f,0.0f,0.0f);
                    down.setCoords(0.0f,0.0f,0.0f);
                    left.setCoords(0.0f,0.0f,0.0f);
                    right.setCoords(0.0f,0.0f,0.0f);
                    if (z4>0){
                        up.setCoords(0.0f,twodpointer[x][z4-1]-twodpointer[x][z4],-1.0f);
                    }
                    if (z4<width-1){
                        down.setCoords(0.0f,twodpointer[x][z4+1]-twodpointer[x][z4],1.0f);
                    }
                    if (x>0){
                        left.setCoords(-1.0f,twodpointer[x-1][z4]-twodpointer[x][z4],0.0f);
                    }
                    if (x<length-1){
                        right.setCoords(1.0f,twodpointer[x+1][z4]-twodpointer[x][z4],0.0f);
                    }

					//now compute the sum of the cross products
                    if (x > 0 && z4 > 0) {
						sum = sum + up.crossproduct(left).normalize();
					}
					if (x > 0 && z4 < width - 1) {
						sum = sum + left.crossproduct(down).normalize();
					}
					if (x < length - 1 && z4 < width - 1) {
						sum = sum + down.crossproduct(right).normalize();
					}
					if (x < length - 1 && z4 > 0) {
						sum = sum + right.crossproduct(up).normalize();
					}
					tempnormal[x][z4] = sum.normalize();
                }
            }
			//averaging normals w.r.to the normals of vertices on its side
            const float FR = 0.5f;
			for(int x = 0; x < length; x++) {
				for(int z4 = 0; z4 < width; z4++) {
					sum = tempnormal[x][z4];
					if (x > 0) {
						sum = sum + tempnormal[x-1][z4].scalarMult(FR);
					}
					if (x < length - 1) {
						sum = sum + tempnormal[x+1][z4].scalarMult(FR);
					}
					if (z4 > 0) {
						sum = sum + tempnormal[x][z4-1].scalarMult(FR);
					}
					if (z4 < width - 1) {
						sum = sum + tempnormal[x][z4+1].scalarMult(FR);
					}

					if (sum.magnitude() == 0) {
						sum = vector(0.0f, 1.0f, 0.0f);
					}
					normals[x][z4] = sum.normalize();
				}
			}

			for(int i = 0; i < length; i++) {
				delete[] tempnormal[i];
			}
			delete[] tempnormal;
		}
//returns normal for a point
vector Terrain::getNormal(int x,int z4){
            return normals[x][z4];
        }
