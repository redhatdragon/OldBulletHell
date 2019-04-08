#pragma once

using namespace std;

class Pixel{
public:
	uint16_t x;
	uint16_t y;
	uint16_t color;
	uint32_t data;  //bitmask
	//0 = alpha
	
	Pixel(){
		
	}
	
	Pixel(uint16_t _x, uint16_t _y){
		x = _x; y = _y;
		color = 0;
	}
	Pixel(uint16_t _x, uint16_t _y, uint16_t _color){
		
	}
	bool getAlpha(){
		return false;
	}
};