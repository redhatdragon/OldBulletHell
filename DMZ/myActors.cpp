#include "myActors.h"
#include "BluePyroGameEngine\Level.h"

#ifndef OFFSET_X
#define OFFSET_X level->camera->p->position->x+windowWidth/2
#endif

#ifndef OFFSET_Y
#define OFFSET_Y level->camera->p->position->y+windowHeight/2
#endif

void Player::fire() {
	if (leftMouseDown) {
		Vector *c = level->camera->p->position;
		int clickPosX = mouseX + (c->x - windowWidth / 2), clickPosY = mouseY+(c->y- windowHeight /2);
		int d = dist(getX(), getY(), clickPosX, clickPosY);
		Vector v = Vector(clickPosX - getX(), clickPosY - getY());
		v.normalize();
		v.scale(3);
		level->addActor(*new PlayerBullet(getX(), getY(), v.x, v.y));
	}
}
void Player::display() {
	Vector *v = p->position;  //our physics bodyy's location.
							  //this is to cast our physics body into a circle to get the radious.
							  //don't worry it about it too much.
	PhysicsBodyCircle *tp = static_cast<PhysicsBodyCircle*>(p);
	rect(v->x - tp->radious - OFFSET_X, v->y - tp->radious - OFFSET_Y, tp->radious * 2, tp->radious * 2, 25, 255, 150);
}
void Player::eventOverlap(Actor &_actor) {
	if (dynamic_cast<Bullet*> (&_actor)) {
		health--;
	}else if(dynamic_cast<Enemy*> (&_actor)){
		health--;
	}else if(dynamic_cast<IceFloor*> (&_actor)) {
		floorDrag = .9;
		//p->velocity->x /= 2;
		//p->velocity->y /= 2;
	}
}
Actor *Player::clone() {
	return new Player(getX(), getY());
}

void PlayerBullet::display() {
	Vector *v = p->position;
	PhysicsBodyCircle *tp = static_cast<PhysicsBodyCircle*>(p);
	rect(v->x - tp->radious - OFFSET_X, v->y - tp->radious - OFFSET_Y, tp->radious * 2, tp->radious * 2, 50, 20, 255);
}
void PlayerBullet::eventOverlap(Actor &_actor) {
	if (dynamic_cast<Wall*>(&_actor)) {
		del();
	}
}
Actor *PlayerBullet::clone() {
	return new PlayerBullet(getX(), getY(),p->velocity->x,p->velocity->y);
}

void Bullet::display() {
	Vector *v = p->position;
	PhysicsBodyCircle *tp = static_cast<PhysicsBodyCircle*>(p);
	rect(v->x - tp->radious - OFFSET_X, v->y - tp->radious - OFFSET_Y, tp->radious*2, tp->radious*2, 200, 200, 200);
}
void Bullet::eventOverlap(Actor &_actor) {
	if (dynamic_cast<Wall*> (&_actor)) {
		del();
	}
}
Actor *Bullet::clone() {
	return new Bullet(getX(), getY(), static_cast<PhysicsBodyCircle*>(p)->radious);
}

void WallTileCross::display() {
	Vector *v = p->position;
	PhysicsBodyAABB *tp = static_cast<PhysicsBodyAABB*>(p);
	drawTexture(TEXTURE_WALL_CROSS, v->x - tp->width / 2 - OFFSET_X, v->y - tp->height / 2 - OFFSET_Y, tp->width, tp->height);
}
Actor *WallTileCross::clone() {
	return new WallTileCross(getY(), getY());
}
void WallTileCross2::display() {
	Vector *v = p->position;
	PhysicsBodyAABB *tp = static_cast<PhysicsBodyAABB*>(p);
	drawTexture(TEXTURE_WALL_CROSS2, v->x - tp->width / 2 - OFFSET_X, v->y - tp->height / 2 - OFFSET_Y, tp->width, tp->height);
}
Actor *WallTileCross2::clone() {
	return new WallTileCross2(getY(), getY());
}
void WallTileCross3::display() {
	Vector *v = p->position;
	PhysicsBodyAABB *tp = static_cast<PhysicsBodyAABB*>(p);
	drawTexture(TEXTURE_WALL_CROSS3, v->x - tp->width / 2 - OFFSET_X, v->y - tp->height / 2 - OFFSET_Y, tp->width, tp->height);
}
Actor *WallTileCross3::clone() {
	return new WallTileCross3(getY(), getY());
}
void Tree::display() {
	Vector *v = p->position;
	PhysicsBodyAABB *tp = static_cast<PhysicsBodyAABB*>(p);
	drawTexture(TEXTURE_TREE, v->x - tp->width / 2 - OFFSET_X, v->y - tp->height / 2 - OFFSET_Y, tp->width, tp->height);
}
Actor *Tree::clone() {
	return new Tree(getY(), getY());
}

