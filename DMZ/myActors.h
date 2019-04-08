#pragma once
#include <sstream>
#include "Graphics.h"
#include "BluePyroGameEngine\Objects\Object.h"
#include "shotTypeMacros.h"
#include "BluePyroGameEngine\Math\Math.h"

#ifndef to_string  //our version of to_string for compilation.  Interesting link on gcc...
//http://stackoverflow.com/questions/12975341/to-string-is-not-a-member-of-std-says-g
#define to_string( x ) static_cast< ostringstream & >( \
        ( ostringstream() << dec << x ) ).str()
#endif

class Pawn :public Actor {
public:
	Pawn() {
		direction.set(0, 1);
	}
	__forceinline void setDirection(float _x, float _y) {
		direction.set(_x, _y);
	}
	__forceinline void setDirectionAndNormalize(float _x, float _y) {
		direction.set(_x, _y);
		direction.normalize();
	}
	__forceinline void turnDirection(float _angle) {
		rotatePoint(0, 0, _angle, &direction);
	}
	__forceinline Vector* getDirectionVector() {
		return &direction;
	}
	__forceinline float getDirectionInRadians(){
		return atan2(direction.x,direction.y);
	}
	__forceinline float getDirectionInDegrees() {
		return atan2(direction.x,direction.y) * 180 / M_PI;
	}
private:
	Vector direction;
};
class NPC : public Pawn {
public:
	NPC() {}
	NPC(float _x, float _y, int _w, int _h) {
		p = new PhysicsBodyAABB(_x, _y, _w, _h, *this);
		p->solid = true;
		p->dynamic = true;
		p->friction = .7;
	}
};
class Enemy : public NPC {
public:
	Enemy() {}
	Enemy(float _x, float _y, int _w, int _h) :NPC(_x, _y, _w, _h) {

	}
};

class Player: public Pawn {
public:
	int health;
	float floorDrag;
	bool canMove, canFire;
	Player(){}
	Player(float _x, float _y) {
		p = new PhysicsBodyCircle(_x, _y, 20, *this);  //create a physics body of type circle and make it 20 pixels wide.
		p->dynamic = true;  //make it so the actor can move.
		p->friction = .7;  //the friction(how much it bounces after collision).
		health = 1000;
		floorDrag = .95;  //0 for none and 1 for full.
		canMove = canFire = true;
	}
	void fire();
	virtual void display();
	virtual void run() {
		if(canFire){
			fire();
		}
		if (canMove) {
			int tx = 0; int ty = 0;
			tx = ty = 0;
			#ifndef speed
			#define speed 10*(1/floorDrag)
			#endif
			#ifndef acceleration
			#define acceleration 1
			#endif
			if (wk) {
				ty -= speed/acceleration;
			}if (sk) {
				ty += speed/acceleration;
			}if (ak) {
				tx -= speed/acceleration;
			}if (dk) {
				tx += speed/acceleration;
			}
			Vector *v = p->velocity;
			v->add(tx, ty);
			if (v->x > speed) {
				v->x = speed;
			}
			else if (v->x < -speed) {
				v->x = -speed/acceleration;
			}
			if (v->y > speed) {
				v->y = speed/acceleration;
			}
			else if (v->y < -speed) {
				v->y = -speed;
			}
			v->scale(floorDrag);
			floorDrag = .1;
			#undef speed
			#undef acceleration
		}
	}
	virtual void eventOverlap(Actor &_actor);
	virtual Actor* clone();
};

class PlayerBullet : public Actor {
public:
	PlayerBullet(){}
	PlayerBullet(float _x, float _y, float _vx, float _vy) {
		p = new PhysicsBodyCircle(_x, _y, 4, *this);
		p->velocity->set(_vx, _vy);
		p->dynamic = true;
		p->solid = false;
	}
	virtual void display();
	virtual void eventOverlap(Actor &_actor);
	virtual Actor* clone();
};

class Bullet : public Actor {
public:
	Bullet(){}
	Bullet(float _x, float _y, float _radious) {
		p = new PhysicsBodyCircle(_x, _y, _radious, *this);
		p->dynamic = true;
		p->solid = false;
	}
	virtual void display();
	virtual void eventOverlap(Actor &_actor);
	virtual Actor* clone();
};

class Wall : public Actor {
public:
	Wall() {}
};
class Floor : public Actor {
public:
	Floor() {}
	Floor(float _x, float _y, int _w, int _h) {
		p = new PhysicsBodyAABB(_x, _y, _w, _h, *this);
		p->solid = false;
	}
};
class DestructableWall : public Wall {
public:
	int health;
	DestructableWall() {
		health = 100;
	}
};

