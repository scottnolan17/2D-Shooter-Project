
#include "ofMain.h"
#include "SpriteSystem.h"

// Reduce a sprite's health by 1 if it's colliding with another sprite
// from the given SpriteSystem, and also increment score
int SpriteSystem::checkCollision(Sprite *s) {
	for (int i = 0; i < sprites.size(); i++) {
		if ((sprites[i].trans - s->trans).length() < sprites[i].width / 2 + s->width / 2) {	// check for collision by radius
			s->health--;
			sprites[i].health--;	
			if (s->health <= 0) return s->pointValue;		// + extra points for a kill
			return 10;										// +1 point for a single hit
		}
	}
	return 0;
}

// Checks if the player is running into any sprite from the given system (presumably enemies),
// and reacts accordingly
void SpriteSystem::checkCollision(Player *p) {
	if (p->isDamaged()) return;	// don't care if we're running into anything while we're already damaged
	for (int i = 0; i < sprites.size(); i++) {
		Sprite s = sprites[i];
		if (p->position.x - p->getWidth() / 2 + 5 < s.trans.x + s.width / 2 &&		// Check for collision by bounding box
			p->position.x + p->getWidth() / 2 - 5 > s.trans.x - s.width / 2 &&		//
			p->position.y - p->getHeight() / 2 + 8 < s.trans.y + s.height / 2 &&	// The player's bounding box is a little smaller than the
			p->position.y + p->getHeight() / 2 - 15 > s.trans.y - s.height / 2) {	// actual image is, just to make it a little easier.
			p->damage();
			sprites[i].health = 0;	// Kill the sprite injuring the player, but for no points.
			return;
		}
	}
}

//  Add a Sprite to the Sprite System
//
void SpriteSystem::add(Sprite s) {
	sprites.push_back(s);
}

// Remove a sprite from the sprite system. Note that this function is not currently
// used. 
//
void SpriteSystem::remove(int i) {
	sprites.erase(sprites.begin() + i);
}

// Give a death sound effect for the sprites in this system.
//
void SpriteSystem::setDeathSound(ofSoundPlayer sound) {
	spriteDeathSound = sound;
	hasDeathSound = true;
}

//  Update the SpriteSystem by checking which sprites have exceeded their
//  lifespan (and deleting).  Also the sprite is moved to its next
//  location based on velocity and direction.
//
void SpriteSystem::update() {

	if (sprites.size() == 0) return;
	vector<Sprite>::iterator s = sprites.begin();
	vector<Sprite>::iterator tmp;

	// check which sprites have exceed their lifespan and delete
	// from list.  When deleting multiple objects from a vector while
	// traversing at the same time, use an iterator.
	//
	while (s != sprites.end()) {
		if (s->lifespan != -1 && s->age() > s->lifespan || s->trans.y > ofGetWindowHeight() + s->height/2) {
			tmp = sprites.erase(s);
			s = tmp;
		}
		else s++;
	}

	// kill the sprites with no health left
	s = sprites.begin();
	while (s != sprites.end()) {
		if (s->health <= 0) {
			if (hasDeathEffect) {
				deathEffectEmitter->setPosition(s->trans);
				deathEffectEmitter->emit();
				
			}
			if (hasDeathSound) spriteDeathSound.play();
			//			cout << "deleting sprite: " << s->name << endl;
			tmp = sprites.erase(s);
			s = tmp;
		}
		else s++;
	}


	//  Move sprites
	//
	for (int i = 0; i < sprites.size(); i++)  sprites[i].trans += sprites[i].velocity / ofGetFrameRate();				
}

//  Render all the sprites
//
void SpriteSystem::draw() {
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i].draw();
	}
}