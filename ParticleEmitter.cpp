
#include "ParticleEmitter.h"

// duplicated from Lab 6

ParticleEmitter::ParticleEmitter() {
	sys = new ParticleSystem();
	createdSys = true;
	init();
}

ParticleEmitter::ParticleEmitter(ParticleSystem *s) {
	if (s == NULL)
	{
		cout << "fatal error: null particle system passed to ParticleEmitter()" << endl;
		ofExit();
	}
	sys = s;
	createdSys = false;
	init();
}

ParticleEmitter::~ParticleEmitter() {

	// deallocate particle system if emitter created one internally
	//
	if (createdSys) delete sys;
} 

void ParticleEmitter::init() {
	trans = ofVec3f(0, 0, 0);
	velocity = ofVec3f(0, 20, 0);
	lifespan = 0.75;
	particleSize = 3;
	groupSize = 150;
	damping = 0.94;
}


// The emitter will always be invisible, so we only need to draw the particles themselves
void ParticleEmitter::draw() {
	sys->draw();
}


// A far simpler emitter than the one in Lab 6 it's derived from:
// it emits its particles whenever it's called, with no automatic repeat functionality.
// This is because we will only need to emit a particle cloud when one-off events happen (i.e. a sprite dies).
// Therefore, each sprite that may need to emit particle will have to store one of these emitters to call.
//
void ParticleEmitter::emit() {
	float time = ofGetElapsedTimeMillis();
	for (int i = 0; i < groupSize; i++) spawn(time);
}

// Spawn a single particle travelling in a random direction out from the emitter.
// Time is the time of particle creation (so it should be right now)
//
void ParticleEmitter::spawn(float time) {

	Particle particle;

	ofVec3f dir = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), 0);
	float speed = velocity.length();
	particle.velocity = dir.getNormalized() * ofRandom(0, speed);
	particle.position.set(trans);

	particle.lifespan = lifespan;
	particle.birthtime = time;
	particle.size = particleSize;
	particle.damping = damping;

	sys->add(particle);
}
