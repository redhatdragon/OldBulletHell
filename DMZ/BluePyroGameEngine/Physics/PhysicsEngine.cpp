#include "PhysicsEngine.h"
#include "../Level.h"
#include "SpatialHash.h"
PhysicsEngine *physicsEngine;

//TODO:  Finish the collision response.
//I really hate using a class over a good namespace however i have no choice.

/*namespace PhysicsEngine{
	PhysicsBody *body[MAX_ACTORS];
	void simulate() {
		for (int i = 0; i < bodyCount; i++) {
			for (int j = i + 1; j < bodyCount; j++) {
				if (body[i]->bodyInBody(*body[j])) {
					//Actor *a = body[j]->actorHandle;
					//body[i]->actorHandle->eventOverlap(*a);
					body[j]->actorHandle->eventOverlap(*body[i]->actorHandle);
				}
			}
		}
	}
	__forceinline void collisionDetection() {

	}
	__forceinline void collisionResponse() {

	}
	void run() {
		simulate();
		collisionDetection();
		collisionResponse();
	}
}*/

Actors *PhysicsEngine::dotIntersectBodies(Vector &d) {
	Actors *actors = new Actors();
	for (int i = 0; i < bodyCount; i++) {
		if (body[i]->dotInBody(d)) {
			cout << "hit" << endl;
			actors->addActor(body[i]->actorHandle);
		}
	}
	return actors;
}
void PhysicsEngine::deleteActorsThatIntersectDot(Vector &d) {
	for (int i = 0; i < bodyCount; i++) {
		if (body[i]->dotInBody(d)) {
			cout << "hit" << endl;
			//body[i]->actorHandle->level->removeActor(body[i]->actorHandle->id);
			//delete body[i];
			body[i]->actorHandle->del();
		}
	}
}
__forceinline void PhysicsEngine::collisionDetection() {

}
__forceinline void PhysicsEngine::collisionResponse() {

}
void PhysicsEngine::run() {
	simulate();
	collisionDetection();
	collisionResponse();
}







#if PHYSICS_ENGINE_TYPE == NO_HASH
__forceinline PhysicsEngine::PhysicsEngine() {
	bodyCount = dynamicBodyCount = 0;
}
void PhysicsEngine::addBody(PhysicsBody &_body) {
#if BP_SAFE_MODE == 1
	if (bodyCount < MAX_ACTORS) {
		body[bodyCount] = &_body;
		body[bodyCount]->id = bodyCount;
		bodyCount++;
	}
	else {
		cout << "ERROR: Too many bodies for array." << endl;
		cout << "MEMORYLEAK: Unable to cleanup extra body." << endl;
	}
#else
	body[bodyCount] = &_body; body[bodyCount]->id = bodyCount; bodyCount++;
#endif
}
void PhysicsEngine::removeBody(int _id) {
	if (_id < bodyCount - 1) {
		bodyCount--;
		body[_id] = body[bodyCount];
		body[_id]->id = _id;
	}
	else {
		bodyCount--;
	}
}
void PhysicsEngine::translate(PhysicsBody &_body, int _x, int _y) {
	
}
void PhysicsEngine::simulate() {
	//TODO: Need to create some collision response.
	for (int i = 0; i < bodyCount; i++) {
		if (body[i]->dynamic) {
			body[i]->move();
			for (int j = 0; j < bodyCount; j++) {
				if (i != j) {
					if (body[i]->bodyInBody(*body[j])) {
						if (body[i]->solid && body[j]->solid) {
							body[i]->velocity->scale(-1);
							body[i]->move(); //Reverse object to it's old pos.
							body[i]->velocity->scale(-1);
							Actor *a = body[i]->actorHandle;
							Actor *b = body[j]->actorHandle;
							float totalFriction = ((body[i]->friction + body[j]->friction) / 2) - 1;
							body[i]->velocity->scale(-1 * -totalFriction);
							//body[j]->velocity->scale(-1 * -totalFriction);
							a->eventOverlap(*b);
							//b->eventOverlap(*a);
						}else{
							Actor *a = body[i]->actorHandle;
							Actor *b = body[j]->actorHandle;
							a->eventOverlap(*b);
							//sb->eventOverlap(*a);
						}
					}
				}
			}
		}
	}
}



//PIXEL BACKGROUND ENGINE
#elif PHYSICS_ENGINE_TYPE == PIXEL_HASH
#define PIXEL_HASH_WIDTH 1920
#define PIXEL_HASH_HEIGHT 1080
#define PIXEL_HASH_SCREENCOUNT 9
#define PIXEL_HASH_SCREENCOUNT_ROOT 3
//Pixel *pixel;
Pixel pixel
[PIXEL_HASH_WIDTH*PIXEL_HASH_SCREENCOUNT_ROOT]
[PIXEL_HASH_HEIGHT*PIXEL_HASH_SCREENCOUNT_ROOT];

