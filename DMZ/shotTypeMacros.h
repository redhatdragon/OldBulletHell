#pragma once
#include "BluePyroGameEngine\Math\Math.h"

#ifndef SHOT_SHOTGUN
#define SHOT_SHOTGUN(_cx,_cy,_x,_y,_amount) \
for(float i = 0; i < _amount; i++){ \
	Actor *tb = new Bullet(_cx,_cy,4); \
	tb->p->velocity->set(_x,_y); \
	float offset = (1/float(_amount))/2; \
	rotatePoint(0,0,(i+1)*offset,tb->p->velocity); \
	level->addActor(*tb); \
}
//float offset = 1/((i+1)/_amount)/8;
#endif