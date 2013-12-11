/*!
 * LoadBMP.h
 *
 * 
 * Conatins IMAGE class, reads Bitmap file into memory 
 * 
 *  Created on: Aug 7, 2013
 *      Author: cs1120239
 */

class Image{
	public :
		int width,height;
		unsigned char* imagedata;
		//constructor
		Image(int w,int h,unsigned char* data);///< Constructur Image(width_of_file,Height_of_file,Unsigned_pointer_data )
		//default constructor
		Image();
		~Image();
};
Image* readBMP(char*);
