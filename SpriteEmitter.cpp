
#include "SpriteEmitter.h"
#include "ofGraphics.h"

//  Create a new Emitter - needs a SpriteSystem
//
SpriteEmitter::SpriteEmitter(SpriteSystem *spriteSys) {
	sys = spriteSys;
	lifespan = 1000;    // milliseconds
	started = false;
	lastSpawned = 0;
	rate = 1;    // sprites/sec
	haveChildImage = false;
	haveImage = true;
	velocity = ofVec3f(0, 0, 0);
	drawable = true;
	width = 50;
	height = 50;
	spriteHealth = 1;
}

//  Draw the Emitter if it is drawable. In many cases you would want a hidden emitter
//
//
void SpriteEmitter::draw() {
	if (drawable) {

		if (haveImage) {
			image.draw(-image.getWidth() / 2.0 + trans.x, -image.getHeight() / 2.0 + trans.y);
		}
		else {
			ofSetColor(0, 0, 200);
			ofDrawRectangle(-width / 2 + trans.x, -height / 2 + trans.y, width, height);
		}
	}
}

//  Update the Emitter. If it has been started, spawn new sprites with
//  initial velocity, lifespan, birthtime.
//
void SpriteEmitter::update() {
	if (!started) { 
		return;
	}

	float time = ofGetElapsedTimeMillis();
	if ((time - lastSpawned) > (1000.0 / rate)) {
		// spawn a new sprite
		Sprite sprite;
		if (haveChildImage) sprite.setImage(childImage);
		sprite.velocity = velocity;
		sprite.speed = velocity.length() / ofGetFrameRate();
		sprite.lifespan = lifespan;
		sprite.setPosition(ofVec3f(trans.x, trans.y, 0));
		sprite.rot = rot;
		sprite.birthtime = time;
		sprite.height = height;
		sprite.width = width;
		sprite.health = spriteHealth;
		sprite.pointValue = spritePointValue;
		sys->add(sprite);
		lastSpawned = time;
	}
}

// Start/Stop the emitter.
//
void SpriteEmitter::start() {
	started = true;
	lastSpawned = ofGetElapsedTimeMillis();
}

void SpriteEmitter::stop() {
	started = false;
}

void SpriteEmitter::setLifespan(float life) {
	lifespan = life;
}

void SpriteEmitter::setVelocity(ofVec3f v) {
	velocity = v;
}

void SpriteEmitter::setChildImage(ofImage img) {
	childImage = img;
	haveChildImage = true;
}

void SpriteEmitter::setImage(ofImage img) {
	image = img;
}

void SpriteEmitter::setRate(float r) {
	rate = r;
}

EnemyEmitter::EnemyEmitter(SpriteSystem *spriteSys) {
	sys = spriteSys;
	lifespan = 4000;    // milliseconds
	started = false;
	lastSpawned = 0;
	rate = 1;    // sprites/sec
	haveChildImage = false;
	haveImage = true;
	velocity = ofVec3f(0, 0, 0);
	drawable = true;
	width = 50;
	height = 50;
	spriteHealth = 1;
}

void EnemyEmitter::update() {
	if (!started) {
		return;
	}

	// The emitters travel back and forth along the top of the screen for a random-ish spawn pattern.
	trans.x += motion;
	if (trans.x <= 0 || trans.x >= ofGetWindowWidth()) motion *= -1;	// if the emitter is about to move beyond the screen on either side, reverse movement direction

	float time = ofGetElapsedTimeMillis();
	if ((time - lastSpawned) > (1000.0 / rate)) {
		// spawn a new sprite
		Sprite sprite;
		if (haveChildImage) sprite.setImage(childImage);
		if (bAnimateSprites) sprite.setSpriteSheet(spriteSheet, frames);
		sprite.rot = ofRandom(																								// Wow, I had to bust out sohcahtoa for this one. It's been a while...
			max(glm::radians(-(angleRange / 2)), glm::atan((ofGetWindowWidth() - trans.x) / ofGetWindowHeight())* -1),		// Choose the larger angle (in radians) between the maximum angle range to the right and the angle to the bottom right corner of the screen (the tan function again).
			min(glm::radians(angleRange / 2), glm::atan(trans.x / ofGetWindowHeight())));									// Choose the smaller angle (in radians) between the maximum angle range to the left and the angle to the bottom left corner of the screen (the tan function).
		sprite.velocity = ofVec3f(cos(sprite.rot)*velocity.x - sin(sprite.rot)*velocity.y, sin(sprite.rot)*velocity.x + cos(sprite.rot)*velocity.y, 0);	// rotate the default velocity by the new angle
		sprite.speed = velocity.length() / ofGetFrameRate();
		sprite.lifespan = lifespan;
		sprite.setPosition(ofVec3f(trans.x, trans.y, 0));
		sprite.rot = rot;
		sprite.birthtime = time;
		sprite.height = height;
		sprite.width = width;
		sprite.health = spriteHealth;
		sprite.pointValue = spritePointValue;
		sys->add(sprite);
		lastSpawned = time;
	}
}

void EnemyEmitter::setSpriteSheet(vector<ofImage> sh, int nFrames) {
	bAnimateSprites = true;
	frames = nFrames;
	spriteSheet = sh;
}


Turret::Turret(SpriteSystem *spriteSys) {
	sys = spriteSys;
	lifespan = 1500;    // milliseconds
	started = false;
	bShooting = false;	// tells when spacebar is held down to shoot projectiles
	lastSpawned = 0;
	rate = 4;			// sprites/sec
	haveChildImage = true;
	haveImage = false;
	velocity = ofVec3f(0, -1000, 0);
}

void Turret::setSoundEffect(ofSoundPlayer sound) {
	soundEffect = sound;
	hasSound = true;
}

// The method to fire the turret instead of .update(), so it can verify that it should be firing right now
//
void Turret::update()
{
	if (!started) {
		return; 
	}

	float time = ofGetElapsedTimeMillis();
	if ((time - lastSpawned) > (1000.0 / rate)) {
		if (bShooting) {
			Sprite sprite;
			if (haveChildImage) sprite.setImage(childImage);
			sprite.velocity = velocity;
			sprite.speed = velocity.length() / ofGetFrameRate();
			sprite.lifespan = lifespan;
			sprite.setPosition(ofVec3f(trans.x, trans.y, 0));
			sprite.rot = rot;
			sprite.birthtime = time;
			sprite.height = height;
			sprite.width = width;
			sys->add(sprite);
			lastSpawned = time;
			if (hasSound) soundEffect.play();
			side = side * -1;
		}
	}
}