#pragma once

#include "Sprite.h"
#include "ParticleEmitter.h"

//  Manages all Sprites in a system.  You can create multiple systems
//
class SpriteSystem {
public:
	void add(Sprite);
	void remove(int);
	void update();
	void draw();
	void setDeathSound(ofSoundPlayer);
	int checkCollision(Sprite *);					// checks if any sprite in this system is colldiing with the given sprite and, if so, deletes that sprite and returns the point to add
	void checkCollision(Player *);					// checks if the player is colliding with any sprites in this system, and reacts accordingly
	vector<Sprite> sprites;

	bool hasDeathEffect = false;
	ParticleEmitter *deathEffectEmitter;
	bool hasDeathSound;
	ofSoundPlayer spriteDeathSound;
};

