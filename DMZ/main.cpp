#include <iostream>
#include <cstring>
#include <vector>
#include <SDL2/SDL.h>
//#include "include/SDL2/SDL_Net.h"
#include "Graphics.h"  //Personally predefined graphics functions in c.
#include "BluePyroGameEngine/Level.cpp"  //Wish i could get rid of this include.
#include "myActors.h"  //Our custome actors for the game.  Inherits from class Actor and is easy to make new actos with.
using namespace std;

/************************************************************************************************************
This Level::display() function is used to define our own method for displaying the actors from the level.
This is necessary to allow portability between different graphics libraries when "transforming" the levels
or doing any camera related stuff as well as keeping track of draw calls if so desired.
HINT HINT If i have an invisable actor i want to see along with everything else i could place some drawing
code here to make something like an outline or dot where every actor in the level is...  or add post
processing effects if so desired.  Perhaps there's a better way then exposing the display function?
************************************************************************************************************/
__forceinline void Level::display(){
	for (int i = 0; i < actorCount; i++) {
		actor[i]->display();  //each actor inside our level is running it's own drawing code.
	}
}

Level *level;

int main(int argc, char* args[]){
	setup(120,120,1200,800);  //Inits SDL.
	level = new Level();  //Inits our level.

	#include "SpawnList\floors.txt"  //spawns our flooring.
	Player *p = new Player(250, 250);  //Creates a new player at coords 50x50.
	level->camera = p;  //attaches a simple camera actor to the player to be referenced later for translating the level.
	level->addActor(*p);  //Adds our newly created player to the level.
	#include "SpawnList\walls.txt"  //spawns our walls.
	#include "SpawnList\items.txt"  //spawns our items.
	#include "SpawnList\NPCs.txt"  //spawns our NPC's.

	bool running = true;  //Is our game loop running?
	
	while(!quite){  //--GAME LOOP!--//
		clear();  //Clears garbage form SDL.

		level->run();  //Runs our level(movement and physics as well as logic related stuff).
		level->display();  //Prepares everything(including our actors) for displaying.

		//draw healthbar.
		rect(20,20,100,20,150,150,140);
		rect(20,20,(float(p->health)/1000)*100,20,180,0,15);
		
		render();  //Causes SDL to draw what we made to our window.

		if (p->health <= 0) {
			quite = true;  //brake game loop if player health below 0.
		}
	}
	endGame();  //Necessary to properly shutdown SDL.
}