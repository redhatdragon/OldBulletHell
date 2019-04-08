#include "Physics.h"
#include "PhysicsEngine.h"

/*PhysicsBody::PhysicsBody(){

}*/

PhysicsBody::PhysicsBody() {
	actorHandle = nullptr;
	position = velocity = nullptr;
	bodyVertexCount = 0;
	dynamic = false;
	solid = true;
	//physicsEngine->addBody(*this);
}

PhysicsBody::PhysicsBody(int _bodyVertexCount, Vector _position, Actor &_actor){
	//MUST FILL MEMBER Vector
	type = BP_BODYTYPE_CONVEX;
	bodyVertexCount = _bodyVertexCount;
	position = new Vector(_position);
	body = new Vector[bodyVertexCount];
	velocity = new Vector();
	actorHandle = &_actor;
	physicsEngine->addBody(*this);
}
PhysicsBody::PhysicsBody(Vector d0, Vector d1, Vector d2, Vector _position, Actor &_actor){
	type = BP_BODYTYPE_CONVEX;
	bodyVertexCount = 3;
	body = new Vector(_position);
	body = new Vector[bodyVertexCount];
	body[0] = new Vector(d0); body[1] = new Vector(d1); body[2] = new Vector(d2);
	setWorldPosition(_position.x,_position.y);
	body = new Vector();
	actorHandle = &_actor;
	physicsEngine->addBody(*this);
}
PhysicsBody::PhysicsBody(Vector d0, Vector d1, Vector d2, Vector d3, Vector _position, Actor &_actor){
	type = BP_BODYTYPE_CONVEX;
	bodyVertexCount = 4;
	position = new Vector(_position);
	body = new Vector[bodyVertexCount];
	body[0] = new Vector(d0); body[1] = new Vector(d1);
	body[2] = new Vector(d2); body[3] = new Vector(d3);
	setWorldPosition(_position.x,_position.y);
	velocity = new Vector();
	actorHandle = &_actor;
	physicsEngine->addBody(*this);
}
PhysicsBody::~PhysicsBody(){
	delete position;
	delete velocity;
	if(type == BP_BODYTYPE_AABB && bodyVertexCount != 0){
		for(int i = 0; i < bodyVertexCount; i++){
			delete &body[i];  //may cause error
		}delete[] &body;
	}
	//physicsEngine->removeBody(id);
}

void PhysicsBody::del() {
	physicsEngine->removeBody(id);
	delete this;
}

__forceinline void PhysicsBody::setWorldPosition(int _x, int _y){
	position->set(_x,_y);
}
__forceinline void PhysicsBody::addToVelocity(int _x, int _y){
	velocity->x += _x;
	velocity->y += _y;
	if(state == BP_STATIC_DYNAMIC){
		if(velocity->x != 0 || velocity->y != 0){
			state = BP_ACTIVE_DYNAMIC;

		}
	}else if(state == BP_ACTIVE_DYNAMIC){
		if(velocity->x == 0 && velocity->y == 0){
			state = BP_STATIC_DYNAMIC;
		}
	}
}

__forceinline bool PhysicsBody::vectorInBody(Vector d){
	for(int i = 0; i < bodyVertexCount; i++){
		if(i != bodyVertexCount-1){
			if(!vectorOverLine(Line(body[i]+position,body[i+1]+position),d)){
				return false;
			}
		}else{
			if(!vectorOverLine(Line(body[i]+position,body[0]+position),d)){
				return false;
			}
		}
	}return true;
}
bool PhysicsBody::bodyInBody(PhysicsBody &otherBody){
	Vector p = position;
	Vector p2 = otherBody.position;
	for(int a = 0; a < bodyVertexCount; a++){
		for(int b = 0; b < otherBody.bodyVertexCount; b++){
		if(a != bodyVertexCount-1){
			if(b != otherBody.bodyVertexCount-1){
				if(lineIntersect(body[a]+p,body[a+1]+p,otherBody.body[b]+p2,
					otherBody.body[b+1]+p2)){
					return true;
				}
			}
			if(lineIntersect(body[a]+p,body[a+1]+p,
				otherBody.body[b]+p2,otherBody.body[0]+p2)){
			return true;
			}
		}else{
			if(b != otherBody.bodyVertexCount-1){
				if(lineIntersect(body[a]+p,body[0]+p,
					otherBody.body[b]+p2,otherBody.body[b+1]+p2)){
					return true;
				}
			}
				if(lineIntersect(body[a]+p,body[0]+p,
					otherBody.body[b]+p2,otherBody.body[0]+p2)){
				return true;
				}
			}
		}
	}
	for(int i = 0; i < bodyVertexCount; i++){
		if(otherBody.vectorInBody(body[i])){
			cout << "hit" << endl;
			return true;
		}
	}//checks if one body is completly inside the other
	for(int i = 0; i < otherBody.bodyVertexCount; i++){
		if(vectorInBody(otherBody.body[i])){
			return true;
		}
	}//checks if one body is completly inside the other
	cout << dist(p.x,p.y,p2.x,p2.y) << endl;
	return false;
}



