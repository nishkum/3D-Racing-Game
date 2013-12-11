/*!
 * testmain.cpp
 *
 * Created on: Aug 7, 2013
 *      Author: cs1120239
 */

//texture loading on line 29
//terrain loading on line 136
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
using namespace std;


#include "terrain_Generation.h"									//for the terrain library
#include "loadTexture.h"										//for the texture library
#include "object.h"												//for the object class - part of physics library
#include "ObjectController.h"									//for physics library - handles every physics related to object
#include "Renderer.h"											//for loading Object Rendering library
#include "hud.h"												//for loading HUD library

bool isGameOver = false;										//is the game over
bool ifPractice = false;										//check to see if the game is a practice mode game ?

int MAX_MINUTES;												//the max number of minutes the game runs
																//if it is not a practice mode , then the game displays this

extern float score;												//scores and time are defined in hud.cpp
int  timeElapsedCounter;
extern int timeToFinishsec;
extern int timeToFinishmin;


const int WINDOW_WIDTH = 800; 									//setting window displayed parameters
const int WINDOW_HEIGHT = 800;
char WINDOW_TITLE[] = " WELCOME TO DIRT RACING : VERSION 2.0 ";
const int TIME_BETWEEN_UPDATES = 25;
float BACKGROUND_COLOR[] = { (float)102/255.0  , (float) 178/255.0 , (float) 250/250.0 ,1.0};
float PERSPECTIVE_CAM_ANGLE = 40.0;
bool ifFullScreen = true;
bool isPaused = false;


char* TERRAIN_BITMAP ;											//setting all terrain parameters in function loadTrackFiles
float TERRAIN_HEIGHT = 10.0;
char* TERRAIN_TEX ;
float TERRAIN_SCALE = 200/60;


char BIKE_TEX[] = "./Suzuki/bike01.tga";						//setting bike parameters
char BIKE_OBJ[] ="./Suzuki/Bike_Suzuki_Katana.obj";
float BIKE_SCALE_FACTOR = 0.004;
GLMmodel* mybike ;
int bikeInitX = 5, bikeInitZ = 5;


																//initializing other static objects' texture
GLMmodel* crate;												//crate
char CRATE_OBJ[] ="./obstacles/cube/cube_texture.obj";
char CRATE_TEX[] = "./obstacles/cube/crate.tga";
float CRATE_SCALE_FACTOR = 1.0;

										
GLMmodel* tree ;												//trees
char TREE_OBJ[] = "./obstacles/Palm_Tree/Palm_Tree.obj";
char TREE_TEX[] = "./obstacles/Palm_Tree/ENV_MP_Iraq_PlantsSansTrans_D.tga";
float TREE_SCALE_FACTOR = 0.04;

GLMmodel* bonusob;												//bonus objects
char BONUS_OBJ[] = "./obstacles/bonus/cube_texture.obj";
char BONUS_TEX[] = "./obstacles/bonus/wrapper.tga";
float BONUS_SCALE_FACTOR = 1.0;


GLuint terrain_tex;												//initialzing the texture integers
GLuint bike_tex;
GLuint crate_tex;
GLuint tree_tex;
GLuint bonus_tex;


Terrain* terrain;												//initializing other parameters
object* obj ;
bool firsttimedrawn = true;
float theta = 45.0f, phi = 45.0f;
float rad = 15.0f;

extern float turnBike;											//angle by which bike will be turned


statObject* statobj;											//pointers to apt objects
bonusObject* bonusobj;
treeObject* treeobj;


