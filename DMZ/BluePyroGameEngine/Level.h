#pragma once

//#include "Objects\Objects.h"
#include "Physics\PhysicsEngine.h"
#include "..\myActors.h"
class Objects;
class Object;
class Actor;

/*LEVEL*/
//--------------------------------------------------------------
class Level{
public:
	int actorCount;
	int deleteActorPoolCount;
	int drawCount;
	Actor* actor[MAX_ACTORS];
	//Actors *removePool;
	Actor* deleteActorPool[MAX_ACTORS];
	Actor* camera;
	Level(){
		//Init our physics engine and set our actor count to 0.
		physicsEngine = new PhysicsEngine();
		actorCount = deleteActorPoolCount = 0;
	}
	//Look at level.cpp for details.
	__forceinline void setCamera(Actor &a);  //attaches our camera to any actor we choose; E.G. Player.
	void addActor(Actor &a);  //adds custome actor to our level.
	void addActorToDeletePool(Actor &_actor);
	void removeActor(int _id);  //Is called when you delete an actor(DO NOT TOUCH OR CALL YOURSELF!!!!).
	void emptyDeleteActorPool();
	void run();
	void editorRun();
	//Display must be defined inside main.cpp for customizability.
	__forceinline void display();
};

//This camera is used as a position offset reference for where to draw objects.
__forceinline void Level::setCamera(Actor &a){
	camera = &a;
}
//--------------------------------------------------------------















/*
!!!!DISREGARD THIS COMMENT.  This hack is no longer used.  It's just here incase i need to use it later.!!!!
i got the idea of copying code from another file without it being used arbitrarily from this link.

http://stackoverflow.com/questions/3203365/problem-with-linking-against-a-static-library-which-has-inline-functions

@Staffan to be pedantic, any compilation unit including the header needs to see the definition of the function. They don't need to be in the same header file. A common trick from MFC days was to have the declaration of the methods in the class declaration then put inline definitions of the functions in a separate .inl file which was conditionally included either into the headers or into MFC source, depending on being in debug mode. I think this was a workaround for debuggers of the day failing to support inline debugging. – Andy Dent Jun 30 '13 at 6:56
add a comment

MY NOTE
It failed using the .inl extension however i changed it to .txt and it worked.  Then
i tried to change the file name and make the extension .h for the IDE to use syntext highlighting AND IT WORKS.
THE RULE is that you MUST include at the bottum of your declarations.  You cant define something before it exists.
*/