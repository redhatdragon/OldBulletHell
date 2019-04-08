#pragma once
#include <string>
#include "Graphics.h"
#include "myActors.h"
#include "BluePyroGameEngine\Level.h"

using namespace std;

class Widget{
public:
	float x, y, w, h;
	int r, g, b;
	Widget(){}
	virtual bool pointInWidget(int _x, int _y) {
		if (_x > x && _x < x + w && _y > y && _y < y + h) {
			return true;
		}return false;
	}
	virtual void display() = 0;
};

class WidgetBox: public Widget {
public:
	WidgetBox(){}
	WidgetBox(float _x, float _y, float _w, float _h, int _r, int _g, int _b) {
		x = _x; y = _y; w = _w; h = _h;
		r = _r; g = _g; b = _b;
	}
	virtual void display() {
		rect(x, y, w, h, r, g, b);
	}
};

class WidgetArrows : public Widget {
public:
	int *num;
	Widget *leftArrow, *rightArrow;
	WidgetArrows(){}
	WidgetArrows(float _x, float _y, int *_num) {
		x = _x; y = _y; num = _num;
		leftArrow = new WidgetBox(_x, _y, 20, 20, 255, 180, 180);
		rightArrow = new WidgetBox(_x+40, _y, 20, 20, 180, 255, 180);
	}
	virtual bool pointInWidget(int _x, int _y) {
		if (leftArrow->pointInWidget(_x, _y)) {
			*num = *num-1;
		}else if (rightArrow->pointInWidget(_x, _y)) {
			*num = *num+1;
		}
	}
	virtual void display() {
		leftArrow->display();
		rightArrow->display();
	}
};
class WidgetArrowsDecade : public WidgetArrows {
public:
	Widget *farLeftArrow, *farRightArrow;
	WidgetArrowsDecade(){}
	WidgetArrowsDecade(int _x, int _y, int *_num) {
		x = _x; y = _y; num = _num;
		farLeftArrow = new WidgetBox(_x, _y, 20, 20, 255, 0, 0);
		leftArrow = new WidgetBox(_x + 20, _y, 20, 20, 255, 180, 180);
		rightArrow = new WidgetBox(x+60, _y, 20, 20, 180,255,180);
		farRightArrow = new WidgetBox(x + 80, _y, 20, 20, 0, 255, 0);
	}
	virtual bool pointInWidget(int _x, int _y) {
		if (leftArrow->pointInWidget(_x, _y)) {
			*num = *num - 1;
		}else if (rightArrow->pointInWidget(_x, _y)) {
			*num = *num + 1;
		}else if(farLeftArrow->pointInWidget(_x, _y)){
			*num = *num - 10;
		}else if(farRightArrow->pointInWidget(_x, _y)){
			*num = *num + 10;
		}
	}
	virtual void display() {
		leftArrow->display();
		rightArrow->display();
		farLeftArrow->display();
		farRightArrow->display();
	}
};

class TextBox: public WidgetBox{
public:
	string txt;
	TextBox(){}
	TextBox(float _x, float _y, float _w, float _h, int _r, int _g, int _b, string _s){
		x = _x; y = _y; w = _w; h = _h;
		r = _r; g = _g; b = _b;
		txt = _s;
	}
	virtual void display(){
		rect(x,y,w,h,r,g,b);
	}
};

class ActorBox: public WidgetBox {
public:
	Actor *actor;
	ActorBox(){}
	ActorBox(float _x, float _y, float _w, float _h, int _r, int _g, int _b, Actor &_actor) {
		x = _x; y = _y; w = _w; h = _h;
		r = _r; g = _g; b = _b;
		actor = &_actor;
		actor->p->position->x = x + _w / 2; actor->p->position->y = y + h / 2;
	}
	virtual void display() {
		rect(x, y, w, h, r, g, b);
		actor->display();
	}
};

class ActorBoxCollection: public Widget {
public:
	Level *level;
	ActorBox *box[100][10];
	int currentBox, currentCatagory;
	int gridScale, spawnAmmountWidth, spawnAmmountHeight;
	int spawnScale;

	WidgetArrows *catagoryArrows;
	WidgetArrows *gridScaleArrows, *spawnAmmountWidthArrows, *spawnAmmountHeightArrows;
	WidgetArrows *spawnScaleArrows;

	ActorBoxCollection(){
		
	}
	ActorBoxCollection(int _x, int _y, int _w, int _h, int _r, int _g, int _b, Level *_level);
	void addBox(ActorBox &_actorBox) {
		for (int i = 0; i < 100; i++) {
			if (box[i][currentCatagory] == NULL) {
				box[i][currentCatagory] = &_actorBox;
				return;
			}
		}
	}
	void selectDifferentActor(int _num) {
		currentBox += _num;
	}
	void placeActor(int _x, int _y);
	void clicked() {
		if (catagoryArrows->pointInWidget(mouseX, mouseY)) {
			currentBox = 0;
		}else if(gridScaleArrows->pointInWidget(mouseX, mouseY)){
			return;
		}else if(spawnAmmountWidthArrows->pointInWidget(mouseX, mouseY)){
			return;
		}else if(spawnAmmountHeightArrows->pointInWidget(mouseX, mouseY)){
			return;
		}else if(spawnScaleArrows->pointInWidget(mouseX, mouseY)){
			return;
		}
	}
	virtual void display();
};