//this function loads all track spefific information from the file - the file is "track"+ the fileno
void loadTrackFiles(int fileno){
	//following code will build the name of the file 
	string t1 = "tracks/track";
	string t2 = "bmp";
	string t3 = "_tex";
	string t4 = "txt";

	//loading the terrain name
	TERRAIN_BITMAP = new char[20];
	TERRAIN_BITMAP[0] = '.';
	TERRAIN_BITMAP[1] = '/';
	copy(t1.begin(), t1.end() , TERRAIN_BITMAP+2);
	TERRAIN_BITMAP[14] = (char)(48 + fileno);
	TERRAIN_BITMAP[15] = '.';
	copy(t2.begin() , t2.end() , TERRAIN_BITMAP+16);
	TERRAIN_BITMAP[19] = '\0';

	//loading the terrain texture
	TERRAIN_TEX = new char[24];
	TERRAIN_TEX[0] = '.';
	TERRAIN_TEX[1] = '/';
	copy(t1.begin(), t1.end() , TERRAIN_TEX+2);
	TERRAIN_TEX[14] = (char)(48 + fileno);
	copy(t3.begin() , t3.end() , TERRAIN_TEX+15);
	TERRAIN_TEX[19] = '.';
	copy(t2.begin() , t2.end() , TERRAIN_TEX+20);
	TERRAIN_TEX[23] = '\0';

	//loading the .txt file
	char* fileToLoad = new char[20];
	fileToLoad[0] = '.';
	fileToLoad[1] = '/';
	copy(t1.begin(), t1.end() , fileToLoad+2);
	fileToLoad[14] = (char)(48 + fileno);
	fileToLoad[15] = '.';
	copy(t4.begin() , t4.end() , fileToLoad+16);
	fileToLoad[19] = '\0';


	//now scan the file
	ifstream trfile;
	trfile.open(fileToLoad);
	string temp ;

	//first line contains the parameter terrain_height
	getline(trfile , temp);
	TERRAIN_HEIGHT = atof(temp.c_str());

	//terrain generation
	terrain = gen_Terrain( TERRAIN_BITMAP , TERRAIN_HEIGHT);

	//number of static objects
	getline(trfile,temp);
	int number = atoi(temp.c_str());
	float stato[4][3];
	float centre[3];
	//scan and initialize each static object
	float a , b;
	for(int i=0;i<number;i++){
		getline(trfile, temp , ' ');
		a = atof(temp.c_str());
		getline(trfile, temp );
		b = atof(temp.c_str());

		stato[0][0] = a;stato[0][2] = b;
		stato[1][0] = a;stato[1][2] = b-1;
		stato[2][0] = a-1;stato[2][2] = b-1;
		stato[3][0] = a-1;stato[3][2] = b;

		centre[0] = (stato[0][0]+stato[1][0]+stato[2][0]+stato[3][0])/4.0;
		centre[2] = (stato[0][2]+stato[1][2]+stato[2][2]+stato[3][2])/4.0;
		centre[1] = terrain->getHeight((int)(stato[0][0]), (int)(stato[0][2])) + 0.5;
		stato[0][1] = centre[1];
		stato[1][1] = centre[1];
		stato[2][1] = centre[1];
		stato[3][1] = centre[1];
		//following  line automatically adds the object created to the array of static objects
		statobj = new statObject(stato , centre);
	}



	//now scan the number of bonus objects
	getline(trfile,temp);
	number = atoi(temp.c_str());
	//scan and initialize each bonus object
	for(int i=0;i<number;i++){
		getline(trfile, temp , ' ');
		a = atof(temp.c_str());
		getline(trfile, temp );
		b = atof(temp.c_str());

		stato[0][0] = a;stato[0][2] = b;
		stato[1][0] = a;stato[1][2] = b-1;
		stato[2][0] = a-1;stato[2][2] = b-1;
		stato[3][0] = a-1;stato[3][2] = b;

		centre[0] = (stato[0][0]+stato[1][0]+stato[2][0]+stato[3][0])/4.0;
		centre[2] = (stato[0][2]+stato[1][2]+stato[2][2]+stato[3][2])/4.0;
		centre[1] = terrain->getHeight((int)(stato[0][0]), (int)(stato[0][2])) + 0.5;
		stato[0][1] = centre[1];
		stato[1][1] = centre[1];
		stato[2][1] = centre[1];
		stato[3][1] = centre[1];
		//initialize each bonus object once created
		bonusobj = new bonusObject(stato , centre);
	}


	//scan the number of tree objects
	getline(trfile , temp);
	number = atoi(temp.c_str());
	//now scan and initialize each tree object
	for(int i=0;i<number;i++){
			getline(trfile, temp , ' ');
			a = atof(temp.c_str());
			getline(trfile, temp );
			b = atof(temp.c_str());
			stato[0][0] = a;stato[0][2] = b;
			stato[1][0] = a;stato[1][2] = b-1;
			stato[2][0] = a-1;stato[2][2] = b-1;
			stato[3][0] = a-1;stato[3][2] = b;
			centre[0] = (stato[0][0]+stato[1][0]+stato[2][0]+stato[3][0])/4.0;
			centre[2] = (stato[0][2]+stato[1][2]+stato[2][2]+stato[3][2])/4.0;
			centre[1] = terrain->getHeight((int)(stato[0][0]), (int)(stato[0][2])) - 0.5;
			stato[0][1] = centre[1];
			stato[1][1] = centre[1];
			stato[2][1] = centre[1];
			stato[3][1] = centre[1];
			//initialize each tree object
			treeobj = new treeObject(stato , centre);
	}
	//the last line of each file gives the initial x and  z coords of the bike .. scan those and those to bikeInitX and bikeInitZ
	getline(trfile ,temp ,' ');
	bikeInitX = atoi(temp.c_str());
	getline(trfile , temp);
	bikeInitZ = atoi(temp.c_str());
	//done all reading .. now close the file
	trfile.close();
}


