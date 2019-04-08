/*********************************************************************************
This file may be a .c file however it's being treated like a c++ file.
This is because we are compiling/linking iwth g++.
So any functions we create here must be declared as "extern "C" int foo()" first.
This prevents any strange name mangleing.
*********************************************************************************/

//#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
//#include "include/SDL2/SDL_Net.h"
#include "Graphics.h"
/*#define SDL_reinterpret_cast(type, expression)\
reinterpret_cast<type>(expression)*/
//using namespace std;

SDL_Window *win;
SDL_Renderer *ren;
SDL_Event evt;
SDL_Surface *bmp;
SDL_Texture *tex;

//events and input.
bool quite;
bool upk, downk, leftk, rightk, wk, sk, ak, dk;
bool leftMouseDown, rightMouseDown;
int mouseX, mouseY;
int windowWidth, windowHeight;

//texture variables.
int textureCount = 0;
#ifndef TEXTURE_LIMIT
#define TEXTURE_LIMIT 100
#endif
SDL_Texture* texture[TEXTURE_LIMIT];

void setupTextures();
void destroyTextures();
void addTexture(std::string _s);

int setup(int _x, int _y, int _w, int _h){
	quite = false;
	textureCount = 0;
	//SDLNet_Init();
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		//std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		printf("SDL_Init Error: ", SDL_GetError());
		return 1;
	}
	windowWidth = _w; windowHeight = _h;
	win = SDL_CreateWindow("Hello World!", _x, _y, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (win == NULL){
		//std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		printf("SDL_CreateWindow Error: ", SDL_GetError());
		SDL_Quit();
		//return 1;
	}
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL){
		SDL_DestroyWindow(win);
		//std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		printf("SDL_CreateRenderer Error: ", SDL_GetError());
		SDL_Quit();
		//return 1;
	}
	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
	}
	setupTextures();
	return 0;
}

void clear(){
	SDL_RenderClear(ren);
	//SDL_RenderCopy(ren, tex, NULL, NULL);
	SDL_Rect fillRect = { 0, 0, windowWidth, windowHeight };
	SDL_SetRenderDrawColor( ren, 0x00, 0x00, 0x00, 0xFF );        
	SDL_RenderFillRect( ren, &fillRect );
}

inline void pollEvents() {
	if (evt.type == SDL_QUIT) {
		quite = true;
	}else if (evt.type == SDL_MOUSEMOTION) {
		mouseX = evt.motion.x;
		mouseY = evt.motion.y;
	}else if (evt.type == SDL_MOUSEBUTTONDOWN) {
		if (evt.button.button == SDL_BUTTON_LEFT) {
			mouseX = evt.button.x;
			mouseY = evt.button.y;
			leftMouseDown = true;
		}else if (evt.button.button == SDL_BUTTON_RIGHT) {
			mouseX = evt.button.x;
			mouseY = evt.button.y;
			rightMouseDown = true;
		}
	}else if (evt.type == SDL_MOUSEBUTTONUP) {
		if(evt.button.button == SDL_BUTTON_LEFT){
			mouseX = evt.button.x;
			mouseY = evt.button.y;
			leftMouseDown = false;
		}
		if (evt.button.button == SDL_BUTTON_RIGHT) {
			mouseX = evt.button.x;
			mouseY = evt.button.y;
			rightMouseDown = false;
		}
	}else if (evt.type == SDL_KEYDOWN) {
		switch (evt.key.keysym.sym)
		{
		case SDLK_UP:
			upk = true;
			break;

		case SDLK_DOWN:
			downk = true;
			break;

		case SDLK_LEFT:
			leftk = true;
			break;

		case SDLK_RIGHT:
			rightk = true;
			break;
		
		case SDLK_w:
			wk = true;
			break;
		
		case SDLK_s:
			sk = true;
			break;
		
		case SDLK_a:
			ak = true;
			break;
		
		case SDLK_d:
			dk = true;
			break;
		}
	}else if (evt.type == SDL_KEYUP) {
		switch (evt.key.keysym.sym)
		{
		case SDLK_UP:
			upk = false;
			break;

		case SDLK_DOWN:
			downk = false;
			break;

		case SDLK_LEFT:
			leftk = false;
			break;

		case SDLK_RIGHT:
			rightk = false;
			break;
		
		case SDLK_w:
			wk = false;
			break;
		
		case SDLK_s:
			sk = false;
			break;
		
		case SDLK_a:
			ak = false;
			break;
		
		case SDLK_d:
			dk = false;
			break;
		}
	}
}

void render(){
	static int start = SDL_GetTicks();
	int time = SDL_GetTicks() - start;
	//if (time < 0) continue; // if time is negative, the time probably overflew, so continue asap

	int sleepTime = float(1 / float(60)) * 1000 - time;
	if (sleepTime > 0) {
		SDL_Delay(sleepTime);
	}
	SDL_RenderPresent(ren);
	SDL_PollEvent(&evt);
	pollEvents();
	start = SDL_GetTicks();
}

void endGame(){
	SDL_DestroyTexture(tex);
	destroyTextures();
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	TTF_Quit();
	SDL_Quit();
	//SDLNet_Quit();
}

