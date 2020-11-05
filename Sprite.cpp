
#include "Sprite.h"

//
// Basic Sprite Object
//
Sprite::Sprite() {
	speed = 0;
	velocity = ofVec3f(0, 0, 0);
	lifespan = -1;      // lifespan of -1 => immortal 
	birthtime = 0;
	bSelected = false;
	haveImage = false;
	name = "UnamedSprite";
	width = 60;
	height = 80;
	health = 1;
}

// Return a sprite's age in milliseconds
//
float Sprite::age() {
	return (ofGetElapsedTimeMillis() - birthtime);
}

//  Set an image for the sprite. If you don't set one, a rectangle
//  gets drawn.
//
void Sprite::setImage(ofImage img) {
	image = img;
	haveImage = true;
	width = image.getWidth();
	height = image.getHeight();
}

//	Designates this sprite as an animated one, and plugs the given sheet into the sprite
//
void Sprite::setSpriteSheet(vector<ofImage> sh, int nFrames) {
	bAnimated = true;
	frames = nFrames;
	spriteSheet = sh;
}

//  Causes the sprite to be removed next update()
//
void Sprite::kill() {
	lifespan = 0;
}


//  Render the sprite
//
void Sprite::draw() {

	ofSetColor(255, 255, 255, 255);

	// draw image centered and add in translation amount
	//
	if (haveImage) {
		if (!bAnimated) image.draw(-width / 2.0 + trans.x, -height / 2.0 + trans.y);	// non-animated sprite
		// draw the current frame of the animated sprite
		else {
			spriteSheet[frame].draw(-width / 2.0 + trans.x, -height / 2.0 + trans.y);	
			if (ofGetElapsedTimeMillis() - lastFrame >= frameSpeedDiv) {
				frame++; // increment the frame
				frame = frame % frames;	 
				lastFrame = ofGetElapsedTimeMillis();
			}
		}
	}
	else {
		// in case no image is supplied, draw something.
		// 
		ofSetColor(255, 0, 0);
		ofDrawRectangle(-width / 2.0 + trans.x, -height / 2.0 + trans.y, width, height);
	}
}

// A method to test if a given vector is inside the bounds of the sprite.
// Note that for now this only uses a basic bounding box to represent the sprite's  area.
bool Sprite::inside(ofVec3f vec) {
	return (vec.x >= trans.x - width / 2 &&
		vec.x <= trans.x + width / 2 &&
		vec.y >= trans.y - height / 2 &&
		vec.y <= trans.y + height / 2);
}

