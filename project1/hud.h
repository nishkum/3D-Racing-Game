/*!
 * clock.h
 *
 *  Created on: 07-Sep-2013
 *      Author: harsh
 */

void initHud(); 				///<initializes the Hud parameters
void gameOver();				///<this function is called once the player finishes the game , i.e. when either the time is up
								///<or when the player collects all bonus markers

void render_hud();				///<the main function for rendering HUD every time the scene is drawn