// this function initializes everything required for proper loading tof the program
void initRendering(int tfile) {
	//initialize objects and terrain from the file
	loadTrackFiles(tfile);

	//initialize the max number of minutes
	if (tfile>=5){
		MAX_MINUTES = 2;
	}
	else{
		MAX_MINUTES = 3;
	}

	//initialize hud paras if it not the practice mode
	if (!ifPractice) initHud();

	//initialize the bike physics object
	obj = new object( bikeInitX , terrain->twodpointer[bikeInitX][bikeInitZ] , bikeInitZ ,
				   100 , asin(terrain->getNormal(bikeInitX,bikeInitZ).normalize().dotproduct( vector(0.0f,1.0f,0.0f) ))
				   , 0.0);

	//initialze the gl paras	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	//set the background color
	glClearColor( BACKGROUND_COLOR[0],  BACKGROUND_COLOR[1] ,  BACKGROUND_COLOR[2] ,  BACKGROUND_COLOR[3]);

	//initialize all .obj files
	mybike = initObjRender(BIKE_OBJ, BIKE_SCALE_FACTOR);
	crate = initObjRender( CRATE_OBJ , CRATE_SCALE_FACTOR);
	tree = initObjRender(TREE_OBJ , TREE_SCALE_FACTOR);
	bonusob = initObjRender(BONUS_OBJ , BONUS_SCALE_FACTOR);
	
	//load all textures
	terrain_tex = loadTexture(TERRAIN_TEX);
	bike_tex = loadTexture(BIKE_TEX);
	crate_tex = loadTexture(CRATE_TEX);
	tree_tex = loadTexture(TREE_TEX);
	bonus_tex = loadTexture(BONUS_TEX);
	tree_tex = loadTexture(TREE_TEX);
	timeElapsedCounter = 0;
}


//cleanUp will be called on exit
void cleanUp(){
	delete obj;
	int total = statObject::totalObjects;
	for(int i=0;i<total;i++){
		delete statObject::ObjArray[i];
	}
	cleanstaticObjects();
	delete TERRAIN_BITMAP;
	delete TERRAIN_TEX;
}


//on exit this function writes score and time elapsed in a file named curr_game.txt
void finishingAction(){
	ofstream writedata ;
	writedata.open("../linux_build/curr_game.txt" , ios::app);
	writedata << "\n";
	writedata << (int)score <<"\n";
	writedata << (timeToFinishmin*60 + timeToFinishsec) <<"\n";
	writedata.close();
}


//the order in which keys are considered are w,s,a,d,8,2,7,9,1,3
//f4 for fullscreen
bool keys[10];

