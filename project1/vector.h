/*
 * vector.h
 *
 *  Created on: Aug 8, 2013
 *      Author: cs1120239
 */

#ifndef vector_H_
#define vector_H_

class vector{
	public :
		float* comp;
		vector(float,float,float);
		vector();
		vector(const vector& v);
		~vector();
		void setCoords(float,float,float);
		vector operator+(const vector& v) const;
		vector operator-(const vector& v) const;
		vector operator+=(const vector& v) const;
		vector operator-=(const vector& v) const;
		vector& operator=(const vector&v) ;
		vector scalarMult(float f);
		float dotproduct(const vector& v) ;
		vector crossproduct(const vector& v) ;
		float magnitude();
		float magnitudesquare();
		vector normalize();
};

bool equals(float,float);

#endif /* vector_H_ */
