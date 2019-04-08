//----[Inside the possible PhysicsEngine namespaces]----//

//STANDERED ENGINE
#if PHYSICS_ENGINE_TYPE == NO_HASH
__forceinline void constructor(){
	bodyCount = dynamicBodyCount = 0;
}
__forceinline void addBody(PhysicsBody &_body){
	#if BP_SAFE_MODE == 1
	if(bodyCount < MAX_ACTORS){
		body[bodyCount] = &_body; bodyCount++;
	}else{
		cout << "ERROR: Too many bodies for array." << endl;
		cout << "MEMORYLEAK: Unable to cleanup extra body." << endl;
	}
	#else
	body[bodyCount] = &_body; bodyCount++;
	#endif
}
__forceinline void removeBody(int _id){
	if(_id < bodyCount-1){
		 bodyCount--; body[_id] = body[bodyCount];
	}else{
		bodyCount--;
	}
}
__forceinline void translate(PhysicsBody &_body, int _x, int _y){

}



//PIXEL BACKGROUND ENGINE
#elif PHYSICS_ENGINE_TYPE == PIXEL_HASH
#define PIXEL_HASH_WIDTH 1920
#define PIXEL_HASH_HEIGHT 1080
#define PIXEL_HASH_SCREENCOUNT 9
#define PIXEL_HASH_SCREENCOUNT_ROOT 3
//Pixel *pixel;
Pixel pixel
[PIXEL_HASH_WIDTH*PIXEL_HASH_SCREENCOUNT_ROOT]
[PIXEL_HASH_HEIGHT*PIXEL_HASH_SCREENCOUNT_ROOT];

__forceinline void constructor(){
	bodyCount = dynamicBodyCount = 0;
	for(uint16_t i = 0; i < PIXEL_HASH_WIDTH*PIXEL_HASH_SCREENCOUNT_ROOT; i++){
		for(uint16_t j = 0; j < PIXEL_HASH_HEIGHT*PIXEL_HASH_SCREENCOUNT_ROOT; j++){
			pixel[i][j] = Pixel(i,j);
		}
		//cout << i << endl;
	}
}
__forceinline void addBody(PhysicsBody &_body){
	#if BP_SAFE_MODE == 1
	if(bodyCount < MAX_ACTORS){
		body[bodyCount] = &_body; bodyCount++;
	}else{
		cout << "ERROR: Too many bodies for array." << endl;
		cout << "MEMORYLEAK: Unable to cleanup extra body." << endl;
	}
	#else
	body[bodyCount] = &_body; bodyCount++;
	#endif
}
__forceinline void removeBody(int _id){
	if(_id < bodyCount-1){
		 bodyCount--; body[_id] = body[bodyCount];
	}else{
		bodyCount--;
	}
}
__forceinline void translate(PhysicsBody &_body, int _x, int _y){
	
}
__forceinline void simulate(){
	for(int i = bodyCount; i < bodyCount; i++){
		for(int j = i+1; j < bodyCount; j++){
			body[i]->move();
			if(!body[i]->bodyInBody(*body[j])){
				
			}else{
				
			}
		}
	}
}
__forceinline void collisionDetection(){

}
__forceinline void collisionResponse(){

}
__forceinline void run(){
	simulate();
	collisionDetection();
	collisionResponse();
}




#else
	#error "No PhysicsEngine selected"
#endif
//----[end]----//