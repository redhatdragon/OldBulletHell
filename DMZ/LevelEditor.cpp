#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <SDL2/SDL.h>
//#include "include/SDL2/SDL_Net.h"
#include "Graphics.h"  //Personally predefined graphics functions in c.
#include "BluePyroGameEngine/Level.cpp"  //Wish i could get rid of this include.
#include "myActors.h"  //Our custome actors for the game.  Inherits from class Actor and is easy to make new actos with.
#include "Ui.h"
using namespace std;

/************************************************************************************************************
This Level::display() function is used to define our own method for displaying the actors from the level.
This is necessary to allow portability between different graphics libraries when "transforming" the levels
or doing any camera related stuff as well as keeping track of draw calls if so desired.
HINT HINT If i have an invisable actor i want to see along with everything else i could place some drawing
code here to make something like an outline or dot where every actor in the level is...  or add post
processing effects if so desired.  Perhaps there's a better way then exposing the display function?
************************************************************************************************************/
__forceinline void Level::display() {
	for (int i = 0; i < actorCount; i++) {
		actor[i]->display();  //each actor inside our level is running it's own drawing code.
	}
}

Level *level;
ActorBoxCollection *actorBoxCollection;

int main(int argc, char* args[]) {
	setup(0, 20, 1420, 800);  //Inits SDL.
	//windowWidth = 1200;  //reserves room for our level editing ui.
	level = new Level();  //Inits our level.
	actorBoxCollection = new ActorBoxCollection(windowWidth-50,0,50,50,125,125,125, level);

	#include "SpawnList\floors.txt"  //spawns our flooring.
	Player *p = new Player(250, 250);  //Creates a new player at coords 50x50.
	p->canFire = false;
	level->camera = p;  //attaches a simple camera actor to the player to be referenced later for translating the level.
	level->addActor(*p);  //Adds our newly created player to the level.
	#include "SpawnList\walls.txt"  //spawns our walls.
	#include "SpawnList\items.txt"  //spawns our items.
	#include "SpawnList\NPCs.txt"  //spawns our NPC's.

	bool running = true;  //Is our game loop running?

	while (!quite) {  //--GAME LOOP!--//
		clear();  //Clears garbage form SDL.

		level->editorRun();  //Runs our level(movement and physics as well as logic related stuff).
		level->display();  //Prepares everything(including our actors) for displaying.
		int flipAmmount = 0;
		static int gridScale = 50;
		static bool flippingLeft = false, flippingRight = false;
		static bool flippingUp = false, flippingDown = false;
		if (leftk) {
			if (!flippingLeft) {
				flipAmmount--; flippingLeft = true;
			}
		}else{
			flippingLeft = false;
		}if (rightk) {
			if (!flippingRight) {
				flipAmmount++; flippingRight = true;
			}
		}else{
			flippingRight = false;
		}
		gridScale = actorBoxCollection->gridScale;

		//Mouse behaviour
		static bool pressingLeftMouse = false;
		if (leftMouseDown) {
			if (mouseX >= 0 && mouseX < 1200 && mouseY >= 0 && mouseY < 800) {
				if (!pressingLeftMouse) {
					for (int i = 0; i < actorBoxCollection->spawnAmmountWidth; i++) {
						for (int j = 0; j < actorBoxCollection->spawnAmmountHeight; j++) {
							Vector v = Vector(mouseX + level->camera->getX() - windowWidth / 2, mouseY + level->camera->getY() - windowHeight / 2);
							v.round(gridScale);
							v.add(gridScale / 2 + (i*gridScale), gridScale / 2 + (j*gridScale));
							actorBoxCollection->placeActor(v.x, v.y);
							pressingLeftMouse = true;
						}
					}
					/*Vector v = Vector(mouseX + level->camera->getX() - windowWidth / 2, mouseY + level->camera->getY() - windowHeight / 2);
					v.round(gridScale);
					v.add(gridScale/2,gridScale/2);
					actorBoxCollection->placeActor(v.x, v.y);
					pressingLeftMouse = true;*/
				}
			}else{
				if (!pressingLeftMouse) {
					actorBoxCollection->clicked();
					pressingLeftMouse = true;
				}
			}
		}else{
			pressingLeftMouse = false;
		}
		if (rightMouseDown) {
			if (mouseX >= 0 && mouseX < 1200 && mouseY >= 0 && mouseY < 800) {
				cout << "HIT" << endl;
				Vector v = Vector(mouseX + level->camera->getX() - windowWidth / 2, mouseY + level->camera->getY() - windowHeight / 2);
				v.round(gridScale);
				v.add(gridScale / 2, gridScale / 2);
				physicsEngine->deleteActorsThatIntersectDot(v);
			}
		}

		rect(1200, 0, 220, 800, 10, 10, 10);  //clear right side of screen for editor.
		actorBoxCollection->selectDifferentActor(flipAmmount);
		actorBoxCollection->display();

		render();  //Causes SDL to draw what we made to our window.
	}

	/************************************************************************************************************
	The following code is used to write created actors to their corrisponding files.  This is used so that when
	recompiling the game all of the actor's created with the level editor are there to be compiled directly
	into the level.  First we delete the files if they exist to prevent duplication then proceed to write
	to the files we just deleted.  Last step is to close the files once everything else is done.
	TODO:  Add some macro's to shorten some of this code.
	************************************************************************************************************/
	remove("SpawnList/floors.txt");
	remove("SpawnList/walls.txt");
	remove("SpawnList/NPCs.txt");
	ofstream floors;
	ofstream walls;
	ofstream items;
	ofstream npcs;
	floors.open("SpawnList/floors.txt");
	walls.open("SpawnList/walls.txt");
	items.open("SpawnList/items.txt");
	npcs.open("SpawnList/NPCs.txt");

	for (int i = 0; i < level->actorCount; i++) {
		Actor *a = level->actor[i];
		if (dynamic_cast<Wall*> (a)) {
			walls << a->spawnString();
		}else if (dynamic_cast<Floor*> (a)) {
			floors << a->spawnString();
		}
		else if (dynamic_cast<NPC*> (a)) {
			npcs << a->spawnString();
		}
	}
	npcs.close();
	items.close();
	walls.close();
	floors.close();

	endGame();  //Necessary to properly shutdown SDL.
}
