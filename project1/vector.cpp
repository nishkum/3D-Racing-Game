/*
 * vector.cpp
 *
 *  Created on: Aug 8, 2013
 *      Author: cs1120239
 */
#include <math.h>
#include "vector.h"

vector::vector(const vector& v){
	comp = new float[3];
	comp[0] = v.comp[0];
	comp[1] = v.comp[1];
	comp[2] = v.comp[2];
}

vector :: vector(float x,float y,float z6){
	this->comp = new float[3];
	this->comp[0] = x;
	this->comp[1] = y;
	this->comp[2] = z6;
}

vector::vector(){
    comp = new float[3];
    comp[0] = 0.0f;
    comp[1] = 0.0f;
    comp[2] = 0.0f;
}

void vector::setCoords(float x,float y,float z6){
    comp[0] = x;comp[1] = y;comp[2] = z6;
}

vector::~vector(){
	delete[] this->comp;
}
vector vector::operator+(const vector& v) const{
    return vector(v.comp[0]+this->comp[0],v.comp[1]+this->comp[1],v.comp[2]+this->comp[2]);
}
vector vector::operator-(const vector& v) const{
    return vector(this->comp[0]-v.comp[0],this->comp[1]-v.comp[1],this->comp[2]-v.comp[2]);
}

vector vector::operator+=(const vector& v) const{
	return vector(this->comp[0]+v.comp[0],this->comp[1]+v.comp[1],this->comp[2]+v.comp[2]);
}

vector vector::operator-=(const vector& v) const{
	return vector(this->comp[0]-v.comp[0],this->comp[1]-v.comp[1],this->comp[2]-v.comp[2]);
}

vector& vector::operator=(const vector& v) {
	comp[0] = v.comp[0];
	comp[1] = v.comp[1];
	comp[2] = v.comp[2];
	return *this;
}


vector vector::scalarMult(float f){
    return vector(this->comp[0]*f,this->comp[1]*f,this->comp[2]*f);
}

float vector::dotproduct(const vector& v) {
    return (float)(this->comp[0]*v.comp[0]+this->comp[1]*v.comp[1]+this->comp[2]*v.comp[2]);
}
vector vector::crossproduct(const vector& v) {
    return vector(comp[1] * v.comp[2] - comp[2] * v.comp[1],
				 comp[2] * v.comp[0] - comp[0] * v.comp[2],
				 comp[0] * v.comp[1] - comp[1] * v.comp[0]);
}


float vector::magnitude(){
    return sqrt(comp[0] * comp[0] + comp[1] * comp[1] + comp[2] * comp[2]);
}
float vector::magnitudesquare(){
    return (comp[0] * comp[0] + comp[1] * comp[1] + comp[2] * comp[2]);
}
vector vector::normalize(){
    float mag = magnitude();
    vector v;
    if (magnitudesquare()!=0.0f){
		v.comp[0] = (this->comp[0])/(mag);
		v.comp[1] = (this->comp[1])/(mag);
		v.comp[2] = (this->comp[2])/mag;
    }
    return v;
}

float z6 = 1.0e-12;
bool equals(float x,float y){
	if ((x-y)<z6 || (y-x)<z6) return true;
	else return false;
}
