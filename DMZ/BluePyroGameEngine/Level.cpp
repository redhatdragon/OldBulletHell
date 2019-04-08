#include "Level.h"
#include "Physics\PhysicsEngine.cpp"  //below
/*-------------------------------------------
Necessary for gcc for some reason.
Need to fix the files so source need not be
included into each other directly.
Must research about custome compiling.
-------------------------------------------*/

void Level::addActor(Actor &a){
	actor[actorCount] = &a;
	a.id = actorCount;
	a.level = this;
	actorCount++;
}

void Level::addActorToDeletePool(Actor &_actor) {
	for (int i = 0; i < deleteActorPoolCount; i++) {
		if (&_actor == deleteActorPool[i]) {
			return;  //return if actor is already in deletion pool.
		}
	}
	deleteActorPool[deleteActorPoolCount] = &_actor;
	deleteActorPoolCount++;
}

void Level::removeActor(int _id){
	actor[_id] = actor[actorCount - 1];
	actor[_id]->id = _id;
	actorCount--;
}

void Level::emptyDeleteActorPool() {
	for (int i = 0; i < deleteActorPoolCount; i++) {
		delete deleteActorPool[i];
	}
	deleteActorPoolCount = 0;
}

void Level::run() {
	for (int i = 0; i < actorCount; i++) {
		actor[i]->run();
	}
	physicsEngine->run();
	emptyDeleteActorPool();
}

void Level::editorRun() {
	camera->run();
	physicsEngine->run();
	emptyDeleteActorPool();

	//draw hash table's domain.
	int hashOffset = HASH_LIMIT*HASH_SIZE;
	int offsetX = camera->getX() - windowWidth / 2;
	int offsetY = camera->getY() - windowHeight / 2;
	rect(0-offsetX,0-offsetY,hashOffset-offsetX,hashOffset-offsetY,125,125,125);
}