class WallTileCross : public Wall {
public:
	WallTileCross(){}
	WallTileCross(float _x, float _y) {
		p = new PhysicsBodyAABB(_x, _y, 50, 50, *this);
		p->solid = true;
		p->friction = 1;
	}
	virtual void display();
	virtual string spawnString() {
		Vector *v = p->position;
		return "level->addActor(*new WallTileCross(" + to_string(v->x) + ", " + to_string(v->y) + "));\n";
	}
	virtual Actor* clone();
};
class WallTileCross2 : public Wall {
public:
	WallTileCross2() {}
	WallTileCross2(float _x, float _y) {
		p = new PhysicsBodyAABB(_x, _y, 50, 50, *this);
		p->solid = true;
		p->friction = 1;
	}
	virtual void display();
	virtual string spawnString() {
		Vector *v = p->position;
		return "level->addActor(*new WallTileCross2(" + to_string(v->x) + ", " + to_string(v->y) + "));\n";
	}
	virtual Actor* clone();
};
class WallTileCross3 : public Wall {
public:
	WallTileCross3() {}
	WallTileCross3(float _x, float _y) {
		p = new PhysicsBodyAABB(_x, _y, 50, 50, *this);
		p->solid = true;
		p->friction = 1;
	}
	virtual void display();
	virtual string spawnString() {
		Vector *v = p->position;
		return "level->addActor(*new WallTileCross3(" + to_string(v->x) + ", " + to_string(v->y) + "));\n";
	}
	virtual Actor* clone();
};
class Tree : public Wall {
public:
	Tree() {}
	Tree(float _x, float _y) {
		p = new PhysicsBodyAABB(_x, _y, 50, 50, *this);
		p->solid = true;
		p->friction = 1;
	}
	virtual void display();
	virtual string spawnString() {
		Vector *v = p->position;
		return "level->addActor(*new Tree(" + to_string(v->x) + ", " + to_string(v->y) + "));\n";
	}
	virtual Actor* clone();
};

class FloorTileWood : public Floor {
public:
	FloorTileWood() {}
	FloorTileWood(float _x, float _y) :Floor(_x,_y,50,50) {

	}
	virtual void display();
	virtual string spawnString() {
		Vector *v = p->position;
		return "level->addActor(*new FloorTileWood(" + to_string(v->x) + ", " + to_string(v->y) + "));\n";
	}
	virtual Actor* clone();
};
class FloorTileWood2 : public Floor {
public:
	FloorTileWood2() {}
	FloorTileWood2(float _x, float _y) :Floor(_x, _y, 50, 50) {

	}
	virtual void display();
	virtual string spawnString() {
		Vector *v = p->position;
		return "level->addActor(*new FloorTileWood2(" + to_string(v->x) + ", " + to_string(v->y) + "));\n";
	}
	virtual Actor* clone();
};
class FloorTileWood3 : public Floor {
public:
	FloorTileWood3() {}
	FloorTileWood3(float _x, float _y) :Floor(_x, _y, 50, 50) {

	}
	virtual void display();
	virtual string spawnString() {
		Vector *v = p->position;
		return "level->addActor(*new FloorTileWood3(" + to_string(v->x) + ", " + to_string(v->y) + "));\n";
	}
	virtual Actor* clone();
};
class Grass : public Floor {
public:
	Grass() {}
	Grass(float _x, float _y) :Floor(_x, _y, 50, 50) {

	}
	virtual void display();
	virtual string spawnString() {
		Vector *v = p->position;
		return "level->addActor(*new Grass(" + to_string(v->x) + ", " + to_string(v->y) + "));\n";
	}
	virtual Actor* clone();
};

class IceFloor : public Floor {
public:
	IceFloor() {}
	IceFloor(float _x, float _y) :Floor(_x, _y, 50, 50) {

	}
	virtual void display();
	virtual string spawnString() {
		Vector *v = p->position;
		return "level->addActor(*new IceFloor(" + to_string(v->x) + ", " + to_string(v->y) + "));\n";
	}
	virtual Actor* clone();
};

class EnemyPawn1 : public Enemy {
public:
	EnemyPawn1(){}
	EnemyPawn1(float _x, float _y) :Enemy(_x, _y, 64, 64) {

	}
	virtual void display();
	virtual string spawnString() {
		Vector *v = p->position;
		return "level->addActor(*new EnemyPawn1(" + to_string(v->x) + ", " + to_string(v->y) + "));\n";
	}
	virtual void eventOverlap(Actor &_actor);
	virtual Actor* clone();
	virtual void run();
};
