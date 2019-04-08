#pragma once
#include "Physics.h"
#include "../GameMacros.h"
#include "../Objects/Object.h"
#include "../Objects/Objects.h"
#include "SpatialHash.h"

class Actors;
//class Actor;
//class PhysicsBody;

#define NO_HASH 0
#define SPATIAL_HASH 1
#define PIXEL_HASH 2

//Change the result dependent on the type of engine
//you wish to use.
//Example: #define PHYSICS_ENGINE_TYPE NO_HASH
#define PHYSICS_ENGINE_TYPE SPATIAL_HASH



/*************************************************
This is the layout for the namespace.
If you wish to edit or add another type of physics
engine all you have to do is go to
PhysicsEngineInl.h and make your edits there.
The type of engine used is determined by the macro
PHYSICS_ENGINE_TYPE to allow ease of switching for
whatever type of game is necessary.
*************************************************/
/*namespace PhysicsEngine{
	int bodyCount;
	int dynamicBodyCount;
	extern PhysicsBody *body[MAX_ACTORS];

	extern __forceinline void constructor();
	extern __forceinline void addBody(PhysicsBody &_body);
	extern __forceinline void removeBody(int _id);
	extern __forceinline void translate(PhysicsBody &_body, int _x, int _y);

	extern void simulate();
	extern __forceinline void collisionDetection();
	extern __forceinline void collisionResponse();
	extern void run();
	
	#include "PhysicsEngineInl.h"  //don't move this for cross compiler reasons.
}*/

class PhysicsEngine {
	int bodyCount;
	int dynamicBodyCount;
	PhysicsBody *body[MAX_ACTORS];
	#if PHYSICS_ENGINE_TYPE == SPATIAL_HASH
	//to adjust size go to SpatialHash.h and tweek HASH_LIMIT
	SpatialHash spatialHash;
	#endif

public:
	PhysicsEngine();

	void addBody(PhysicsBody &_body);
	void removeBody(int _id);
	void translate(PhysicsBody &_body, int _x, int _y);
	Actors *dotIntersectBodies(Vector &d);
	void deleteActorsThatIntersectDot(Vector &d);

	void simulate();
	__forceinline void collisionDetection();
	__forceinline void collisionResponse();
	void run();
};

extern PhysicsEngine *physicsEngine;