//following function will be called on pressing the apt key
void handleKeypress(unsigned char key , int x ,int y){
	switch(key){
		case 'z':
			cout<<obj->position.comp[0]<<" "<<obj->position.comp[2]<<endl;
			break;
		case 'w':
			keys[0] = true;
			break;
		case 's':
			keys[1] = true;
			break;
		case 'a':
			keys[2] = true;
			break;
		case 'd':
			keys[3] = true;
			break;
		case '8':
			rad-=2.0f;
			keys[4] = true;
			break;
		case '2':
			rad+=2.0f;
			keys[5] = true;
			break;
		case '7':
			theta += 2.0f;
			keys[6] = true;
			break;
		case '9':
			theta -= 2.0f;
			keys[7] = true;
			break;
		case '1':
			phi+=2.0f;
			keys[8] = true;
			break;
		case '3':
			phi-=2.0f;
			keys[9] = true;
			break;
		case ' ':
			if (!isGameOver){
				if (isPaused) isPaused = false;			//switch the value of isPaused by doing exor with 1
				else isPaused = true;
			}
			break;
		case (27):
			//on pressing exit call cleanUp which will free resources and exit the game
			cleanUp();
			finishingAction();
			exit(0);
	}
}

//handles pressing of special keys
void handleSpecialKeys(int key , int x, int y){
	switch(key){
		case GLUT_KEY_F4:
			if (!ifFullScreen){
				glutFullScreen();
				ifFullScreen = true;
			}
			else{
				glutReshapeWindow(WINDOW_WIDTH , WINDOW_HEIGHT);
				glutPositionWindow(10,10);
				ifFullScreen = false;
			}
			break;
	}
}


//following function will be called when apt key is released
void keyRelease(unsigned char key , int x, int y){
	switch(key){
		case 'w':
			keys[0] = false;
			break;
		case 's':
			keys[1] = false;
			break;
		case 'a':
			keys[2] = false;
			break;
		case 'd':
			keys[3] = false;
			break;
		case '8':
			keys[4] = false;
			break;
		case '2':
			keys[5] = false;
			break;
		case '7':
			keys[6] = false;
			break;
		case '9':
			keys[7] = false;
			break;
		case '1':
			keys[8] = false;
			break;
		case '3':
			keys[9] = false;
			break;
	}
}


//handles resizing
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( PERSPECTIVE_CAM_ANGLE, (double)w / (double)h, 1.0, 200.0);
}


