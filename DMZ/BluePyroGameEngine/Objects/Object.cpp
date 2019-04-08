#include "Object.h"
#include "../Level.h"

Actor::~Actor(){
	if (p != nullptr) {
		p->del();
	}
	if (level != nullptr) {
		level->removeActor(id);
	}
}

void Actor::del() {
	level->addActorToDeletePool(*this);
}

__forceinline void Actor::translate(int _x, int _y) {
	//x = _x; y = _y;
	physicsEngine->translate(*p, _x, _y);
}

void Actor::eventOverlap(Actor &_actor) {
	
}