#include <string>

//window
extern "C" int windowWidth, windowHeight;
//routine
extern "C" int setup(int,int,int,int);
extern "C" void clear();
extern "C" void render();
extern "C" void endGame();
//drawing
extern "C" void rect(int, int, int, int, int, int, int);
extern "C" void text(char*, int,int,int,int, int,int,int);
extern "C" void createAndDrawTexture(std::string, int _x, int _y, int _w, int _h);
extern "C" void drawTexture(int _textureNum, int _x, int _y, int _w, int _h);
extern "C" void drawTextureSplit(int _textureNum, int _x, int _y, int _w, int _h, int _frame, float _angle);
//input/events
extern "C" bool quite;
extern "C" bool upk, downk, leftk, rightk, wk, sk, ak, dk;
extern "C" bool leftMouseDown, rightMouseDown;
extern "C" int mouseX, mouseY;

#ifndef TEXTURE_FLOOR_WOOD
#define TEXTURE_FLOOR_WOOD 0
#endif
#ifndef TEXTURE_FLOOR_WOOD2
#define TEXTURE_FLOOR_WOOD2 1
#endif
#ifndef TEXTURE_FLOOR_WOOD3
#define TEXTURE_FLOOR_WOOD3 2
#endif
#ifndef TEXTURE_GRASS
#define TEXTURE_GRASS 3
#endif

#ifndef TEXTURE_WALL_CROSS
#define TEXTURE_WALL_CROSS 4
#endif
#ifndef TEXTURE_WALL_CROSS2
#define TEXTURE_WALL_CROSS2 5
#endif
#ifndef TEXTURE_WALL_CROSS3
#define TEXTURE_WALL_CROSS3 6
#endif
#ifndef TEXTURE_TREE
#define TEXTURE_TREE 7
#endif

#ifndef TEXTURE_ENEMY1
#define TEXTURE_ENEMY1 8
#endif
#ifndef TEXTURE_ENEMY_MOVE1
#define TEXTURE_ENEMY_MOVE1 9
#endif