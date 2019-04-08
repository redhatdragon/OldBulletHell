/*Math related code commonly used by the physics engine*/
#pragma once

#include <iostream>
#if GCC == TRUE
#include <stdlib.h>  //for the abs function
#include <math.h>  //for the sqrt function
#endif
#include "../GameMacros.h"
using namespace std;

/*CLASSES*/
//--------------------------------------------------------------
class Vector{
public:
	float x,y;
	Vector(){
		x = y = 0;
	}
	Vector(const Vector& v){
		x = v.x; y = v.y;
	}
	Vector(const Vector *v){
		x = v->x; y = v->y;
	}
	Vector(float _x, float _y){
		x = _x; y = _y;
	}
	Vector operator+(const Vector &other){
		return Vector(x+other.x,y+other.y);
	}
	Vector operator+(Vector *other){
		return Vector(x+other->x,y+other->y);
	}
	Vector operator+(const float delta){
		return Vector(x+delta,y+delta);
	}
	Vector operator-(const Vector &other) {
		return Vector(x - other.x, y - other.y);
	}
	Vector operator-(Vector *other) {
		return Vector(x - other->x, y - other->y);
	}
	Vector operator-(const float delta) {
		return Vector(x - delta, y - delta);
	}
	__forceinline void set(float _x, float _y){
		x = _x; y = _y;
	}
	__forceinline void add(float _x, float _y){
		x += _x; y += _y;
	}
	__forceinline void add(Vector &other){
		x += other.x; y += other.y;
	}
	__forceinline void scale(float delta){
		x *= delta; y *= delta;
	}
	__forceinline void round(int _num) {
		/*int tx = (int)x % _num;
		int ty = (int)y % _num;
		if (tx < _num / 2) {
			x -= tx;
		}else{
			x += _num - tx;
		}if (ty < _num / 2) {
			y -= ty;
		}else{
			y += _num - ty;
		}*/
		int tx = (int)x / _num;
		int ty = (int)y / _num;
		x = tx*_num;
		y = ty*_num;
	}
	__forceinline float length(){
		return sqrt((x * x) + (y * y));
	}
	__forceinline void normalize(){
		float l = length();
		x = x / l; y = y / l;
	}
	__forceinline void printData(){
		cout << x << "," << y << endl;
	}
};
//--------------------------------------------------------------
class Line{
public:
	float x1,y1,x2,y2;
	Line(){
		x1 = y1 = x2 = y2 = 0;
	}
	Line(const Line &v){
		x1 = v.x1; y1 = v.y1; x2 = v.x2; y2 = v.y2;
	}
	Line(const Line *v){
		x1 = v->x1; y1 = v->y1; x2 = v->x2; y2 = v->y2;
	}
	Line(const Vector &a, const Vector &b){
		x1 = a.x; y1 = a.y; x2 = b.x; y2 = b.y;
	}
	Line(float _x1, float _y1, float _x2, float _y2){
		x1 = _x1; y1 = _y1; x2 = _x2; y2 = _y2;
	}
	Line operator+(const Line &other){
		return Line(x1+other.x1,y1+other.y1,
			x2+other.x2,y2+other.y2);
	}
	Line operator+(Line *other){
		return Line(x1+other->x1,y1+other->y1,
			x2+other->x2,y2+other->y2);
	}
	Line operator+(const float delta){
		return Line(x1+delta,y1+delta,
			x2+delta,y2+delta);
	}
	__forceinline float length(){
		return sqrt((x2-x1 * x2-x1) + (y2-y1 * y2-y1));
	}
	__forceinline void printData(){
		cout << x1 << "," << y1 << " " << x2 << "," << y2 << endl;
	}
};







/*FUNCTIONS*/
//--------------------------------------------------------------
__forceinline int dist(float x1, float y1, float x2, float y2){
	float dx = x1 - x2;
	float dy = y1 - y2;
	return abs(int(sqrt(dx*dx+dy*dy)));
}
__forceinline bool rectInRect(int x1, int y1, int s1x, int s1y, int x2, int y2, int s2x, int s2y){
  s1x /= 2; s1y /= 2; s2x /= 2; s2y /= 2;
  if(x1-s1x >= x2+s2x || x1+s1x <= x2-s2x || y1-s1y >= y2+s2y || y1+s1y <= y2-s2y){
    return false;
  }return true;
}
__forceinline void rotatePoint(float cx, float cy, float angle, Vector *p){
	float s = sin(angle);
	float c = cos(angle);

	// translate point back to origin:
	p->x -= cx;
	p->y -= cy;

	// rotate point
	float xnew = p->x * c - p->y * s;
	float ynew = p->x * s + p->y * c;

	// translate point back:
	p->x = xnew + cx;
	p->y = ynew + cy;
}
__forceinline void increaseDistance(float cx, float cy, float magnitude, Vector *p){
	// translate point back to origin:
	p->x -= cx;
	p->y -= cy;

	//get the direction vector.
	Vector direction = Vector(p->x,p->y);
	direction.normalize();

	//multiply our direction by magnitude.
	direction.scale(magnitude);

	// translate point back:
	p->x = direction.x + cx;
	p->y = direction.y + cy;
}
//--------------------------------------------------------------