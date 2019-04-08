#include "../../include/SDL2/SDL.h"  //TODO:  need to fix this.
#include "../../include/SDL2/SDL_thread.h"  //TODO:  need to fix this.
/*  TODO:  From this link.  http://lazyfoo.net/SDL_tutorials/lesson33/
*nix user may have to include X11:
#include "X11/Xlib.h"

You'll also have to call XInitThreads() in your initialization function and link with -lX11
*/
#include "SpatialHash.h"
#include "../GameMacros.h"
#include "../Objects/Objects.h"
#include "Physics.h"
#include "../Math/Math.h"
#include <iostream>

typedef struct {
	SpatialHash *thisObject;
	int param1;
	int param2;
} ThreadData2I;

int SpatialHash::threadedInitFillHash(void *data) {
	ThreadData2I *tdata = (ThreadData2I*)data;
	SpatialHash *thisObject = tdata->thisObject;
	int beginning = tdata->param1;
	int ending = tdata->param2;
	if(ending < HASH_LIMIT){
		for (int i = beginning; i < ending; i++) {
			for (int j = 0; j < HASH_LIMIT; j++) {
				thisObject->hash[i][j] = new Actors();
			}
		}
	}else{
		for (int i = beginning; i < HASH_LIMIT; i++) {
			for (int j = 0; j < HASH_LIMIT; j++) {
				thisObject->hash[i][j] = new Actors();
			}
		}
	}
	thisObject->threadDoneCounter++;
	delete (ThreadData2I*)data;
	return 0;
}

SpatialHash::SpatialHash() {
	threadDoneCounter = 0;
	int threadCount = SDL_GetCPUCount();

	if(HASH_LIMIT % threadCount != 0){
		threadCount++;
	}

	#ifdef MULTITHREADED
	SDL_Thread **myThread;
	myThread = new SDL_Thread*[threadCount];

	for(int i = 0; i < threadCount; i++){
		ThreadData2I *data = new ThreadData2I;
		data->thisObject = this;
		data->param1 = i*(HASH_LIMIT/threadCount);
		data->param2 = (i+1)*(HASH_LIMIT/threadCount);
		myThread[i] = SDL_CreateThread(threadedInitFillHash, "Thread: "+i, data);
	}
	while (threadDoneCounter != threadCount) {
		//wait till threads are all done.
	}
	threadDoneCounter = 0;

	#else
	for (int i = 0; i < HASH_LIMIT; i++) {
		for (int j = 0; j < HASH_LIMIT; j++) {
			hash[i][j] = new Actors(0);
		}
	}
	#endif
}

void SpatialHash::addActor(PhysicsBody &_b) {
	int x = _b.position->x;
	int y = _b.position->y;
	int width, height;
	if(PhysicsBodyAABB *tb = dynamic_cast<PhysicsBodyAABB*>(&_b)){
		width = tb->width;
		height = tb->height;
	}else if(PhysicsBodyCircle *tb = dynamic_cast<PhysicsBodyCircle*>(&_b)){
		width = height = tb->radious*2;
	}
	int iLimit = width / HASH_SIZE;
	if (width % HASH_SIZE != 0) {
		iLimit++;
	}
	int jLimit = height / HASH_SIZE;
	if (height % HASH_SIZE != 0) {
		jLimit++;
	}
	//cout << iLimit << ", " << jLimit << endl;
	//get the hash that our physics bodie's position is sitting in.
	int startingHashX = (x + 1)/HASH_SIZE;
	if ((x + 1) % HASH_SIZE != 0) { startingHashX++; } startingHashX--;
	int startingHashY = (y + 1) / HASH_SIZE;
	if ((y + 1) % HASH_SIZE != 0) { startingHashY++; } startingHashY--;
	for(int i = -iLimit; i <= iLimit; i++){
		for(int j = -jLimit; j <= jLimit; j++){
			int currentHashX = startingHashX + i;
			int currentHashY = startingHashY + j;
			//double checking that the hash we are observing is actually inside the table(otherwise skip).
			if (currentHashX >= 0 && currentHashX < HASH_LIMIT && currentHashY >= 0 && currentHashY < HASH_LIMIT) {
				//check if the physics body is probably inside the hash.
				if (rectInRect(x,y,width,height,currentHashX*HASH_SIZE+ HASH_SIZE/2,currentHashY*HASH_SIZE+HASH_SIZE/2,HASH_SIZE,HASH_SIZE)) {
					hash[startingHashX + i][startingHashY + j]->addActorNonDup(_b.actorHandle);
				}
			}
		}
	}
}

