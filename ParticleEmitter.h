#pragma once

#include "ParticleSystem.h"
#include "BaseObject.h"

// duplicated from Lab 6

class ParticleEmitter : public BaseObject {
public:
	ParticleEmitter();
	ParticleEmitter(ParticleSystem *s);
	~ParticleEmitter();
	void init();
	void draw();
	void setLifespan(const float life) { lifespan = life; }
	void setVelocity(const ofVec3f &vel) { velocity = vel; }
	void setParticleSize(const float r) { particleSize = r; }
	void setGroupSize(int s) { groupSize = s; }
	void emit();
	void spawn(float time);
	ParticleSystem *sys;
	ofVec3f velocity;
	float lifespan;     // sec
	float particleSize;
	float damping;
	int groupSize;      // number of particles to spawn in a group
	bool createdSys;
};
