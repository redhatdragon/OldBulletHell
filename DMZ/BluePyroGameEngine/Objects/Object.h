#pragma once
#include "../Physics/Physics.h"
#include "../Physics/PhysicsEngine.h"

class Physics;
class Level;
//class Objects;

class Object{
public:
	//float x,y;
	//int s1,s2;
	virtual ~Object(){
		
	}
	virtual void display(){
		
	}
	virtual void run(){
		
	}
};

class Actor: public Object{
public:
	Level *level;
	PhysicsBody *p;
	int id;  //placeholder to help deletion.  NO TOUCHY!
	Actor(){
		setup();
	}
	/*Actor(int _x, int _y){
		//x = _x; y = _y;

		setup();
	}*/
	__forceinline void setup(){
		level = nullptr; p = nullptr;
	}
	__forceinline float getX() {
		return p->position->x;
	}
	__forceinline float getY() {
		return p->position->y;
	}
	__forceinline Vector *getPos() {
		return p->position;
	}
	virtual ~Actor();

	void del();

	__forceinline void translate(int _x, int _y);
	virtual void eventOverlap(Actor &_actor);
	virtual string spawnString() {}
	virtual Actor* clone() = 0;
};