void FloorTileWood::display() {
	Vector *v = p->position;
	PhysicsBodyAABB *tp = static_cast<PhysicsBodyAABB*>(p);
	drawTexture(TEXTURE_FLOOR_WOOD, v->x - tp->width / 2 - OFFSET_X, v->y - tp->height / 2 - OFFSET_Y, tp->width, tp->height);
}
Actor *FloorTileWood::clone() {
	return new FloorTileWood(getY(), getY());
}
void FloorTileWood2::display() {
	Vector *v = p->position;
	PhysicsBodyAABB *tp = static_cast<PhysicsBodyAABB*>(p);
	drawTexture(TEXTURE_FLOOR_WOOD2, v->x - tp->width / 2 - OFFSET_X, v->y - tp->height / 2 - OFFSET_Y, tp->width, tp->height);
}
Actor *FloorTileWood2::clone() {
	return new FloorTileWood2(getY(), getY());
}
void FloorTileWood3::display() {
	Vector *v = p->position;
	PhysicsBodyAABB *tp = static_cast<PhysicsBodyAABB*>(p);
	drawTexture(TEXTURE_FLOOR_WOOD3, v->x - tp->width / 2 - OFFSET_X, v->y - tp->height / 2 - OFFSET_Y, tp->width, tp->height);
}
Actor *FloorTileWood3::clone() {
	return new FloorTileWood3(getY(), getY());
}
void Grass::display() {
	Vector *v = p->position;
	PhysicsBodyAABB *tp = static_cast<PhysicsBodyAABB*>(p);
	drawTexture(TEXTURE_GRASS, v->x - tp->width / 2 - OFFSET_X, v->y - tp->height / 2 - OFFSET_Y, tp->width, tp->height);
}
Actor *Grass::clone() {
	return new Grass(getY(), getY());
}
void IceFloor::display() {
	Vector *v = p->position;
	PhysicsBodyAABB *tp = static_cast<PhysicsBodyAABB*>(p);
	rect(v->x - tp->width / 2 - OFFSET_X, v->y - tp->height / 2 - OFFSET_Y, tp->width, tp->height, 200, 200, 255);
}
Actor *IceFloor::clone() {
	return new IceFloor(getY(), getY());
}

void EnemyPawn1::display() {
	Vector *v = p->position;
	PhysicsBodyAABB *tp = static_cast<PhysicsBodyAABB*>(p);
	static int frame = 0;
	static int delay = 10;
	const int frameLimit = 3-1;
	const int delayLimit = 30;
	drawTextureSplit(TEXTURE_ENEMY1,v->x - tp->width / 2 - OFFSET_X, v->y - tp->height / 2 - OFFSET_Y, tp->width, tp->height,frame, -getDirectionInDegrees()+90);
	if (delay < delayLimit) {
		delay++;
	}else{
		delay = 0;
		if (frame < frameLimit) {
			frame++;
		}
		else {
			frame = 0;
		}
	}
}
void EnemyPawn1::eventOverlap(Actor &_actor) {
	if (dynamic_cast<PlayerBullet*> (&_actor)) {
		del();
	}
}
Actor *EnemyPawn1::clone() {
	return new EnemyPawn1(getY(), getY());
}
void EnemyPawn1::run() {
	#ifndef speed
	#define speed 1.5
	#endif
	Actor *c = level->camera;
	Vector pos = Vector(getX()+20, getY()+10);
	rotatePoint(getX(), getY(), -getDirectionInRadians(), &pos);
	//increaseDistance(getX(),getY(),30,&pos);
	int d = dist(getX(), getY(), c->getX(), c->getY());
	if (d < 100) {
		static int timer = 0;
		if (timer < 10) {
			timer++;
		}else{
			Bullet *b = new Bullet(pos.x, pos.y, 8);
			Vector *velocity = b->p->velocity;
			velocity->set(c->getX() - pos.x, c->getY() - pos.y);
			velocity->normalize();
			velocity->scale(speed * 2);
			level->addActor(*b);
			//b->del();
			//SHOT_SHOTGUN(getX(), getY(), velocity->x, velocity->y, 8)
			timer = 0;
		}
	}
	if (d > 60 && d < 200) {
		Vector *velocity = p->velocity;
		velocity->set(c->getX() - getX(), c->getY() - getY());
		velocity->normalize();
		velocity->scale(speed);
	}
	#undef speed
	float velX = p->velocity->x;
	float velY = p->velocity->y;
	if (velX != 0 || velY != 0) {
		setDirectionAndNormalize(velX, velY);
		//cout << velX << " and " << velY << endl;
	}
}