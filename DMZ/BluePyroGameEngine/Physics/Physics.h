#pragma once

#include "../Math/Math.h"
#include "../GameMacros.h"
class PhysicsBody;
class Actor;
/*NOTES*/
/*
* Need to add a lineIntersect function that takes two Lines
and uses them effeciently.
* Clean up the unnecessary step in VectorOverLine in "CLEAN".
* Redo physics body to only store relative positions and use a getter
to return the global coords.  Basiclly get rid of "Vector" array.
* Consider storing Lines instead of Vectors in physics body.
-Line would take more space
-Vector may be more unwieldly
-perhaps use getters to return Lines form the Vectors???
* Consider collision responce and how that would effect hiarichy.
*/




/*FUNCTIONS*/
//--------------------------------------------------------------
__forceinline bool vectorInBox(int _x, int _y, int _s, int px, int py){
	_s = _s/2;
	if(px >= _x-_s && px <= _x+_s && py >= _y-_s && py <= _y+_s){
		return true;
	}return false;
}
__forceinline bool vectorInRect(int _x, int _y, int _s, int _s2, int px, int py){
	_s = _s/2; _s2 = _s2/2;
	if(px >= _x-_s && px <= _x+_s && py >= _y-_s2 && py <= _y+_s2){
		return true;
	}return false;
}
/*__forceinline bool rectInRect(int x1, int y1, int _w1, int _h1, int x2, int y2, int _w2, int _h2){
	int w1 = _w1/2; int w2 = _w2/2;
	if(x1+w1 >= x2-w2 && x1-w1 <= x2+w2){
		int h1 = _h1/2;  int h2 = _h2/2;
		if(y1+h1 >= y2-h2 && y1-h1 <= y2+h2){
			return true;
		}
	}return false;
}*/
//--------------------------------------------------------------
__forceinline bool vectorInCircle(int _x, int _y, int _s, int px, int py){
	if(dist(px,py,_x,_y)<=_s){
		return true;
	}return false;
}
//--------------------------------------------------------------
//THE BELOW FUNCTION IS ACCURATE  //MAY HAVE ISSUES WITH COINCIDIENT PAIRS.
__forceinline bool lineIntersect(Vector a, Vector b, Vector c, Vector d){
  float denominator = (b.x-a.x)*(d.y-c.y)-(b.y-a.y)*(d.x-c.x);
  float numerator1 = (a.y-c.y)*(d.x-c.x)-(a.x-c.x)*(d.y-c.y);
  float numerator2 = (a.y-c.y)*(b.x-a.x)-(a.x-c.x)*(b.y-a.y);
  //perhaps for detecting coincidient lines?
  if(denominator == 0){
    return numerator1 == 0 && numerator2 == 0;
  }
  float r = numerator1/denominator;
  float s = numerator2/denominator;
  return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
}
__forceinline bool vectorOverLine(Line _v, Vector objectPos, int px, int py){
	int tx = objectPos.x; int ty = objectPos.y;
	int tx1 = _v.x1+tx; int tx2 = _v.x2+tx;
	int ty1 = _v.y1+ty; int ty2 = _v.y2+ty;
	int tmp = (tx2-tx1)*(py-ty1)-(ty2-ty1)*(px-tx1);
	if(tmp >= 0){return true;}
	return false;
}
__forceinline bool vectorOverLine(Line _v, Vector d){
	int tx1 = _v.x1; int tx2 = _v.x2;//clean out
	int ty1 = _v.y1; int ty2 = _v.y2;//clean out
	int tmp = (tx2-tx1)*(d.y-ty1)-(ty2-ty1)*(d.x-tx1);
	if(tmp >= 0){return true;}
	return false;
}
//__forceinline bool VectorInBody(PhysicsBody pb, Vector d);
//--------------------------------------------------------------







/*CLASSES*/
//--------------------------------------------------------------
class PhysicsBody{
public:
	int bodyVertexCount;
	int id;  //helps physics engine remove body.
	int state;
	int type;
	float friction;
	Actor *actorHandle;
	Vector *body;
	Vector *position;
	Vector *velocity;
	bool dynamic;
	bool solid;
	PhysicsBody();
	PhysicsBody(int _vectorCount, Vector _position, Actor &_actor);
	PhysicsBody(Vector d0, Vector d1, Vector d2, Vector _position, Actor &_actor);
	PhysicsBody(Vector d0, Vector d1, Vector d2, Vector d3, Vector _position, Actor &_actor);
	virtual ~PhysicsBody();
	void del();
	__forceinline void setWorldPosition(int _x, int _y);
	__forceinline void addToVelocity(int _x, int _y);
	__forceinline bool vectorInBody(Vector d);
	virtual bool dotInBody(Vector &d) {
		return false;
	}
	virtual bool bodyInBody(PhysicsBody &otherBody);
	__forceinline void move(){
		position->x+=velocity->x; position->y+=velocity->y;
	}
	__forceinline void moveReverse(){
		position->x-=velocity->x; position->y-=velocity->y;
	}
	__forceinline void drawBody(){
		/*ofSetColor(255,100,100);
		int tx = position->x; int ty = position->y;
		for(int i = 0; i < vectorCount-1; i++){
			ofLine(Vector[i].x+tx,Vector[i].y+ty,Vector[i+1].x+tx,Vector[i+1].y+ty);
		}
		if(vectorCount-1 > 0){
			ofLine(Vector[vectorCount-1].x+tx,Vector[vectorCount-1].y+ty,Vector[0].x+tx,Vector[0].y+ty);
		}*/
	}
};

class PhysicsBodyCircle: public PhysicsBody{
public:
	int radious;
	PhysicsBodyCircle();
	virtual ~PhysicsBodyCircle();
	PhysicsBodyCircle(Vector &_position, int _radious, Actor &_actor);
	PhysicsBodyCircle(float _x, float _y, int _radious, Actor &_actor);
	bool dotInBody(Vector &d);
	bool bodyInBody(PhysicsBody &otherBody);
};

class PhysicsBodyAABB: public PhysicsBody{
public:
	int width,height;
	PhysicsBodyAABB();
	virtual ~PhysicsBodyAABB();
	PhysicsBodyAABB(Vector &_position, int _width, int _height, Actor &_actor);
	PhysicsBodyAABB(int _x, int _y, int _width, int _height, Actor &_actor);
	bool dotInBody(Vector &d);
	bool bodyInBody(PhysicsBody &otherBody);
};