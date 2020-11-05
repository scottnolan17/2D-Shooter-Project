#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "SpriteEmitter.h"
#include "Button.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void gameOver();	// when ending a game
		void initGame();	// when starting a game

		int score;
		vector<int> highScores;	// store the player's scores; this won't ever end up holding more than 10
		int numSpawners;
		float spawnRate;
		float difficultyScale;
		float irregularityScale;
		ofVec3f enemyVelocity;

		float scoreMultiplier = 1.0;

		Screen currentScreen;

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		SpriteSystem *playerSprites;	// aka bullets
		Turret *turret;					// the turret that lives on the player's plane
		Player *player;

		SpriteSystem *enemies;
		vector<EnemyEmitter *> spawns;

		ParticleSystem *particleSystem;		// These use different systems so that the player can have a giant particle explosion
		ParticleSystem *playerParticles;	// when they die, which calls for different forces and drag.
		ParticleEmitter *playerDeath;
		ControlForce *controls;

		ofImage backgroundImage;
		ofImage playerImage;
		ofImage playerLeft;
		ofImage playerRight;
		ofImage projectileImage;
		vector<ofImage> enemyImages;			// My collection of diy "sprite sheets" that I
		vector<ofImage> enemy1Sprites;			// resorted to when getting rid of the sprite
		vector<ofImage> enemy2Sprites;			// wobble from frame to frame became too hard. 
		vector<ofImage> playerCenterSprites;	// Plus I get to use drawImage() instead of
		vector<ofImage> playerLeftSprites;		// drawSubsection(), which is just easier.
		vector<ofImage> playerRightSprites;		//
		ofSoundPlayer shotSound;
		ofSoundPlayer hitSound;
		ofTrueTypeFont silkscreen;
		ofTrueTypeFont bigFont;					// for the high scores and game over screen
		ofTrueTypeFont titleFont;				// for the title screen
		ofVec3f mousePos;
		
		bool imageLoaded;
		float backGroundProportions;
		int imageOffset = 0;

		bool bForward, bBack, bLeft, bRight = false;

		char scoreDisp[64];			// contains the score display string in the bottom left while playing
		char finalScore[64];		// contains the score string that displays on game over
		char highScoresDisp[64];	// contains the placement and value of a score to be displayed on the high scores screen
		char multDisp[64];			// contains the score multiplier string that displays when customizing difficulty
		float healthBoxLength;
		float HP_BOX_LENGTH;
		float HP_BOX_HEIGHT;
		float LINE_WIDTH;
		float EDGE_PADDING;

		Button *startGame;
		Button *difficultyOptions;
		Button *viewScores;

		OptionButton *numEnemySpawnersButton;
		OptionButton *spawnRateButton;
		OptionButton *enemyVelocityButton;
		OptionButton *enemyFlightIrregularityButton;
		OptionButton *playerFireRateButton;
		Button *difficultyReturn;

		Button *scoresReturn;

		Button *newGame;
		Button *gameOverReturn;
};