//the drawscene function
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//initialize the camera
	gluLookAt(obj->position.comp[0]-7.0*cos(obj->fi),obj->position.comp[1]+2.0,obj->position.comp[2]-7.0*sin(obj->fi),
				obj->position.comp[0]+5.0*cos(obj->fi),obj->position.comp[1],obj->position.comp[2]+5.0*sin(obj->fi),0.0f,1.0f,0.0f);


	//score updated in render_hud and autoUpdateObj
	glColor3f(1.0f,1.0f,1.0f);
	glEnable(GL_TEXTURE_2D);
	
	//rendering the bike
	glPushMatrix();
	vector v = obj->position;
	glTranslatef(v.comp[0],v.comp[1] + BIKE_SCALE_FACTOR*110,v.comp[2]);
	glRotatef(90.0+obj->fi*DEG_CONV,0.0,-1.0,0.0);
	glRotatef(90.0-obj->teta*DEG_CONV,1.0,0.0,0.0);
	glTranslatef(0.0,0.0,BIKE_SCALE_FACTOR*30);
	if(turnBike !=0.0 ){
		glRotatef(turnBike*30.0f,0.0,0.0,1.0);
	}
	
	//bind the texture of the bike then draw it
	glBindTexture(GL_TEXTURE_2D, bike_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	RenderObj(mybike , bike_tex ,  GLM_SMOOTH  | GLM_TEXTURE );
	glPopMatrix();


	//now first load the texture for static objects and then bind the texture and finally draw them
	glColor3f(1.0f,1.0f,1.0f);
	glBindTexture(GL_TEXTURE_2D, crate_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	for(int i=0;i<statObject::totalObjects;i++){
		glPushMatrix();
		glTranslatef(statObject::ObjArray[i]->centre[0] , statObject::ObjArray[i]->centre[1] ,
				statObject::ObjArray[i]->centre[2] );
		RenderObj(crate , crate_tex , GLM_TEXTURE | GLM_FLAT);
		glPopMatrix();
	}


	//load texture for tree objects , bind it and finally draw it
	glBindTexture(GL_TEXTURE_2D, tree_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for(int i=0;i<treeObject::totalTreeObjects;i++){
		glPushMatrix();
		glTranslatef(treeObject::treeObjArray[i]->centre[0] , treeObject::treeObjArray[i]->centre[1] ,
				treeObject::treeObjArray[i]->centre[2] );
		glRotatef( 90 , -1,0,0);
		RenderObj(tree , tree_tex , GLM_TEXTURE | GLM_SMOOTH);
		glPopMatrix();
	}


	//now draw the bonus objects
	glBindTexture(GL_TEXTURE_2D, bonus_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for(int i=0;i<bonusObject::totalbonusObjects;i++){
		//display only those bonus objects that have not been hit
		if (bonusObject::bonusObjArray[i]->beenhit) continue;
		glPushMatrix();
		glTranslatef(bonusObject::bonusObjArray[i]->centre[0] , bonusObject::bonusObjArray[i]->centre[1] ,
				bonusObject::bonusObjArray[i]->centre[2] );
		RenderObj(bonusob , bonus_tex , GLM_TEXTURE | GLM_FLAT);
		glPopMatrix();
	}


	//for lighting
	float ab[] = {0.85f, 0.85f, 0.85f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ab);

	GLfloat lColor[] = {0.3f, 0.7f, 0.8f, 1.0f};
	GLfloat lPosition[] = {1.0f, 1.8f, 12.1f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lPosition);

	//for texture of terrain
	glBindTexture(GL_TEXTURE_2D, terrain_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//setting the color of terrain and drawing the terrain
	glColor3f(1.0f, 1.0f, 1.0f);
	for(int x = 0; x < terrain->length-1; x++) {
		glBegin(GL_TRIANGLE_STRIP);
		for(int z5 = 0; z5 < terrain->width; z5++) {
			vector v = terrain->normals[x][z5];
			glNormal3f(v.comp[0],v.comp[1],v.comp[2]);
			glTexCoord2f( (float)x / (terrain->length-1) , (float)z5 / (terrain->width-1));
			glVertex3f(x,terrain->twodpointer[x][z5],z5);

			v = terrain->normals[x+1][z5];
			glNormal3f(v.comp[0],v.comp[1],v.comp[2]);
			glTexCoord2f( (float)(x+1) / (terrain->length-1) , (float)(z5) / (terrain->width-1));
			glVertex3f(x+1,terrain->twodpointer[x+1][z5],z5);
		}
		glEnd();
	}
	//autoUpdateObj will handle all physics
	//called only if the game is not over and if its not a practice mode
	if (!isGameOver && !isPaused) autoUpdateObj();

	//render the hud if not the practice mode
	if (!ifPractice) render_hud();

	//finally swap the buffers
	glutSwapBuffers();
}


//calls the display function every 25 msec
void update(int value) {

	//timeElapsedCounter keeps track of the number of milliseconds passed till now
	if (!isPaused) timeElapsedCounter+=140; 				
	glutPostRedisplay();
	glutTimerFunc(TIME_BETWEEN_UPDATES, update, 0);
}


//the main function
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow(WINDOW_TITLE);
	//scan the number passed and initialize the game
	if (argc != 2) {
		return 1;
	}
	else{
		string te = argv[1];
		int trackno = atoi(te.c_str());

		//check and see if the game is a practice mode game
		if (trackno == 11) {
			ifPractice = true;
			trackno =2 ;
		}
		initRendering(trackno);
	}
	glutFullScreen();				//launch the game in full screen initially
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutKeyboardUpFunc(keyRelease);
	glutReshapeFunc(handleResize);
	glutSpecialFunc(handleSpecialKeys);
	glutTimerFunc(TIME_BETWEEN_UPDATES, update, 0);
	glutMainLoop();
	return 0;
}