void rect(int _x, int _y, int _w, int _h, int _r, int _g, int _b){
	SDL_Rect fillRect = { _x, _y, _w, _h };
	SDL_SetRenderDrawColor( ren, _r, _g, _b, 0xFF );        
	SDL_RenderFillRect( ren, &fillRect );
}

void text(char *_c, int _x, int _y, int _w, int _h, int _r, int _g, int _b) {

	TTF_Font* font = TTF_OpenFont("ARIAL.TTF", 16);
	SDL_Color foregroundColor = { _r, _g, _b };
	SDL_Color backgroundColor = { 0, 0, 0 };
	SDL_Surface *textSurface = TTF_RenderText_Shaded(font, _c, foregroundColor, backgroundColor);
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
	SDL_Rect textLocation = { _x, _y, _w, _h };
	SDL_RenderCopy(ren,textTexture, NULL, &textLocation);

	/*SDL_Rect textLocation = { _x, _y, 0, 0 };
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
	SDL_Flip(screen);
	SDL_FreeSurface(textSurface);*/

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
	TTF_CloseFont(font);
}

void createAndDrawTexture(std::string _s, int _x, int _y, int _w, int _h) {
	/*SDL_Surface *s = SDL_LoadBMP(_s.c_str());
	SDL_Texture *t = SDL_CreateTextureFromSurface(ren, s);
	SDL_FreeSurface(s);*/

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(_s.c_str());
	if (loadedSurface == NULL){
		printf("Unable to load image %s! SDL_image Error: %s\n", _s.c_str(), IMG_GetError());
	}else{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(ren, loadedSurface);
		if (newTexture == NULL){
			printf("Unable to create texture from %s! SDL Error: %s\n", _s.c_str(), SDL_GetError());
		}

		SDL_Rect r;
		r.x = _x; r.y = _y; r.w = _w; r.h = _h;
		SDL_RenderCopy(ren, newTexture, NULL, &r);

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
		SDL_DestroyTexture(newTexture);
	}
}

inline void setupTextures() {
	//std::string _s = "../ART/Floor Tile Wood.jpg";
	addTexture("../ART/Floors/FloorWood.jpg");
	addTexture("../ART/Floors/FloorWood2.jpg");
	addTexture("../ART/Floors/FloorWood3.jpg");
	addTexture("../ART/Floors/grass.png");
	addTexture("../ART/Walls/WallCross.jpg");
	addTexture("../ART/Walls/WallCross2.jpg");
	addTexture("../ART/Walls/WallCross3.jpg");
	addTexture("../ART/Walls/tree.png");
	addTexture("../ART/Enemies/Enemy1.png");
	addTexture("../ART/Enemies/Enemy1_Move.png");
}
inline void destroyTextures() {
	for (int i = 0; i < textureCount; i++) {
		SDL_DestroyTexture(texture[i]);
	}
}
void addTexture(std::string _s) {
	if (textureCount < TEXTURE_LIMIT - 1) {
		SDL_Texture* newTexture = NULL;

		SDL_Surface* loadedSurface = IMG_Load(_s.c_str());
		if (loadedSurface == NULL){
			printf("Unable to load image %s! SDL_image Error: %s\n", _s.c_str(), IMG_GetError());
		}else{
			newTexture = SDL_CreateTextureFromSurface(ren, loadedSurface);
			if (newTexture == NULL) {
				printf("Unable to create texture from %s! SDL Error: %s\n", _s.c_str(), SDL_GetError());
			}
			texture[textureCount] = newTexture; textureCount++;
			SDL_FreeSurface(loadedSurface);
		}
	}else{
		printf("ERROR: Loading too many textures!  Consider increasing TEXTURE_LIMIT.%s\n");
	}
}
void drawTexture(int _textureNum, int _x, int _y, int _w, int _h) {
	SDL_Rect r;
	r.x = _x; r.y = _y; r.w = _w; r.h = _h;
	SDL_RenderCopy(ren, texture[_textureNum], NULL, &r);
}
void drawTextureSplit(int _textureNum, int _x, int _y, int _w, int _h, int _frame, float _angle) {
	//get number of textures in this one texture.
	int totalWidth, totalHeight;
	int tFrame = 0;
	SDL_Rect r;
	SDL_Rect sR;
	r.x = _x; r.y = _y; r.w = _w; r.h = _h;
	SDL_QueryTexture(texture[_textureNum], NULL, NULL, &totalWidth, &totalHeight);
	totalWidth = totalWidth / 64;
	totalHeight = totalHeight / 64;

	for (int i = 0; i < totalHeight; i++) {
		for (int j = 0; j < totalWidth; j++) {
			if (_frame == tFrame) {
				sR.x = (j) * 64; sR.y = (i) * 64;
				//sR.x = sR.y = 0;
				sR.w = 64; sR.h = 64;
				SDL_RendererFlip flip = SDL_FLIP_NONE;
				//SDL_Point p; p.x = sR.x; p.y = sR.y;
				SDL_RenderCopyEx(ren, texture[_textureNum], &sR, &r, double(_angle), NULL, flip);
				i = totalWidth;
				j = totalHeight;
			}
			tFrame++;
		}
	}
}