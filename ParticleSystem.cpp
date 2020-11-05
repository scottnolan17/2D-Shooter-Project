#include "ParticleSystem.h"

// duplicated from Lab 6

void ParticleSystem::add(const Particle &p) {
	particles.push_back(p);
}

void ParticleSystem::addForce(ParticleForce *f) {
	forces.push_back(f);
}

void ParticleSystem::remove(int i) {
	particles.erase(particles.begin() + i);
}

void ParticleSystem::setLifespan(float l) {
	for (int i = 0; i < particles.size(); i++) {
		particles[i].lifespan = l;
	}
}

void ParticleSystem::reset() {
	for (int i = 0; i < forces.size(); i++) {
		forces[i]->applied = false;
	}
}

void ParticleSystem::update() {
	// check if empty and just return
	if (particles.size() == 0) return;

	vector<Particle>::iterator p = particles.begin();
	vector<Particle>::iterator tmp;

	// check which particles have exceed their lifespan and delete
	// from list.  When deleting multiple objects from a vector while
	// traversing at the same time, we need to use an iterator.
	//
	while (p != particles.end()) {
		if (p->lifespan != -1 && p->age() > p->lifespan) {
			tmp = particles.erase(p);
			p = tmp;
		}
		else p++;
	}

	// update forces on all particles first 
	//
	for (int i = 0; i < particles.size(); i++) {
		for (int k = 0; k < forces.size(); k++) {

			// if the force should only be applied to each particle once...
			if (forces[k]->applyOnce) {
				if (particles[i].justCreated) {
					forces[k]->updateForce(&particles[i]);
					particles[i].justCreated = false;
				}
			}

			// otherwise, apply the forces as normal
			else forces[k]->updateForce(&particles[i]);
		}
	}

	// integrate all the particles in the store
	//
	for (int i = 0; i < particles.size(); i++)
		particles[i].integrate();

}


//  draw the particle cloud
//
void ParticleSystem::draw() {
	for (int i = 0; i < particles.size(); i++) {
		particles[i].draw();
	}
}



// Create the one-off outward force to apply to the particle
//
ImpulseRadialForce::ImpulseRadialForce(float magnitude) {
	this->magnitude = magnitude;
	applyOnce = true;
}

void ImpulseRadialForce::updateForce(Particle * particle) {
	ofVec3f dir = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), 0);
	particle->forces += dir.getNormalized() * ofRandom(magnitude/10, magnitude);
}


// Initialize the strength of the drag to everything on screen
//
DragForce::DragForce(float strength) {
	this->strength = strength;
}

void DragForce::updateForce(Particle *particle) {
	particle->forces += ofVec3f(0, strength, 0);		// increase y value to blow particles downward on screen
}


// Initialize the controlling force representing the player's wasd inputs.
// This force will only apply to the player's plane and will not be part of a particle system.
//
ControlForce::ControlForce(float fb, float lr) {
	this->throttleControl = fb;
	this->bankControl = lr;
	this->forceDir = ofVec3f(0, 0, 0);
}

// Use a provided vector, devised by the main app based on player inputs,
// to act as a controlling force
//
void ControlForce::updateControl(ofVec3f input) {
	this->forceDir = input;
	this->forceDir.x *= bankControl;
	this->forceDir.y *= throttleControl;
}

// Apply the new force to the particle; note this should only be used on the Player subclass of particle
//
void ControlForce::updateForce(Particle *particle) {
	particle->forces += this->forceDir * particle->mass;
}