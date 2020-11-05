#pragma once

#include "ofMain.h"

// duplicated from Lab 6

class Particle {
public:
	Particle();

	ofVec3f position;
	ofVec3f velocity;
	ofVec3f acceleration;
	ofVec3f forces;
	float	damping;
	float   mass;
	float   lifespan;
	float   size;			// particles are squares, so it has an edge length instead of a radius
	float   birthtime;		
	void    integrate();
	void    draw();
	float   age();        // in seconds
	ofColor color;
	bool	justCreated = true; // new particle will have the radial force applied to them
};

const int INIT_HEALTH = 10;
const int GRACE_PERIOD = 4000;		// Grace period after taking damage in milliseconds.

// A special particle to represent the player, since the player's plane is an image and not just a dot.
// From the player's perspective, their plane seems more like a sprite than a particle,
// but since it has physics based motion, it's more like a particle.
//
class Player : public Particle {
	ofImage image;
	vector<ofImage> sprites;	// a sprite sheet in vector form
	int frame = 0;
	int nFrames;				// number of frames in the sprite's animation
	int frameSpeedDiv = 80;		// how many milliseconds between changing frames in the sprites animation
	int lastFrame = 0;
	float width, height;
	int health = INIT_HEALTH;	// aka max health
	bool damaged;				// When the player gets hit, they'll get a grace period of a few seconds before the can get hit again.
	bool bAnimated = false;
	float hitTime;
public:
	void integrate();
	void setImage(ofImage);
	void setSpriteSheet(vector<ofImage>, int);
	float getWidth() { return width; }
	float getHeight() { return height; }
	void draw();

	int getHealth() { return health; }
	bool isDamaged() { return damaged; }
	void damage();
	void repair(int value) { health = (health + value > INIT_HEALTH) ? INIT_HEALTH : health + value; }	// add health back to the player, up to the maximum value
	// ^ this repair method makes me sad, because I originally wanted to include a way for the player to repair their ship,
	// but time constraints killed that idea. This method is still used when starting the game, so the method remains.
};