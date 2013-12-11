#include <string.h>
#include <sstream>
#include <GL/glut.h>
#include "hud.h"
#include "object.h"
using namespace std;

extern int checkPoints;
float score;
extern object* obj;
float time_old = 0;

//time elapsed till now counter : defined in terstmain.cpp
extern int timeElapsedCounter;
extern int MAX_MINUTES;  				//defined in testmain.cpp
int timeElapsed;
int totalCheckPoints ;

stringstream sst;
const char* rech;
string rest;

//isGameOver defined in main
extern bool isGameOver;

//time taken to finish the game :
int timeToFinishmin;	//the number of minutes taken to finish the game
int timeToFinishsec;	//the number of seconds taken to finish the game
bool hasFinished = false;
extern bool isPaused;

//initializes HUD paras
void initHud(){
	score = 0;
	totalCheckPoints =  bonusObject::totalbonusObjects;
}

//called once the game is over
void gameOver(){
	glColor3f(0,0,0);

	//display GAME OVER
	rest = string("GAME OVER");
	rech = rest.c_str();
	glRasterPos2f( -0.3,0.8 ) ;
	do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;

	glColor3f(1,0,0);
	
	//display score
	rest = string("Your Score is :");
	rech = rest.c_str();
	glRasterPos2f( -0.3,0.6 ) ;
	do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;
	sst.str("");
	sst<<(int)score<<ends;
	rest = sst.str();
	rech = rest.c_str();
	do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;

	//display bonuses taken
	rest = string("Number of Bonus Markers taken by you :");
	rech = rest.c_str();
	glRasterPos2f( -0.3,0.4 ) ;
	do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;
	sst.str("");
	sst<<checkPoints<<ends;
	rest = sst.str();
	rech = rest.c_str();
	do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;

	rest = string("/");
	rech = rest.c_str();
	glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech );

	sst.str("");
	sst<<totalCheckPoints<<ends;
	rest = sst.str();
	rech = rest.c_str();
	do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;

	//display the time taken
	glRasterPos2f(-0.3,0.2);
	rest = string("Time taken by you :");
	rech = rest.c_str();
	do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;
	sst.str("");
	sst<<timeToFinishmin<<ends;
	rest = sst.str();
	rech = rest.c_str();
	do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;

	rest = string("Min ");
	rech = rest.c_str();
	do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;

	sst.str("");
	sst<<timeToFinishsec<<ends;
	rest = sst.str();
	rech = rest.c_str();
	do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;

	rest = string(" sec");
	rech = rest.c_str();
	do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;

	//display "Press Esc to Exit ."
	glRasterPos2f(-0.3,0);
	rest = string("Press Esc to exit .");
	rech = rest.c_str();
	do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;

	isGameOver = true;
}


//called every time the scene is drawn
void render_hud(){
	glMatrixMode( GL_PROJECTION ) ;
	glPushMatrix() ;
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW ) ;
	glPushMatrix() ;
	glLoadIdentity() ;
	//disable the depth test so renders on top
	glDisable( GL_DEPTH_TEST ) ;

	timeElapsed = timeElapsedCounter*0.001;	//find the time elapsed

	int timeleft = (60*MAX_MINUTES - timeElapsed);
	if (timeleft <= 0 || checkPoints == totalCheckPoints){
		if (!hasFinished){
			timeToFinishmin = timeElapsed/60;
			timeToFinishsec = timeElapsed%60;
			hasFinished = true;
			gameOver();
		}
		else{
			gameOver();
		}
	}
	else{
		//load all identity matrices by first pushing matrices

		//set the color of text to be rendered
		glColor3f(1.0f, 0.0f, 0.0f);

		//update score
		if (!isPaused ) score -= 0.2;
		if (score < 0) score = 0;
		int diff_min = timeElapsed / 60 ;			//find the number of minutes elapsed
		int diff_sec = timeElapsed % 60 ;			//find the number of seconds elapsed

		//position the writer on the screen
		glRasterPos2f( -0.9,0.90 ) ;
		//display minutes
		sst.str("");
		sst << diff_min << ends;
		rest = sst.str();
		rech = rest.c_str();
		do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;


		rest = " Min ";
		rech = rest.c_str();
		do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;

		//display seconds
		sst.str(std::string()); 	//clear the stringstream
		sst << diff_sec << ends;	//add seconds to the stream
		rest = sst.str();
		rech = rest.c_str();	//get the const char * from it
		do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;


		rest =" sec";
		rech = rest.c_str();
		do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;

		//completed displaying min and sec

		glColor3f(98/255, 250/255, 0);
		glRasterPos2f( -0.3,0.90 ) ;
		//now display the score
		rest = "Score : ";
		rech = rest.c_str();
		do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;

		sst.str(std::string());
		sst<<(int)score<<ends;
		rest = sst.str();
		rech = rest.c_str();
		do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;

		glColor3f(0.0f, 1.0f, 0.0f);
		glRasterPos2f( 0.7,0.90 ) ;
		//Now display the speed
		rest = "Speed : ";
		rech = rest.c_str();
		do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;

		sst.str(std::string());
		sst<<obj->speed<<ends;
		rest = sst.str();
		rech = rest.c_str();
		do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;

		//now display the number of checkpoints left

		glColor3f(0,0,0);
		glRasterPos2f(0.1,0.9);
		rest = "Bonus Markers :";
		rech = rest.c_str();
		do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;

		sst.str("");
		sst<<checkPoints<<ends;
		rech = (sst.str()).c_str();
		do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;

		rech = string("/").c_str();
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech );

		sst.str("");
		sst<<totalCheckPoints<<ends;
		rest = sst.str();
		rech = rest.c_str();
		do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;

		//display the time left only if the minutes left is 1 less than the MAX_MINUTES
		if (diff_min >= MAX_MINUTES-1 ) {

			glColor3f(1,0,0);
			glRasterPos2f(-0.1,0.7);
			rest = string("Time Left :");
			rech = rest.c_str();
			do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;
			sst.str("");
			sst<<timeleft<<ends;
			rest = (sst.str());
			rech = rest.c_str();
			do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;
			rest = string(" sec");
			rech = rest.c_str();
			do glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, *rech ); while( *(++rech) ) ;
		}
	}
	glEnable( GL_DEPTH_TEST ) ; // Turn depth testing back on
	glMatrixMode( GL_PROJECTION ) ;
	glPopMatrix() ; // revert back to the matrix I had before.
	glMatrixMode( GL_MODELVIEW ) ;
	glPopMatrix() ;
}