__forceinline PhysicsEngine::PhysicsEngine() {
	bodyCount = dynamicBodyCount = 0;
	for (uint16_t i = 0; i < PIXEL_HASH_WIDTH*PIXEL_HASH_SCREENCOUNT_ROOT; i++) {
		for (uint16_t j = 0; j < PIXEL_HASH_HEIGHT*PIXEL_HASH_SCREENCOUNT_ROOT; j++) {
			pixel[i][j] = Pixel(i, j);
		}
		//cout << i << endl;
	}
}
__forceinline void PhysicsEngine::addBody(PhysicsBody &_body) {
#if BP_SAFE_MODE == 1
	if (bodyCount < MAX_ACTORS) {
		body[bodyCount] = &_body; bodyCount++;
	}
	else {
		cout << "ERROR: Too many bodies for array." << endl;
		cout << "MEMORYLEAK: Unable to cleanup extra body." << endl;
	}
#else
	body[bodyCount] = &_body; bodyCount++;
#endif
}
__forceinline void PhysicsEngine::removeBody(int _id) {
	if (_id < bodyCount - 1) {
		bodyCount--; body[_id] = body[bodyCount];
	}
	else {
		bodyCount--;
	}
}
__forceinline void PhysicsEngine::translate(PhysicsBody &_body, int _x, int _y) {

}
__forceinline void PhysicsEngine::simulate() {
	for (int i = bodyCount; i < bodyCount; i++) {
		for (int j = i + 1; j < bodyCount; j++) {
			body[i]->move();
			if (!body[i]->bodyInBody(*body[j])) {

			}
			else {

			}
		}
	}
}
__forceinline void PhysicsEngine::collisionDetection() {

}
__forceinline void PhysicsEngine::collisionResponse() {

}
__forceinline void PhysicsEngine::run() {
	simulate();
	collisionDetection();
	collisionResponse();
}



#elif PHYSICS_ENGINE_TYPE == SPATIAL_HASH
__forceinline PhysicsEngine::PhysicsEngine():spatialHash() {
	bodyCount = dynamicBodyCount = 0;
	//spatialHash = SpatialHash();
}
void PhysicsEngine::addBody(PhysicsBody &_body) {
#if BP_SAFE_MODE == 1
	if (bodyCount < MAX_ACTORS) {
		body[bodyCount] = &_body;
		body[bodyCount]->id = bodyCount;
		bodyCount++;
		//cout << int(_body.actorHandle) << endl;
		spatialHash.addActor(_body);
}
	else {
		cout << "ERROR: Too many bodies for array." << endl;
		cout << "MEMORYLEAK: Unable to cleanup extra body." << endl;
	}
#else
	body[bodyCount] = &_body; body[bodyCount]->id = bodyCount; bodyCount++;
#endif
}
void PhysicsEngine::removeBody(int _id) {
	spatialHash.removeActor(*body[_id]);
	if (_id < bodyCount - 1) {
		bodyCount--;
		body[_id] = body[bodyCount];
		body[_id]->id = _id;
	}else{
		bodyCount--;
	}
}
void PhysicsEngine::translate(PhysicsBody &_body, int _x, int _y) {

}
void PhysicsEngine::simulate() {
	//TODO: Need to create some collision response.
	/*for (int i = 0; i < bodyCount; i++) {
		if (body[i]->dynamic) {
			body[i]->move();
			for (int j = 0; j < bodyCount; j++) {
				if (i != j) {
					if (body[i]->bodyInBody(*body[j])) {
						if (body[i]->solid && body[j]->solid) {
							body[i]->velocity->scale(-1);
							body[i]->move(); //Reverse object to it's old pos.
							body[i]->velocity->scale(-1);
							Actor *a = body[i]->actorHandle;
							Actor *b = body[j]->actorHandle;
							float totalFriction = ((body[i]->friction + body[j]->friction) / 2) - 1;
							body[i]->velocity->scale(-1 * -totalFriction);
							//body[j]->velocity->scale(-1 * -totalFriction);
							a->eventOverlap(*b);
							//b->eventOverlap(*a);
						}else{
							Actor *a = body[i]->actorHandle;
							Actor *b = body[j]->actorHandle;
							a->eventOverlap(*b);
							//sb->eventOverlap(*a);
						}
					}
				}
			}
		}
	}*/
	for (int i = 0; i < bodyCount; i++) {
		PhysicsBody *b1 = body[i];
		if (b1->dynamic) {
			spatialHash.removeActor(*b1);
			b1->move();
			Actors *actors = spatialHash.getActors(*b1);
			for (int j = 0; j < actors->count; j++) {
				PhysicsBody *b2 = actors->actor[j]->p;
				if (b1 != b2) {
					if (b1->bodyInBody(*b2)) {
						if (b1->solid && b2->solid) {
							b1->velocity->scale(-1);
							b1->move(); //Reverse object to it's old pos.
							b1->velocity->scale(-1);
							Actor *a = b1->actorHandle;
							Actor *b = b2->actorHandle;
							float totalFriction = ((b1->friction + b2->friction) / 2) - 1;
							b1->velocity->scale(-1 * -totalFriction);
							a->eventOverlap(*b);
						}else{
							Actor *a = b1->actorHandle;
							Actor *b = b2->actorHandle;
							a->eventOverlap(*b);
						}
					}
				}
			}
			//cout << "hit1" << endl;
			delete actors;
			//cout << "hit2" << endl;
			spatialHash.addActor(*b1);
		}
	}
}




#else
#error "No PhysicsEngine selected"
#endif
//----[end]----//