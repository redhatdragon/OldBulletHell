#include "Ui.h"
#include <string>

using namespace std;

#ifndef ADD_ACTOR_TO_UI
#define ADD_ACTOR_TO_UI(className) \
a = new className(_x,_y); \
level->addActor(*a); \
level->removeActor(a->id); \
addBox(*new ActorBox(_x, _y, _w, _h, _r, _g, _b, *a));
#endif

ActorBoxCollection::ActorBoxCollection(int _x, int _y, int _w, int _h, int _r, int _g, int _b, Level *_level) {
	x = _x; y = _y; w = _w; h = _h;
	r = _r; g = _g; b = _b;
	level = _level;
	currentBox = currentCatagory =0;
	gridScale = 50;
	spawnAmmountWidth = spawnAmmountHeight = spawnScale = 1;

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 10; j++) {
			box[i][j] = NULL;
		}
	}

	catagoryArrows = new WidgetArrows(1260,90,&currentCatagory);
	gridScaleArrows = new WidgetArrowsDecade(1260, 150, &gridScale);
	spawnAmmountWidthArrows = new WidgetArrowsDecade(1260, 210, &spawnAmmountWidth);
	spawnAmmountHeightArrows = new WidgetArrowsDecade(1260, 270, &spawnAmmountHeight);
	spawnScaleArrows = new WidgetArrowsDecade(1260, 330, &spawnScale);

	Actor *a = new WallTileCross(_x, _y);
	//Before adding the actor we need to add it and remove it from the level.
	//This prevents the program from crashing.  This is assumed to be a gcc bug.
	level->addActor(*a);
	level->removeActor(a->id);
	addBox(*new ActorBox(_x, _y, _w, _h, _r, _g, _b, *a));
	ADD_ACTOR_TO_UI(WallTileCross2)
	ADD_ACTOR_TO_UI(WallTileCross3)
	ADD_ACTOR_TO_UI(Tree)
	currentCatagory = 1;
	ADD_ACTOR_TO_UI(FloorTileWood)
	ADD_ACTOR_TO_UI(FloorTileWood2)
	ADD_ACTOR_TO_UI(FloorTileWood3)
	ADD_ACTOR_TO_UI(Grass)
	ADD_ACTOR_TO_UI(IceFloor)
	currentCatagory = 2;
	ADD_ACTOR_TO_UI(EnemyPawn1)
	currentCatagory = 0;
}
void ActorBoxCollection::placeActor(int _x, int _y) {
	Actor *a = box[currentBox][currentCatagory]->actor->clone();
	a->p->position->set(_x, _y);
	if (PhysicsBodyAABB *b = dynamic_cast<PhysicsBodyAABB*>(a->p)) {
		b->width = b->width*spawnScale;
		b->height = b->height*spawnScale;
	}else if (PhysicsBodyCircle *b = dynamic_cast<PhysicsBodyCircle*>(a->p)) {
		b->radious = b->radious*spawnScale;
	}
	level->addActor(*a);
	cout << "Added another actor." << endl;
}
void ActorBoxCollection::display() {

	//Display actor.
	text("Current Actor is: ", windowWidth - 220, 0, 100, 20, 155,225,40);
	if (currentBox >= 0 && currentBox < 100 && currentCatagory >= 0 && currentCatagory < 10) {
		if (box[currentBox][currentCatagory] != NULL) {
			box[currentBox][currentCatagory]->actor->p->position->set(level->camera->getX() + (x + w / 2 - windowWidth / 2), level->camera->getY() + (y + h / 2 - windowHeight / 2));
			box[currentBox][currentCatagory]->display();
		}
	}

	//Display current catagory.
	string catagory;
	if (currentCatagory == 0) {
		catagory = "Current catagory is: "  "Walls";
	}else if(currentCatagory == 1){
		catagory = "Current catagory is: "  "Floors";
	}else if(currentCatagory == 2){
		catagory = "Current catagory is: "  "Enemies";
	}else{
		catagory = "Current catagory is: "  "NULL";
	}
	char *c = &catagory[0];
	text(c, windowWidth - 220, 60, 200, 30, 155, 225, 40);
	catagoryArrows->display();

	catagory = "grid size is: "+to_string(gridScale);
	c = &catagory[0];
	text(c, windowWidth - 220, 120, 120, 30, 155, 225, 40);
	gridScaleArrows->display();

	catagory = "spawn ammount WIDTH: " + to_string(spawnAmmountWidth);
	c = &catagory[0];
	text(c, windowWidth - 220, 180, 200, 30, 155, 225, 40);
	spawnAmmountWidthArrows->display();

	catagory = "spawn ammount HEIGHT: " + to_string(spawnAmmountHeight);
	c = &catagory[0];
	text(c, windowWidth - 220, 240, 200, 30, 155, 225, 40);
	spawnAmmountHeightArrows->display();

	catagory = "spawn SCALE: " + to_string(spawnScale);
	c = &catagory[0];
	text(c, windowWidth - 220, 300, 120, 30, 155, 225, 40);
	spawnScaleArrows->display();
}