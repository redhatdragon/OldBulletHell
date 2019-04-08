#pragma once
#include "Object.h"

class Object;
class Actor;

class Objects{
public:
	int size, count;
	Object **object;
	Objects();
	Objects(int _size);
	void makeObjectArray(int _size);
	void doubleSize();
	void addObject(Object *_o);
	void removeObject(Object *_o);

	void subObject(int _index);

	void cleanArray();
	void deleteEverything();
};



class Actors {
public:
	int size, count;
	Actor **actor;
	Actors();
	Actors(int _size);
	void makeActorArray(int _size);
	void doubleSize();
	void addActor(Actor *_o);
	void addActorNonDup(Actor *_o);
	void addActorsNonDup(Actors *_o);
	void removeActor(Actor *_o);

	void subActor(int _index);

	void cleanArray();

	void deleteEverything();
};