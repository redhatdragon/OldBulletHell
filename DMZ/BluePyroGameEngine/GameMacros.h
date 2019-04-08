#pragma once

#define GCC TRUE  //change to false if using visual studio.

#if GCC == TRUE
#define __forceinline __attribute__((always_inline)) inline
#define nullptr NULL
#endif

#define MAX_ACTORS 10000000  //max actors that the level may use.  10 mill.
#define BP_SAFE_MODE 1
//Make 1 if you arn't sure your levels will comply with the limitations of the engine.
//else make it 0.
#define MULTITHREADED  //comment this out if you want multi threading turned off.

//these are the different states a physics body can take.
#define BP_STATIC 0  //can be collided against but can't move.
#define BP_STATIC_DYNAMIC 1  //is stationary but can be collided against and react.
#define BP_ACTIVE_DYNAMIC 2  //is moving and can be collided against and react.

//these tells what type of physics body we are dealing with.
#define BP_BODYTYPE_AABB 0
#define BP_BODYTYPE_SPHERE 1
#define BP_BODYTYPE_CONVEX 2
#define BP_BODYTYPE_PIXEL 3