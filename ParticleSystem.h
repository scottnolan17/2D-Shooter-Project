#pragma once

#include "ofMain.h"
#include "Particle.h"

// duplicated from Lab 6

//  Pure Virtual Function Class - must be subclassed to create new forces.
//
class ParticleForce {
protected:
public:
	bool applyOnce = false;
	bool applied = false;
	virtual void updateForce(Particle *) = 0;
};

class ParticleSystem {
public:
	void add(const Particle &);
	void addForce(ParticleForce *);
	void remove(int);
	void update();
	void setLifespan(float);
	void reset();
	void draw();
	vector<Particle> particles;
	vector<ParticleForce *> forces;
};


// Force to propel all the death cloud particle outward, initally and randomly.
// Only applied to a particle once.
//
class ImpulseRadialForce : public ParticleForce {
	float magnitude;
public:
	ImpulseRadialForce(float);
	void updateForce(Particle *);
};

// Backward force continually applied to simulate drag on the particles.
//
class DragForce : public ParticleForce {
	float strength;
public:
	DragForce(float);
	void updateForce(Particle *);
};

// Force representing the player's control inputs to the plane.
// The control is physics based to simulate a real plane's throttle and banking ability. 
//
class ControlForce : public ParticleForce {
	float throttleControl;	// front/back movement controls			|	These are different values because realistically, a plane's throttle acceleration
	float bankControl;		// left/right movement controls			|	is probably going to be a little tighter than its turning by banking
	ofVec3f forceDir;
public:
	ControlForce(float, float);
	void updateControl(ofVec3f);
	void updateForce(Particle *);
};