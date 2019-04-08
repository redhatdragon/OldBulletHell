#pragma once
//#include "../Objects/Objects.h"

class Actors;
class Actor;
class PhysicsBody;

class SpatialHash {
	#ifndef HASH_LIMIT
	#define HASH_LIMIT 5000
	#endif
	#ifndef HASH_SIZE
	#define HASH_SIZE 10
	#endif
	Actors *hash[HASH_LIMIT][HASH_LIMIT];
public:
	int threadDoneCounter;
	SpatialHash();
	static int threadedInitFillHash(void *data);
	void addActor(PhysicsBody &_b);
	void removeActor(PhysicsBody &_b);
	Actors *getActors(PhysicsBody &_b);
};