#define BP_SPHERE_BODY_SETUP \
type = BP_BODYTYPE_SPHERE; \
bodyVertexCount = 0; \
velocity = new Vector(); \
radious = _diameter/2; \
actorHandle = &_actorHandle; \
physicsEngine->addBody(*this);

PhysicsBodyCircle::PhysicsBodyCircle(Vector &_position, int _diameter, Actor &_actorHandle){
	position = &_position;
	BP_SPHERE_BODY_SETUP
}
PhysicsBodyCircle::PhysicsBodyCircle(float _x, float _y, int _diameter, Actor &_actorHandle){
	position = new Vector(_x, _y);
	BP_SPHERE_BODY_SETUP
}

PhysicsBodyCircle::~PhysicsBodyCircle(){

}

bool PhysicsBodyCircle::dotInBody(Vector &d) {
	if (dist(d.x, d.y, position->x, position->y) < radious) {
		return true;
	}
	return false;
}
bool PhysicsBodyCircle::bodyInBody(PhysicsBody &otherBody){
	Vector p1 = position;
	Vector p2 = otherBody.position;
	if(PhysicsBodyCircle *ob = dynamic_cast<PhysicsBodyCircle*>(&otherBody)){
		if(dist(p1.x, p1.y,p2.x,p2.y) < radious+static_cast<PhysicsBodyCircle&>(otherBody).radious){
			return true;
		}
	}else if (PhysicsBodyAABB *ob = dynamic_cast<PhysicsBodyAABB*>(&otherBody)) {
		Vector v = p2-p1;
		v.normalize();
		v.scale(radious);
		v = v + p1;
		if (lineIntersect(p1, v, Vector(p2.x - ob->width / 2, p2.y - ob->height / 2), Vector(p2.x + ob->width / 2, p2.y - ob->height / 2))) {
			return true;
		}else if (lineIntersect(p1, v, Vector(p2.x + ob->width / 2, p2.y - ob->height / 2), Vector(p2.x + ob->width / 2, p2.y + ob->height / 2))) {
			return true;
		}else if (lineIntersect(p1, v, Vector(p2.x + ob->width / 2, p2.y + ob->height / 2), Vector(p2.x - ob->width / 2, p2.y + ob->height / 2))) {
			return true;
		}else if (lineIntersect(p1, v, Vector(p2.x - ob->width / 2, p2.y + ob->height / 2), Vector(p2.x - ob->width / 2, p2.y - ob->height / 2))) {
			return true;
		}else if(ob->dotInBody(p1)){
			return true;
		}
	}
	return false;
}



#define BP_AABB_BODY_SETUP \
type = BP_BODYTYPE_AABB; \
bodyVertexCount = 0; \
velocity = new Vector(); \
width = _width; \
height = _height; \
actorHandle = &_actorHandle; \
physicsEngine->addBody(*this);

PhysicsBodyAABB::PhysicsBodyAABB(Vector &_position, int _width, int _height, Actor &_actorHandle){
	position = &_position;
	BP_AABB_BODY_SETUP
}
PhysicsBodyAABB::PhysicsBodyAABB(int _x, int _y, int _width, int _height, Actor &_actorHandle){
	position = new Vector(_x, _y);
	BP_AABB_BODY_SETUP
}

PhysicsBodyAABB::~PhysicsBodyAABB(){

}

bool PhysicsBodyAABB::dotInBody(Vector &d) {
	if (d.x < position->x + width / 2 && d.x > position->x - width / 2) {
		if (d.y < position->y + height / 2 && d.y > position->y - height / 2) {
			return true;
		}
	}
	return false;
}
bool PhysicsBodyAABB::bodyInBody(PhysicsBody &otherBody){
	Vector p1 = position;
	Vector p2 = otherBody.position;
	PhysicsBodyAABB *ob = dynamic_cast<PhysicsBodyAABB*>(&otherBody);
	if (ob) {
		if (rectInRect(p1.x, p1.y, width, height, p2.x, p2.y, ob->width, ob->height)) {
			return true;
		}
	}
	else if (PhysicsBodyCircle *ob = dynamic_cast<PhysicsBodyCircle*>(&otherBody)) {
		Vector v = p1-p2;
		v.normalize();
		v.scale(ob->radious);
		v = v + p2;
		if (lineIntersect(p2, v, Vector(p1.x - width / 2, p1.y - height / 2), Vector(p1.x + width / 2, p1.y - height / 2))) {
			return true;
		}else if (lineIntersect(p2, v, Vector(p1.x + width / 2, p1.y - height / 2), Vector(p1.x + width / 2, p1.y + height / 2))) {
			return true;
		}else if (lineIntersect(p2, v, Vector(p1.x + width / 2, p1.y + height / 2), Vector(p1.x - width / 2, p1.y + height / 2))) {
			return true;
		}else if (lineIntersect(p2, v, Vector(p1.x - width / 2, p1.y + height / 2), Vector(p1.x - width / 2, p1.y - height / 2))) {
			return true;
		}else if(dotInBody(p2)){
			return true;
		}
	}
	return false;
}