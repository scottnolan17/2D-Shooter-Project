#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "BaseObject.h"

//  General Sprite class  (similar to a Particle)
//
class Sprite : public BaseObject {
public:
	Sprite();
	void draw();
	float age();
	void setImage(ofImage);
	void setSpriteSheet(vector<ofImage>, int);
	bool bAnimated = false;
	int frame = 0;
	int frames;					// the number of frames in the sprites animation
	int frameSpeedDiv = 80;		// how many milliseconds between switching sprite animation frames
	int lastFrame = 0;
	bool inside(ofVec3f);					// an 'inside' method similar to our first project, except without all the vector math
	void kill();
	float speed;    //   in pixels/sec
	ofVec3f velocity; // in pixels/sec
	float birthtime; // elapsed time in ms
	float lifespan;  //  time in ms
	float width, height;
	int health;
	int pointValue;
	string name;	
	ofImage image;
	vector<ofImage> spriteSheet;
	bool haveImage;
};

