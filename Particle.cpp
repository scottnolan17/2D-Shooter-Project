#include "Particle.h"

// duplicated from Lab 6

Particle::Particle() {

	velocity.set(0, 0, 0);
	acceleration.set(0, 0, 0);
	position.set(0, 0, 0);
	forces.set(0, 0, 0);
	lifespan = 1;
	birthtime = 0;
	size = 1;
	damping = .99;
	mass = 1;
	color = ofColor::whiteSmoke;
}

void Particle::draw() {
	int col = ofMap(age(), 0, lifespan, 200, 255);	// particle ages so that it fades
	ofSetColor(col, col, col);						// from grey to white for a smoke effect
	ofDrawBox(position, size);
	ofSetColor(255);								// return color back to normal
}

void Particle::integrate() {

	float fr = ofGetFrameRate();
	if (fr == 0) fr = 60.0;
	float dt = 1.0 / fr;
	position += (velocity * dt);

	ofVec3f accel = acceleration; 
	accel += (forces * (1.0 / mass));
	velocity += accel * dt;
	velocity *= damping;

	forces.set(0, 0, 0);
}

//  return age in seconds
//
float Particle::age() {
	return (ofGetElapsedTimeMillis() - birthtime) / 1000.0;
}

// A specialized particle to allow the player to have physics based controls.
// See particle.h for a more detailed explanation
void Player::setImage(ofImage newImage) {
	image = newImage;
	width = newImage.getWidth();
	height = newImage.getHeight();
}

// Turns the player into an animated sprite.
// Note that it says "sprite sheet" even though it's really just a vector of seperate sprites.
// This is because I originally used a sprite sheet format, but it was a little wobbly when
// transitioning sprites, so I used this low-effort method instead.
//
void Player::setSpriteSheet(vector<ofImage> sh, int nFr) {
	bAnimated = true;
	nFrames = nFr;
	sprites = sh;
}

void Player::draw() {
	ofImage temp = image;

	if (bAnimated) {
		temp = sprites[frame];
		if (ofGetElapsedTimeMillis() - lastFrame >= frameSpeedDiv) {
			frame++; // increment the frame of the animation
			frame = frame % nFrames;
			lastFrame = ofGetElapsedTimeMillis();
		}
	}

	if (!damaged) temp.draw(-width / 2.0 + position.x, -height / 2.0 + position.y);
	else {
		// check if the player's grace period has ended
		if (ofGetElapsedTimeMillis() - hitTime >= GRACE_PERIOD) {
			damaged = false;
			temp.draw(-width / 2.0 + position.x, -height / 2.0 + position.y);
		}
		// create flashing effect to show grace period duration:
		// flash 4 times at regular intervals; only draw the plane if in between those intervals
		else if ((int)(ofGetElapsedTimeMillis()-hitTime) % (GRACE_PERIOD / 8) > GRACE_PERIOD / 16) temp.draw(-width / 2.0 + position.x, -height / 2.0 + position.y);
	} 
}

// Same as normal Particle::integrate(), but with the functionality to keep the player on the screen.
//
void Player::integrate() {

	float fr = ofGetFrameRate();
	if (fr == 0) fr = 60.0;
	float dt = 1.0 / fr;
	position += (velocity * dt);

	ofVec3f accel = acceleration;
	accel += (forces * (1.0 / mass));
	velocity += accel * dt;
	velocity *= damping;

	forces.set(0, 0, 0);
	
	
	// make sure the plane can't leave the window
	if (position.x - width/2 < 0) {
		position.x = width/2;
		velocity.x = 0;
	}
	else if (position.x + width/2 > ofGetWindowWidth()) {
		position.x = ofGetWindowWidth() - width/2;
		velocity.x = 0;
	}
	if (position.y - height/2 < 0) {
		position.y = height/2;
		velocity.y = 0;
	}
	else if (position.y + height/2 > ofGetWindowHeight()) {
		position.y = ofGetWindowHeight() - height/2;
		velocity.y = 0;
	}
}

// Take away some health...
//
void Player::damage() {
	hitTime = ofGetElapsedTimeMillis();
	damaged = true;
	health--;
} 