void SpatialHash::removeActor(PhysicsBody &_b) {
	int x = _b.position->x;
	int y = _b.position->y;
	int width, height;
	if (PhysicsBodyAABB *tb = dynamic_cast<PhysicsBodyAABB*>(&_b)) {
		width = tb->width;
		height = tb->height;
	}
	else if (PhysicsBodyCircle *tb = dynamic_cast<PhysicsBodyCircle*>(&_b)) {
		width = height = tb->radious * 2;
	}
	int iLimit = width / HASH_SIZE;
	if (width % HASH_SIZE != 0) {
		iLimit++;
	}
	int jLimit = height / HASH_SIZE;
	if (height % HASH_SIZE != 0) {
		jLimit++;
	}
	//get the hash that our physics bodie's position is sitting in.
	int startingHashX = (x + 1) / HASH_SIZE;
	if ((x + 1) % HASH_SIZE != 0) { startingHashX++; } startingHashX--;
	int startingHashY = (y + 1) / HASH_SIZE;
	if ((y + 1) % HASH_SIZE != 0) { startingHashY++; } startingHashY--;
	for (int i = -iLimit; i <= iLimit; i++) {
		for (int j = -jLimit; j <= jLimit; j++) {
			int currentHashX = startingHashX + i;
			int currentHashY = startingHashY + j;
			//double checking that the hash we are observing is actually inside the table(otherwise skip).
			if (startingHashX + i >= 0 && startingHashX + i <= HASH_LIMIT && startingHashY + j >= 0 && startingHashY + j <= HASH_LIMIT) {
				//check if the physics body is probably inside the hash.
				if (rectInRect(x, y, width, height, currentHashX*HASH_SIZE + HASH_SIZE / 2, currentHashY*HASH_SIZE + HASH_SIZE / 2, HASH_SIZE, HASH_SIZE)) {
					hash[startingHashX + i][startingHashY + j]->removeActor(_b.actorHandle);
				}
			}
		}
	}
}

Actors *SpatialHash::getActors(PhysicsBody &_b) {
	Actors *actors = new Actors(20);
	int x = _b.position->x;
	int y = _b.position->y;
	int width, height;
	if (PhysicsBodyAABB *tb = dynamic_cast<PhysicsBodyAABB*>(&_b)) {
		width = tb->width;
		height = tb->height;
	}
	else if (PhysicsBodyCircle *tb = dynamic_cast<PhysicsBodyCircle*>(&_b)) {
		width = height = tb->radious * 2;
	}
	int iLimit = width / HASH_SIZE;
	if (width % HASH_SIZE != 0) {
		iLimit++;
	}
	int jLimit = height / HASH_SIZE;
	if (height % HASH_SIZE != 0) {
		jLimit++;
	}
	//get the hash that our physics bodie's position is sitting in.
	int startingHashX = (x + 1) / HASH_SIZE;
	if ((x + 1) % HASH_SIZE != 0) { startingHashX++; } startingHashX--;
	int startingHashY = (y + 1) / HASH_SIZE;
	if ((y + 1) % HASH_SIZE != 0) { startingHashY++; } startingHashY--;
	for (int i = -iLimit; i <= iLimit; i++) {
		for (int j = -jLimit; j <= jLimit; j++) {
			int currentHashX = startingHashX + i;
			int currentHashY = startingHashY + j;
			//double checking that the hash we are observing is actually inside the table(otherwise skip).
			if (startingHashX + i >= 0 && startingHashX + i <= HASH_LIMIT && startingHashY + j >= 0 && startingHashY + j <= HASH_LIMIT) {
				//check if the physics body is probably inside the hash.
				if (rectInRect(x, y, width, height, currentHashX*HASH_SIZE + HASH_SIZE / 2, currentHashY*HASH_SIZE + HASH_SIZE / 2, HASH_SIZE, HASH_SIZE)) {
					actors->addActorsNonDup(hash[startingHashX + i][startingHashY + j]);
				}
			}
		}
	}
	return actors;
}