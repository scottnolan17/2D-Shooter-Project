#pragma once
#include "SpriteSystem.h"

//  General purpose Emitter class for emitting sprites
//  This works similar to a Particle emitter
//
class SpriteEmitter : public BaseObject {
public:
	SpriteEmitter(SpriteSystem *);
	SpriteEmitter() = default;
	void draw();
	void start();
	void stop();
	void setLifespan(float);
	void setVelocity(ofVec3f);
	void setChildImage(ofImage);
	void setImage(ofImage);
	void setRate(float);
	void update();

	SpriteSystem *sys;
	float rate;
	ofVec3f velocity;
	//float speedupFactor;
	float lifespan;
	bool started;
	float lastSpawned;
	int spriteHealth;
	int spritePointValue;
	ofImage childImage;
	ofImage image;
	bool drawable;
	bool haveChildImage;
	bool haveImage;
	
	//Curve curve;							// stores which curve (if any) the child sprites will follow

	float width, height;
};

// A specialized emitter that only emits enemy sprites.
// Allows functionality for emitting at a sort-of random position and angle and giving the sprites a death sound.
//
class EnemyEmitter : public SpriteEmitter {
public: 
	float angleRange = 10.0;
	float motion = 0.0;		// allows the emitter to move invisibly along the edge of the screen to create the illusion of random enemy plane spawn points
	int frames;
	bool bAnimateSprites = false;
	vector<ofImage> spriteSheet;

	EnemyEmitter(SpriteSystem *);
	void update();
	void setSpriteSheet(vector<ofImage>, int);
};

// An altered emitter class that shoots the player's projectiles with a sound effect
//
class Turret : public SpriteEmitter {
public:
	Turret(SpriteSystem *);
	int side;							// A convoluted way of seeming to have two alternating emitters on the plane: one emitter that switches back and forth between the left and right sides of the plane between shots; will equal 1 or -1
	bool bShooting;						// a boolean to represent if the trigger is being held down (spacebar)
	bool hasSound = false;
	ofSoundPlayer soundEffect;				// the shooting sound effect for creating a projectile sprite
	
	void setSoundEffect(ofSoundPlayer);
	void update();						// Checks if spacebar is held before behaving like emitter's update method
};