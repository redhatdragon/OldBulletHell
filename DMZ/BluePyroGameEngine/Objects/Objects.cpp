#include "Objects.h"

Objects::Objects(){
	makeObjectArray(2);
}

Objects::Objects(int _size){
	if (_size > 2){
		makeObjectArray(_size);
	}
	else{
		makeObjectArray(2);
	}
}

void Objects::makeObjectArray(int _size){
	object = new Object*[_size];
	size = _size; count = 0;
}

void Objects::doubleSize(){
	Object** tmp;
	tmp = new Object*[size*2]();  //may cause problem?
	//for(int i = 0; i < count*2; i++){tmp[i] = nullptr;}
	for(int i = 0; i < count; i++){
		tmp[i] = object[i];
	}
	delete[] object; object = tmp;
	size = size*2;
}

void Objects::addObject(Object *_o){
	if(count < size){
		object[count] = _o; count++;
	}else if(count == size){
		if(size != 0){
			doubleSize(); object[count] = _o; count++;
		}else{
			makeObjectArray(2); object[0] = _o; count++;
		}
	}
}

void Objects::removeObject(Object *_o){
	for(int i = 0; i < count; i++){
		if(object[i] == _o){
			if(i == count-1){
				object[i] = nullptr; count--; return;
			}
			object[i] = object[count-1]; object[count-1] = nullptr; count--; return;
		}
	}
	cout << "Can't remove object as it's not here!!!!" << endl;
}

void Objects::subObject(int _index) {
	if (count > 1) {
		if (count == size) {
			delete object[count]; count--;
		}
		else {
			delete object[count]; object[count] = object[size]; count--;
		}
	}
	else {
		delete object[0]; count--;
	}
}

void Objects::cleanArray() {
	if (count > 2) {
		if (count < size / 2) {
			Object** tmp;
			tmp = new Object*[size / 2]();  //may cause problem?
											//for(int i = 0; i < count*2; i++){tmp[i] = nullptr;}
			for (int i = 0; i < count; i++) {
				tmp[i] = object[i];
			}
			delete[] object; object = tmp;
			size = size / 2;
		}
	}
}

void Objects::deleteEverything() {
	for (int i = 0; i < count; i++) {
		delete object[i];
	}
	delete[] object;
	makeObjectArray(2);
}



Actors::Actors() {
	makeActorArray(2);
}

Actors::Actors(int _size) {
	if (_size > 2) {
		makeActorArray(_size);
	}
	else {
		makeActorArray(2);
	}
}

void Actors::makeActorArray(int _size) {
	actor = new Actor*[_size];
	size = _size; count = 0;
}

void Actors::doubleSize() {
	Actor** tmp;
	tmp = new Actor*[size * 2]();  //may cause problem?
	for (int i = 0; i < count; i++) {
		tmp[i] = actor[i];
	}
	delete[] actor; actor = tmp;
	size = size * 2;
}

void Actors::addActor(Actor *_o) {
	if (count < size) {
		actor[count] = _o; count++;
	}
	else if (count == size) {
		if (size != 0) {
			doubleSize(); actor[count] = _o; count++;
		}else{
			makeActorArray(2); actor[0] = _o; count++;
		}
	}
}

void Actors::addActorNonDup(Actor *_o) {
	for (int i = 0; i < count; i++) {
		if (actor[i] == _o) {
			return;
		}
	}
	addActor(_o);
}

void Actors::addActorsNonDup(Actors *_o) {
	for (int i = 0; i < _o->count; i++) {
		addActorNonDup(_o->actor[i]);
	}
}

void Actors::removeActor(Actor *_o) {
	for (int i = 0; i < count; i++) {
		if (actor[i] == _o) {
			if (i == count - 1) {
				actor[i] = nullptr; count--; cleanArray(); return;
			}
			actor[i] = actor[count - 1]; actor[count - 1] = nullptr; count--; cleanArray(); return;
		}
	}
	cout << "Can't remove actor as it's not here!!!!" << endl;
}

void Actors::subActor(int _index) {
	if (count > 1) {
		if (count == size) {
			delete actor[count]; count--;
		}else{
			delete actor[count]; actor[count] = actor[size]; count--;
		}
	}else{
		delete actor[0]; count--;
	}
}

void Actors::cleanArray() {
	if (count > 2) {
		if (count < size / 2) {
			Actor** tmp;
			tmp = new Actor*[size / 2]();  //may cause problem?
										   //for(int i = 0; i < count*2; i++){tmp[i] = nullptr;}
			for (int i = 0; i < count; i++) {
				tmp[i] = actor[i];
			}
			delete[] actor; actor = tmp;
			size = size / 2;
		}
	}
}

void Actors::deleteEverything() {
	for (int i = 0; i < count; i++) {
		delete actor[i];
	}
	delete[] actor;
	makeActorArray(2);
}