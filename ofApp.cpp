#include "ofApp.h"
//----------------------------------------------------------------------------------
//
// SJSU CS134 Spring 2020 
// 
// Stage 3 (Final!) of the 2D shooter project:
// - added actual playability
//		- keeps score
//		- player and enemies have more than 1 hit point
//		- increased difficulty over time
//			- higher spawn rate and path randomness
//			- higher difficulty can be activated from the start for a score multiplier
// - physics features
//		- planes make a puff of smoke when blown up that blows in the breeze
//		- player controls are physics oriented, like a real plane (it's no flight sim, but it's not too bad!)
// - added UI
//		- navigable menus to change difficulty, restart, view score, and of course, start the game
//		- reactive player health bar in bottom right
//		- live score counter in the bottom left
// - new visuals
//		- scrolling background so it feels like the planes are actually flying
//		- planes have spinning propellers, and the player's plane visibly banks when moving laterally
//
// Scott Nolan


//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);
	ofToggleFullscreen();	// start in fullscreen, because no self-respecting gamer plays in windowed mode

	float ratio;

	// create an image for all the enemy sprites
	//
	ofImage enem1, enem2, enem3, enem4;
	if (enem1.load("images/enemy1.png") && enem2.load("images/enemy2.png")) {
		imageLoaded = true;
		ratio = enem1.getHeight() / enem1.getWidth();
		enem1.resize(ofGetWindowWidth()/16, ratio * ofGetWindowWidth()/16);
		enem2.resize(ofGetWindowWidth()/16, ratio * ofGetWindowWidth()/16);
		enemyImages.push_back(enem1);
		enemyImages.push_back(enem2);
		enemyImages[0].rotate90(2);
		enemyImages[1].rotate90(2);
	}
	else {
		ofLogFatalError("can't load images: images/enemy1.png or images/enemy2.png");
		ofExit();
	}

	// create the sprite sheets for enemy 1's sprites
	//
	if (enem1.load("images/enemy1_1.png") && enem2.load("images/enemy1_2.png") && enem3.load("images/enemy1_3.png") && enem4.load("images/enemy1_4.png")) {
		enem1.resize(enemyImages[0].getWidth(), enemyImages[0].getHeight());
		enem2.resize(enemyImages[0].getWidth(), enemyImages[0].getHeight());
		enem3.resize(enemyImages[0].getWidth(), enemyImages[0].getHeight());
		enem4.resize(enemyImages[0].getWidth(), enemyImages[0].getHeight());
		enemy1Sprites.push_back(enem1);
		enemy1Sprites.push_back(enem2);
		enemy1Sprites.push_back(enem3);
		enemy1Sprites.push_back(enem4);
		enemy1Sprites[0].rotate90(2);
		enemy1Sprites[1].rotate90(2);
		enemy1Sprites[2].rotate90(2);
		enemy1Sprites[3].rotate90(2);
	}
	else {
		ofLogFatalError("can't load images: images/enemy1_1.png, images/enemy1_2.png, images/enemy1_3.png, or images/enemy1_4.png");
		ofExit();
	}


	// create the sprite sheets for enemy 2's sprites
	//
	if (enem1.load("images/enemy2_1.png") && enem2.load("images/enemy2_2.png") && enem3.load("images/enemy2_3.png") && enem4.load("images/enemy2_4.png")) {
		enem1.resize(enemyImages[0].getWidth(), enemyImages[0].getHeight());
		enem2.resize(enemyImages[0].getWidth(), enemyImages[0].getHeight());
		enem3.resize(enemyImages[0].getWidth(), enemyImages[0].getHeight());
		enem4.resize(enemyImages[0].getWidth(), enemyImages[0].getHeight());
		enemy2Sprites.push_back(enem1);
		enemy2Sprites.push_back(enem2);
		enemy2Sprites.push_back(enem3);
		enemy2Sprites.push_back(enem4);
		enemy2Sprites[0].rotate90(2);
		enemy2Sprites[1].rotate90(2);
		enemy2Sprites[2].rotate90(2);
		enemy2Sprites[3].rotate90(2);
	}
	else {
		ofLogFatalError("can't load images: images/enemy2_1.png, images/enemy2_2.png, images/enemy2_3.png, or images/enemy2_4.png");
		ofExit();
	}


	// create the player's sprites
	if (!projectileImage.load("images/bullet.png") || !playerImage.load("images/plane.png") || !playerLeft.load("images/plane_left.png") || !playerRight.load("images/plane_right.png")) {
		ofLogFatalError("can't load image: images/bullet.png, images/plane_left.png, images/plane_right.png, or images/plane.png");
		ofExit();
	}
	ratio = playerImage.getHeight() / playerImage.getWidth();
	playerImage.resize(ofGetWindowWidth()/16, ratio * ofGetWindowWidth() / 16);
	ratio = playerLeft.getWidth() / playerLeft.getHeight();
	playerLeft.resize(playerImage.getHeight() * ratio, playerImage.getHeight());
	playerRight.resize(playerLeft.getWidth(), playerLeft.getHeight());


	// create the player's animated sprites
	//
	ofImage pl1, pl2, pl3, pl4;
	if (pl1.load("images/plane_1.png") && pl2.load("images/plane_2.png") && pl3.load("images/plane_3.png") && pl4.load("images/plane_4.png")) {
		pl1.resize(playerImage.getWidth(), playerImage.getHeight());
		pl2.resize(playerImage.getWidth(), playerImage.getHeight());
		pl3.resize(playerImage.getWidth(), playerImage.getHeight());
		pl4.resize(playerImage.getWidth(), playerImage.getHeight());
		playerCenterSprites.push_back(pl1);
		playerCenterSprites.push_back(pl2);
		playerCenterSprites.push_back(pl3);
		playerCenterSprites.push_back(pl4);
	}
	else {
		ofLogFatalError("can't load images: images/plane_1.png, images/plane_2.png, images/plane_3.png, or images/plane_4.png");
		ofExit();
	}

	if (pl1.load("images/left_1.png") && pl2.load("images/left_2.png") && pl3.load("images/left_3.png") && pl4.load("images/left_4.png")) {
		pl1.resize(playerLeft.getWidth(), playerLeft.getHeight());
		pl2.resize(playerLeft.getWidth(), playerLeft.getHeight());
		pl3.resize(playerLeft.getWidth(), playerLeft.getHeight());
		pl4.resize(playerLeft.getWidth(), playerLeft.getHeight());
		playerLeftSprites.push_back(pl1);
		playerLeftSprites.push_back(pl2);
		playerLeftSprites.push_back(pl3);
		playerLeftSprites.push_back(pl4);
	}
	else {
		ofLogFatalError("can't load images: images/left_1.png, images/left_2.png, images/left_3.png, or images/left_4.png");
		ofExit();
	}

	if (pl1.load("images/right_1.png") && pl2.load("images/right_2.png") && pl3.load("images/right_3.png") && pl4.load("images/right_4.png")) {
		pl1.resize(playerRight.getWidth(), playerRight.getHeight());
		pl2.resize(playerRight.getWidth(), playerRight.getHeight());
		pl3.resize(playerRight.getWidth(), playerRight.getHeight());
		pl4.resize(playerRight.getWidth(), playerRight.getHeight());
		playerRightSprites.push_back(pl1);
		playerRightSprites.push_back(pl2);
		playerRightSprites.push_back(pl3);
		playerRightSprites.push_back(pl4);
	}
	else {
		ofLogFatalError("can't load images: images/right_1.png, images/right_2.png, images/right_3.png, or images/right_4.png");
		ofExit();
	}


	// create the background
	if (!backgroundImage.load("images/backdrop.png")) {
		ofLogFatalError("can't load image: images/backdrop.png");
		ofExit();
	}
	backGroundProportions = backgroundImage.getHeight() / backgroundImage.getWidth();

	// create the shooting sound effect
	if (!shotSound.load("sounds/shot.wav")) {
		ofLogFatalError("can't load sound: shot.wav or hit.wav");
		ofExit();
	}
	shotSound.setVolume(0.2);

	// create the shooting hit sound effect
	if (!hitSound.load("sounds/hit.wav")) {
		ofLogFatalError("can't load sound: shot.wav or hit.wav");
		ofExit();
	}
	hitSound.setVolume(0.3);

	// import the fonts for the game
	if (!silkscreen.load("slkscr.ttf", ofGetWindowHeight()/25) || !bigFont.load("slkscr.ttf", ofGetWindowHeight()/16) || !titleFont.load("slkscr.ttf", ofGetWindowHeight() / 8)) {
		ofLogFatalError("can't load font: slkscr.ttf");
		ofExit();
	}

	silkscreen.setLetterSpacing(0.8);
	


	currentScreen = menu;

	LINE_WIDTH = ofGetWindowHeight() / 125;	// one fifth the hp bar's height
	HP_BOX_LENGTH = ofGetWindowWidth() / 4;
	HP_BOX_HEIGHT = ofGetWindowHeight() / 25 - (2 * LINE_WIDTH);	// the bar height + the 2 lines = the same height as the font
	EDGE_PADDING = 10;
	// ^ these are caps because they were originally constants, but then I made it depend on the screen size and constants don't like variable values

	healthBoxLength = HP_BOX_LENGTH;
	ofSetLineWidth(LINE_WIDTH);
	
	// Setup main menu buttons
	startGame = new Button(ofVec3f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 5 * 3, 0));
	startGame->setText("Play Game!");
	startGame->setWidth(ofGetWindowWidth() / 2);
	startGame->setHeight(ofGetWindowHeight() / 10);
	startGame->setScreen(starting);
	difficultyOptions = new Button(ofVec3f(startGame->trans.x, startGame->trans.y + startGame->height + 30, 0));
	difficultyOptions->setText("Difficulty");
	difficultyOptions->setScreen(difficulty);
	difficultyOptions->setWidth(ofGetWindowWidth() / 2);
	difficultyOptions->setHeight(ofGetWindowHeight() / 10);
	viewScores = new Button(ofVec3f(difficultyOptions->trans.x, difficultyOptions->trans.y + difficultyOptions->height + 30, 0));
	viewScores->setText("High Scores");
	viewScores->setScreen(scores);
	viewScores->setWidth(ofGetWindowWidth() / 2);
	viewScores->setHeight(ofGetWindowHeight() / 10);

	// Setup difficulty option buttons
	numEnemySpawnersButton = new OptionButton(ofVec3f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 3, 0));
	numEnemySpawnersButton->setText("Number of Enemy Spawners : ");
	numEnemySpawnersButton->addOption("Low");
	numEnemySpawnersButton->addOption("Medium");
	numEnemySpawnersButton->addOption("High");
	numEnemySpawnersButton->addOption("Inhuman");
	numEnemySpawnersButton->currentOption = 1;
	numEnemySpawnersButton->setWidth(ofGetWindowWidth() / 1.2);
	numEnemySpawnersButton->setHeight(ofGetWindowHeight() / 15);
	spawnRateButton = new OptionButton(ofVec3f(numEnemySpawnersButton->trans.x, numEnemySpawnersButton->trans.y + numEnemySpawnersButton->height + 30, 0));
	spawnRateButton->setText("Enemy Spawn Rate : ");
	spawnRateButton->addOption("Low");
	spawnRateButton->addOption("Medium");
	spawnRateButton->addOption("High");
	spawnRateButton->addOption("Overwhelming");
	spawnRateButton->currentOption = 1;
	spawnRateButton->setWidth(ofGetWindowWidth() / 1.2);
	spawnRateButton->setHeight(ofGetWindowHeight() / 15);
	enemyVelocityButton = new OptionButton(ofVec3f(spawnRateButton->trans.x, spawnRateButton->trans.y + spawnRateButton->height + 30, 0));
	enemyVelocityButton->setText("Enemy Airspeed : ");
	enemyVelocityButton->addOption("Slow");
	enemyVelocityButton->addOption("Medium");
	enemyVelocityButton->addOption("Fast");
	enemyVelocityButton->addOption("Turbo");
	enemyVelocityButton->currentOption = 1;
	enemyVelocityButton->setWidth(ofGetWindowWidth() / 1.2);
	enemyVelocityButton->setHeight(ofGetWindowHeight() / 15);
	enemyFlightIrregularityButton = new OptionButton(ofVec3f(enemyVelocityButton->trans.x, enemyVelocityButton->trans.y + enemyVelocityButton->height + 30, 0));
	enemyFlightIrregularityButton->setText("Enemy Flight Irregularity Scaling : ");
	enemyFlightIrregularityButton->addOption("Low");
	enemyFlightIrregularityButton->addOption("Medium");
	enemyFlightIrregularityButton->addOption("High");
	enemyFlightIrregularityButton->addOption("Crazy");
	enemyFlightIrregularityButton->currentOption = 1;
	enemyFlightIrregularityButton->setWidth(ofGetWindowWidth() / 1.2);
	enemyFlightIrregularityButton->setHeight(ofGetWindowHeight() / 15);
	playerFireRateButton = new OptionButton(ofVec3f(enemyFlightIrregularityButton->trans.x, enemyFlightIrregularityButton->trans.y + enemyFlightIrregularityButton->height + 30, 0));
	playerFireRateButton->setText("Player fire rate : ");
	playerFireRateButton->addOption("Low");
	playerFireRateButton->addOption("Medium");
	playerFireRateButton->addOption("High");
	playerFireRateButton->addOption("Super High");
	playerFireRateButton->currentOption = 1;
	playerFireRateButton->setWidth(ofGetWindowWidth() / 1.2);
	playerFireRateButton->setHeight(ofGetWindowHeight() / 15);
	difficultyReturn = new Button(ofVec3f(playerFireRateButton->trans.x, playerFireRateButton->trans.y + playerFireRateButton->height + 30, 0));
	difficultyReturn->setText("Back");
	difficultyReturn->setWidth(ofGetWindowWidth() / 2);
	difficultyReturn->setHeight(ofGetWindowHeight() / 12);
	difficultyReturn->setScreen(menu);

	// Setup high scores screen buttons
	scoresReturn = new Button(ofVec3f(ofGetWindowWidth() / 2, ofGetWindowHeight()/8*7, 0));
	scoresReturn->setText("Back");
	scoresReturn->setWidth(ofGetWindowWidth() / 2);
	scoresReturn->setHeight(ofGetWindowHeight() / 12);
	scoresReturn->setScreen(menu);

	// Setup game over screen buttons
	newGame = new Button(ofVec3f(ofGetWindowWidth() / 8 * 3 - 20, ofGetWindowHeight()/ 3 * 2, 0));
	newGame->setText("Play Again");
	newGame->setWidth(ofGetWindowWidth() / 4);
	newGame->setHeight(ofGetWindowHeight() / 12);
	newGame->setScreen(starting);
	gameOverReturn = new Button(ofVec3f(ofGetWindowWidth() / 8 * 5 + 20, ofGetWindowHeight() / 3 * 2, 0));
	gameOverReturn->setText("Main Menu");
	gameOverReturn->setWidth(ofGetWindowWidth() / 4);
	gameOverReturn->setHeight(ofGetWindowHeight() / 12);
	gameOverReturn->setScreen(menu);



	particleSystem = new ParticleSystem();
	particleSystem->addForce(new ImpulseRadialForce(20000));	// I need ridiculously large numbers here to overcome the strong damping effect.
	particleSystem->addForce(new DragForce(1500));				// Why is there such a strong damping effect? I think it makes the cloud puffs look cool.

	playerParticles = new ParticleSystem();
	playerParticles->addForce(new ImpulseRadialForce(20000));
	playerParticles->addForce(new DragForce(400));				// less drag on the player particles, so you have to sit there and stare at your death a little longer

	controls = new ControlForce(2000, 1600);

	playerDeath = new ParticleEmitter(playerParticles);
	playerDeath->damping = 0.99;
	playerDeath->lifespan = 3;
	playerDeath->setGroupSize(500);

	// create the player's sprite and set its position;
	//
	playerSprites = new SpriteSystem();

	player = new Player();
	player->position = ofVec3f(ofGetWindowWidth()/2, ofGetWindowHeight()/3*2, 0);	// start a little below center
	player->setImage(playerImage);
	player->setSpriteSheet(playerCenterSprites, 4);
	player->damping = 0.95;

	turret = new Turret(playerSprites);
	turret->setPosition(ofVec3f(ofGetWindowWidth()/2 - playerImage.getWidth()/6, ofGetWindowHeight()/2 - playerImage.getHeight()/6, 0));
	turret->drawable = false;
	turret->setChildImage(projectileImage);
	turret->setSoundEffect(shotSound);	
	turret->height = projectileImage.getHeight();
	turret->width = projectileImage.getWidth();
	turret->side = 1;
	turret->start();

	// create the enemy spawners on the top of the screen
	//
	enemies = new SpriteSystem();
	enemies->hasDeathEffect = true;
	enemies->setDeathSound(hitSound);
	enemies->deathEffectEmitter = new ParticleEmitter(particleSystem);


	numSpawners = 3;
	spawnRate = 0.4;
	enemyVelocity = ofVec3f(0, 450, 0);
	irregularityScale = 0.4;

	score = 0;
	difficultyScale = 0.005;	

	while (highScores.size() < 10) highScores.push_back(0);		// initialize the highScores list as all zeros
}

//--------------------------------------------------------------
void ofApp::update() {
	switch (currentScreen) {
	case menu:
		// Check if the player is highlighting any of the buttons.
		startGame->inside(mousePos);
		difficultyOptions->inside(mousePos);
		viewScores->inside(mousePos);

		// I reset the button sizes here so that they react when the player resizes the window.
		// I do the same thing with all the buttons on the other screens below.
		startGame->setPosition(ofGetWindowWidth() / 2, ofGetWindowHeight() / 5 * 3);
		startGame->setWidth(ofGetWindowWidth() / 2);
		startGame->setHeight(ofGetWindowHeight() / 10);
		difficultyOptions->setPosition(startGame->trans.x, startGame->trans.y + startGame->height + 30);
		difficultyOptions->setWidth(ofGetWindowWidth() / 2);
		difficultyOptions->setHeight(ofGetWindowHeight() / 10);
		viewScores->setPosition(difficultyOptions->trans.x, difficultyOptions->trans.y + difficultyOptions->height + 30);
		viewScores->setWidth(ofGetWindowWidth() / 2);
		viewScores->setHeight(ofGetWindowHeight() / 10);
		break;
	case difficulty:
		// Same procedure as with the main menu screen, but with a lot more buttons
		numEnemySpawnersButton->inside(mousePos);
		spawnRateButton->inside(mousePos);
		enemyVelocityButton->inside(mousePos);
		enemyFlightIrregularityButton->inside(mousePos);
		playerFireRateButton->inside(mousePos);
		difficultyReturn->inside(mousePos);

		numEnemySpawnersButton->setPosition(ofGetWindowWidth() / 2, ofGetWindowHeight() / 3);
		numEnemySpawnersButton->setWidth(ofGetWindowWidth() / 1.2);
		numEnemySpawnersButton->setHeight(ofGetWindowHeight() / 15);
		spawnRateButton->setPosition(numEnemySpawnersButton->trans.x, numEnemySpawnersButton->trans.y + numEnemySpawnersButton->height + 30);
		spawnRateButton->setWidth(ofGetWindowWidth() / 1.2);
		spawnRateButton->setHeight(ofGetWindowHeight() / 15);
		enemyVelocityButton->setPosition(spawnRateButton->trans.x, spawnRateButton->trans.y + spawnRateButton->height + 30);
		enemyVelocityButton->setWidth(ofGetWindowWidth() / 1.2);
		enemyVelocityButton->setHeight(ofGetWindowHeight() / 15);
		enemyFlightIrregularityButton->setPosition(enemyVelocityButton->trans.x, enemyVelocityButton->trans.y + enemyVelocityButton->height + 30);
		enemyFlightIrregularityButton->setWidth(ofGetWindowWidth() / 1.2);
		enemyFlightIrregularityButton->setHeight(ofGetWindowHeight() / 15);
		playerFireRateButton->setPosition(enemyFlightIrregularityButton->trans.x, enemyFlightIrregularityButton->trans.y + enemyFlightIrregularityButton->height + 30);
		playerFireRateButton->setWidth(ofGetWindowWidth() / 1.2);
		playerFireRateButton->setHeight(ofGetWindowHeight() / 15);
		difficultyReturn->setPosition(playerFireRateButton->trans.x, playerFireRateButton->trans.y + playerFireRateButton->height + 30);
		difficultyReturn->setWidth(ofGetWindowWidth() / 2);
		difficultyReturn->setHeight(ofGetWindowHeight() / 12);
		break;
	case scores:
		scoresReturn->inside(mousePos);

		scoresReturn->setPosition(ofGetWindowWidth() / 2, ofGetWindowHeight() / 8 * 7);
		scoresReturn->setWidth(ofGetWindowWidth() / 2);
		scoresReturn->setHeight(ofGetWindowHeight() / 12);
		break;
	case starting:
		initGame();
		currentScreen = game;
		break;
	case over:
		newGame->inside(mousePos);
		gameOverReturn->inside(mousePos);

		newGame->setPosition(ofGetWindowWidth() / 8 * 3 - 20, ofGetWindowHeight() / 3 * 2);
		newGame->setWidth(ofGetWindowWidth() / 4);
		newGame->setHeight(ofGetWindowHeight() / 12);
		gameOverReturn->setPosition(ofGetWindowWidth() / 8 * 5 + 20, ofGetWindowHeight() / 3 * 2);
		gameOverReturn->setWidth(ofGetWindowWidth() / 4);
		gameOverReturn->setHeight(ofGetWindowHeight() / 12);
		break;
	case game:
		// Priority #1: update the controls first for those extra few microseconds of responsiveness
		controls->updateControl(ofVec3f(bRight * (1) + bLeft * (-1), bForward * (-1) + bBack * (1)));
		controls->updateForce(player);
		player->integrate();

		// switch the player's sprite if they are traveling left or right
		if (bLeft ^ bRight) {
			if (bLeft) {
				player->setImage(playerLeft);
				player->setSpriteSheet(playerLeftSprites, 4);
			}
			else {
				player->setImage(playerRight);
				player->setSpriteSheet(playerRightSprites, 4);
			}
		}
		else {
			player->setImage(playerImage);
			player->setSpriteSheet(playerCenterSprites, 4);
		}

		// update the turret so it stay right at the player
		turret->setPosition(ofVec3f(player->position.x + (turret->side*playerImage.getWidth() / 6), player->position.y - playerImage.getHeight() / 6, 0));
		turret->update();

		// keep all the spawners spawning
		for (int i = 0; i < spawns.size(); i++) {
			spawns[i]->update();
		}

		// check for any bullets hitting enemy planes, and award points
		int hit = 0;
		for (int i = 0; i < enemies->sprites.size(); i++) {
			hit = playerSprites->checkCollision(&enemies->sprites[i]);	// Check every enemy plane for collision with every bullet, every frame. Seems pretty miserably slow, but it's all I got.
			if (hit > 0) {
				score += hit * scoreMultiplier;

				// increase difficulty over time:
				for (int i = 0; i < spawns.size(); i++) {
					if (spawns[i]->rate < 4) spawns[i]->rate += difficultyScale; 				// increment spawn rate...
					if (spawns[i]->angleRange < 60) spawns[i]->angleRange += irregularityScale;	// and possible flight angle for every kill
				}
			}
		}

		// check if the player got hit by anyone
		enemies->checkCollision(player);
		if (player->getHealth() <= 0) gameOver();

		break;

	}	

	// these update no matter what, not just during the game screen, so that the particles and planes continue to float away while navigating the game over screen
	enemies->update();
	playerSprites->update();

	particleSystem->update();
	playerParticles->update();

}


//--------------------------------------------------------------
void ofApp::draw(){

	backgroundImage.resize(ofGetWindowWidth(), ofGetWindowWidth()*backGroundProportions);
	backgroundImage.drawSubsection(0, 0, ofGetWindowWidth(), ofGetWindowHeight(), 0, backgroundImage.getHeight()-ofGetWindowHeight()-imageOffset);
	imageOffset += 5;	// how far to scroll the background down by
	if (imageOffset > backgroundImage.getHeight() - ofGetWindowHeight()) imageOffset = 0;

	enemies->draw();
	playerSprites->draw();
	for (int i = 0; i < spawns.size(); i++) spawns[i]->draw();

	particleSystem->draw();
	playerParticles->draw();

	ofRectangle rect;	// this rectangle is used to hold boudning boxes when I need to .drawString() and i want the text centered

	switch(currentScreen) {
		// this looks like a hopeless nightmare of indecipherable lines of code, but they're mostly just drawing the buttons and the boxes with text
	case menu :
		startGame->draw();
		difficultyOptions->draw();
		viewScores->draw();
		rect = titleFont.getStringBoundingBox("Biplane", 0, 0);
		ofSetColor(0, 0, 0, 100);
		ofDrawRectangle(startGame->trans.x - startGame->width/2, startGame->trans.y - startGame->height/2 - 60 - ofGetWindowHeight()/3, startGame->width, ofGetWindowHeight()/3);
		ofSetColor(255);
		titleFont.drawString("Biplane", ofGetWindowWidth() / 2 - rect.width / 2, startGame->trans.y - startGame->height / 2 - 60 - ofGetWindowHeight() / 12 * 3 + rect.height/2);
		rect = titleFont.getStringBoundingBox("Barons", 0, 0);
		titleFont.drawString("Barons", ofGetWindowWidth() / 2 - rect.width / 2, startGame->trans.y - startGame->height / 2 - 60 - ofGetWindowHeight() / 12 + rect.height/2);

		break;
	case difficulty :
		numEnemySpawnersButton->draw();
		spawnRateButton->draw();
		enemyVelocityButton->draw();
		enemyFlightIrregularityButton->draw();
		playerFireRateButton->draw();
		difficultyReturn->draw();
		ofSetColor(0, 0, 0, 100);
		ofDrawRectangle(ofGetWindowWidth()/2 - numEnemySpawnersButton->width/2, numEnemySpawnersButton->trans.y - numEnemySpawnersButton->height*2, numEnemySpawnersButton->width, ofGetWindowHeight()/12);
		ofSetColor(255);
		sprintf(multDisp, "Score Multiplier : x%.1f", scoreMultiplier);
		rect = silkscreen.getStringBoundingBox(multDisp, 0, 0);
		silkscreen.drawString(multDisp, ofGetWindowWidth()/2 - rect.width/2, numEnemySpawnersButton->trans.y - numEnemySpawnersButton->height*1.4 + rect.height/2);
		break;
	case scores:
		scoresReturn->draw();
		ofSetColor(0, 0, 0, 100);
		ofDrawRectangle(ofGetWindowWidth()/4, EDGE_PADDING*4, ofGetWindowWidth()/2, ofGetWindowHeight()/8);
		ofDrawRectangle(ofGetWindowWidth()/4, EDGE_PADDING*5 + ofGetWindowHeight()/8, ofGetWindowWidth()/2, scoresReturn->trans.y - scoresReturn->height/2 - EDGE_PADDING*7 - ofGetWindowHeight()/8);
		ofSetColor(255);
		rect = bigFont.getStringBoundingBox("High Scores", 0, 0);
		bigFont.drawString("High Scores", ofGetWindowWidth()/2 - rect.width/2, EDGE_PADDING * 4 + ofGetWindowHeight()/16 + rect.height/2);
		for (int i = 0; i < highScores.size(); i++) {
			sprintf(highScoresDisp, "%d.	%010d", i+1, highScores[i]);
			rect = silkscreen.getStringBoundingBox(highScoresDisp, 0, 0);
			silkscreen.drawString(highScoresDisp, ofGetWindowWidth()/2 - rect.width/2, EDGE_PADDING*5 + ofGetWindowHeight()/8 + (scoresReturn->trans.y - scoresReturn->height/2 - EDGE_PADDING*7 - ofGetWindowHeight()/8)/11*(i+1) + rect.height/2);
		}
		break;
	case starting:
	case game :
		player->draw();

		sprintf(scoreDisp, "Score : %010d", score);			// Really digging at the bottom of my mental barrel here if I'm using C functions... This is the only way I know of padding a number with zeros at the front for that vintage arcade look.
		silkscreen.drawString(scoreDisp, EDGE_PADDING, ofGetWindowHeight() - EDGE_PADDING);

		if ((healthBoxLength / HP_BOX_LENGTH) * 10 != player->getHealth()) healthBoxLength = ((player->getHealth() / 10)*HP_BOX_LENGTH < healthBoxLength) ? healthBoxLength - 1 : healthBoxLength + 1;	// wow that's a long if statement, but it bascially just adjusts the current health bar size up or down to match the actual health.
		ofDrawRectangle(ofVec3f(ofGetWindowWidth() - HP_BOX_LENGTH - LINE_WIDTH - EDGE_PADDING - 1, ofGetWindowHeight() - HP_BOX_HEIGHT - LINE_WIDTH - EDGE_PADDING - 1, 0), healthBoxLength, HP_BOX_HEIGHT);
		ofNoFill();
		ofDrawRectangle(ofVec3f(ofGetWindowWidth() - HP_BOX_LENGTH - (2 * LINE_WIDTH) - EDGE_PADDING - 2, ofGetWindowHeight() - (2 * LINE_WIDTH) - HP_BOX_HEIGHT - EDGE_PADDING - 2, 0), HP_BOX_LENGTH + (2 * LINE_WIDTH) + 2, HP_BOX_HEIGHT + (2 * LINE_WIDTH) + 2);
		ofFill();
		break;
	case over:
		newGame->draw();
		gameOverReturn->draw();
		ofSetColor(0, 0, 0, 100);
		ofDrawRectangle(newGame->trans.x - newGame->width/2, ofGetWindowHeight()/4, newGame->width + gameOverReturn->width + 40, ofGetWindowHeight()/4);
		ofSetColor(255);
		if (score == highScores[0]) rect = bigFont.getStringBoundingBox("New High Score!", 0, 0);
		else rect = bigFont.getStringBoundingBox("Game Over", 0, 0);
		if (score == highScores[0]) bigFont.drawString("New High Score!", ofGetWindowWidth() / 2 - rect.width / 2, ofGetWindowHeight() / 4 + bigFont.getLineHeight() + EDGE_PADDING);
		else bigFont.drawString("Game Over", ofGetWindowWidth() / 2 - rect.width / 2, ofGetWindowHeight()/4 + bigFont.getLineHeight() + EDGE_PADDING);
		sprintf(finalScore, "Score :	% 010d", score);
		rect = silkscreen.getStringBoundingBox(finalScore, 0, 0);
		silkscreen.drawString(finalScore, ofGetWindowWidth() / 2 - rect.width / 2, ofGetWindowHeight()/4 + bigFont.getLineHeight() + silkscreen.getLineHeight() + 6*EDGE_PADDING);
		break;
	}
	
}

void ofApp::gameOver() {
	turret->stop();
	for (int i = 0; i < spawns.size(); i++) spawns[i]->stop();
	playerDeath->setPosition(player->position);
	playerDeath->emit();	// emit the player's giant particle explosion upon death
	player->position = (ofVec3f(ofGetWindowWidth() / 2, ofGetWindowHeight()/3*2, 0));	// return to starting point
	vector<int>::iterator iter = highScores.begin();
	while (iter != highScores.end()) {
		if (score > *iter) {
			highScores.insert(iter, score);		// I always cringe at using insertion sort, but since it's only done once every several minutes on a very short array, I think it's fine.
			highScores.pop_back();				// limit the array to 10 members
			iter = highScores.end() - 1;		// break out of the loop since we just added the high score
		}
		iter++;
	}
	currentScreen = over;
}

void ofApp::initGame() {
	turret->side = 1;
	turret->start();

	player->repair(10);

	spawns.clear();

	// re-create the enemy spawners here so that we can have a different number of emitters based on the player's difficulty settings
	for (int i = 0; i < numSpawners; i++)
	{
		EnemyEmitter *enemy = new EnemyEmitter(enemies);
		enemy->motion = ofRandom(-ofGetWindowWidth()/4, ofGetWindowWidth()/4);
		enemy->setChildImage(enemyImages[i % 2]);				// alternate between enemy sprite 1 and 2...
		if ((i % 2)) enemy->setSpriteSheet(enemy2Sprites, 4);	// and between sprite sheets.
		else enemy->setSpriteSheet(enemy1Sprites, 4);
		enemy->setPosition(ofVec3f(ofRandom(0, ofGetWindowWidth()), 0 - enemy->childImage.getHeight(), 0));
		enemy->setRate(ofRandom(spawnRate - 0.3, spawnRate + 0.3));
		enemy->lastSpawned = ofGetElapsedTimeMillis() + (800 * i);
		enemy->setVelocity(enemyVelocity);
		enemy->setLifespan(6000);
		enemy->height = enemy->childImage.getHeight();
		enemy->width = enemy->childImage.getWidth();
		enemy->spriteHealth = (i % 2) ? 4 : 2;			// Black planes have double the health of grey planes.
		enemy->spritePointValue = (i % 2) ? 40 : 20;	// Enemies give their hp total * 10 points upon  being killed.
		enemy->start();
		spawns.push_back(enemy);
	}

	score = 0; 

	healthBoxLength = HP_BOX_LENGTH;

	player->damage();	// Give the player a flashing effect while spawning
	player->repair(1);
}

//--------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	mousePos = ofVec3f(x, y, 0);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	switch (currentScreen) {
		// check if the player is mouseing over the various buttons, so that they can highlight themselves if so
	case menu:
		if (startGame->inside(ofVec3f(x, y, 0))) startGame->click();
		else if (difficultyOptions->inside(ofVec3f(x, y, 0))) difficultyOptions->click();
		else if (viewScores->inside(ofVec3f(x, y, 0))) viewScores->click();
		break;
	case difficulty:
		if (numEnemySpawnersButton->inside(ofVec3f(x, y, 0))) numEnemySpawnersButton->click();
		else if (spawnRateButton->inside(ofVec3f(x, y, 0))) spawnRateButton->click();
		else if (enemyVelocityButton->inside(ofVec3f(x, y, 0))) enemyVelocityButton->click();
		else if (enemyFlightIrregularityButton->inside(ofVec3f(x, y, 0))) enemyFlightIrregularityButton->click();
		else if (playerFireRateButton->inside(ofVec3f(x, y, 0))) playerFireRateButton->click();
		else if (difficultyReturn->inside(ofVec3f(x, y, 0))) difficultyReturn->click();
		break;
	case scores:
		if (scoresReturn->inside(ofVec3f(x, y, 0))) scoresReturn->click();
		break;
	case over:
		if (newGame->inside(ofVec3f(x, y, 0))) newGame->click();
		else if (gameOverReturn->inside(ofVec3f(x, y, 0))) gameOverReturn->click();
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	switch (currentScreen) {
		// The next ~150 lines all just control the results of clicking all the different 
		// buttons, and check to see if they have been clicked.
		//

	case menu:
		if (startGame->inside(ofVec3f(x, y, 0)) && startGame->clicked) currentScreen = startGame->unclick();
		else {
			startGame->clicked = false;
			startGame->highlighted = false;
		}
		if (difficultyOptions->inside(ofVec3f(x, y, 0)) && difficultyOptions->clicked) currentScreen = difficultyOptions->unclick();
		else {
			difficultyOptions->clicked = false;
			difficultyOptions->highlighted = false;
		}
		if (viewScores->inside(ofVec3f(x, y, 0)) && viewScores->clicked) currentScreen = viewScores->unclick();
		else {
			viewScores->clicked = false;
			viewScores->highlighted = false;
		}
		break;
	case difficulty:
		if (numEnemySpawnersButton->inside(ofVec3f(x, y, 0)) && numEnemySpawnersButton->clicked) {
			numEnemySpawnersButton->unclick();
			if (numEnemySpawnersButton->options[numEnemySpawnersButton->currentOption] == "Low") {
				numSpawners = 2;
				scoreMultiplier -= 0.6;
			}
			else if (numEnemySpawnersButton->options[numEnemySpawnersButton->currentOption] == "Medium") {
				numSpawners = 3;
				scoreMultiplier += 0.2;
			}
			else if (numEnemySpawnersButton->options[numEnemySpawnersButton->currentOption] == "High") {
				numSpawners = 4;
				scoreMultiplier += 0.2;
			}
			else if (numEnemySpawnersButton->options[numEnemySpawnersButton->currentOption] == "Inhuman") {
				numSpawners = 6;
				scoreMultiplier += 0.2;
			}
		}
		else {
			numEnemySpawnersButton->clicked = false;
			numEnemySpawnersButton->highlighted = false;
		}
		if (spawnRateButton->inside(ofVec3f(x, y, 0)) && spawnRateButton->clicked) {
			spawnRateButton->unclick();
			if (spawnRateButton->options[spawnRateButton->currentOption] == "Low") {
				spawnRate = 0.3;
				scoreMultiplier -= 0.6;
			}
			else if (spawnRateButton->options[spawnRateButton->currentOption] == "Medium") {
				spawnRate = 0.4;
				scoreMultiplier += 0.2;
			}
			else if (spawnRateButton->options[spawnRateButton->currentOption] == "High") {
				spawnRate = 0.6;
				scoreMultiplier += 0.2;
			}
			else if (spawnRateButton->options[spawnRateButton->currentOption] == "Overwhelming") {
				spawnRate = 0.8;
				scoreMultiplier += 0.2;
			}
		}
		else {
			spawnRateButton->clicked = false;
			spawnRateButton->highlighted = false;
		}
		if (enemyVelocityButton->inside(ofVec3f(x, y, 0)) && enemyVelocityButton->clicked) {
			enemyVelocityButton->unclick();
			if (enemyVelocityButton->options[enemyVelocityButton->currentOption] == "Slow") {
				enemyVelocity.y = 400;
				scoreMultiplier -= 0.6;
			}
			else if (enemyVelocityButton->options[enemyVelocityButton->currentOption] == "Medium") {
				enemyVelocity.y = 450;
				scoreMultiplier += 0.2;
			}
			else if (enemyVelocityButton->options[enemyVelocityButton->currentOption] == "Fast") {
				enemyVelocity.y = 600;
				scoreMultiplier += 0.2;
			}
			else if (enemyVelocityButton->options[enemyVelocityButton->currentOption] == "Turbo") {
				enemyVelocity.y = 750;
				scoreMultiplier += 0.2;
			}
		}
		else {
			enemyVelocityButton->clicked = false;
			enemyVelocityButton->highlighted = false;
		}
		if (enemyFlightIrregularityButton->inside(ofVec3f(x, y, 0)) && enemyFlightIrregularityButton->clicked) {
			enemyFlightIrregularityButton->unclick();
			if (enemyFlightIrregularityButton->options[enemyFlightIrregularityButton->currentOption] == "Low") {
				irregularityScale = 0.2;
				scoreMultiplier -= 0.6;
			}
			else if (enemyFlightIrregularityButton->options[enemyFlightIrregularityButton->currentOption] == "Medium") {
				irregularityScale = 0.4;
				scoreMultiplier += 0.2;
			}
			else if (enemyFlightIrregularityButton->options[enemyFlightIrregularityButton->currentOption] == "High") {
				irregularityScale = 0.75;
				scoreMultiplier += 0.2;
			}
			else if (enemyFlightIrregularityButton->options[enemyFlightIrregularityButton->currentOption] == "Crazy") {
				irregularityScale = 1;
				scoreMultiplier += 0.2;
			}
		}
		else {
			enemyFlightIrregularityButton->clicked = false;
			enemyFlightIrregularityButton->highlighted = false;
		}
		if (playerFireRateButton->inside(ofVec3f(x, y, 0)) && playerFireRateButton->clicked) {
			playerFireRateButton->unclick();
			if (playerFireRateButton->options[playerFireRateButton->currentOption] == "Low") {
				turret->setRate(3);
				scoreMultiplier += 0.4;
			}
			else if (playerFireRateButton->options[playerFireRateButton->currentOption] == "Medium") {
				turret->setRate(4);
				scoreMultiplier -= 0.2;
			}
			else if (playerFireRateButton->options[playerFireRateButton->currentOption] == "High") {
				turret->setRate(5);
				scoreMultiplier -= 0.1;
			}
			else if (playerFireRateButton->options[playerFireRateButton->currentOption] == "Super High") {
				turret->setRate(8);
				scoreMultiplier -= 0.1;
			}
		}
		else {
			playerFireRateButton->clicked = false;
			playerFireRateButton->highlighted = false;
		}
		if (difficultyReturn->inside(ofVec3f(x, y, 0)) && difficultyReturn->clicked) currentScreen = difficultyReturn->unclick();
		else {
			difficultyReturn->clicked = false;
			difficultyReturn->highlighted = false;
		}
		break;
		case scores:
			if (scoresReturn->inside(ofVec3f(x, y, 0)) && scoresReturn->clicked) currentScreen = scoresReturn->unclick();
			else {
				scoresReturn->clicked = false;
				scoresReturn->highlighted = false;
			}
			break;
		case over:
			if (newGame->inside(ofVec3f(x, y, 0)) && newGame->clicked) currentScreen = newGame->unclick();
			else {
				newGame->clicked = false;
				newGame->highlighted = false;
			}
			if (gameOverReturn->inside(ofVec3f(x, y, 0)) && gameOverReturn->clicked) currentScreen = gameOverReturn->unclick();
			else {
				gameOverReturn->clicked = false;
				gameOverReturn->highlighted = false;
			}
			break;

	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

void ofApp::keyPressed(int key) {
	switch (key) {
	case 'C':
	case 'c':
		break;
	case 'F':
	case 'f':
		ofToggleFullscreen();
		break;
	case 'H':
	case 'h':
		break;
	case 'r':
		break;
	case 'u':
		break;
	case ' ':
		turret->bShooting = true;
		break;
	case 'w':						// =================
		bForward = true;			// wasd controls
		break;						//
	case 's':						//
		bBack = true;				//
		break;						// 
	case 'a':						//
		bLeft = true;				//
		break;						//
	case 'd':						//
		bRight = true;				// =================
		break;						
	case OF_KEY_UP:					// =================
		bForward = true;			// arrow keys controls
		break;						//
	case OF_KEY_DOWN:				//
		bBack = true;				//
		break;						//
	case OF_KEY_LEFT:				//
		bLeft = true;				//
		break;						//
	case OF_KEY_RIGHT:				//
		bRight = true;				// =================
		break;						
	case OF_KEY_ALT:
		break;
	case OF_KEY_CONTROL:
		break;
	case OF_KEY_SHIFT:
		break;
	case OF_KEY_DEL:
		break;
	}
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key) {
	case ' ':
		turret->bShooting = false;	// =================
		break;						// wasd release controls
	case 'w':						//
		bForward = false;			//
		break;						//
	case 's':						//
		bBack = false;				//
		break;						//
	case 'a':						//
		bLeft = false;				//
		break;						//
	case 'd':						//
		bRight = false;				// =================
		break;						
	case OF_KEY_UP:					// =================
		bForward = false;			// arrow keys release
		break;						// controls
	case OF_KEY_DOWN:				//
		bBack = false;				//
		break;						//
	case OF_KEY_LEFT:				//
		bLeft = false;				//
		break;						//
	case OF_KEY_RIGHT:				//
		bRight = false;				//
		break;						// =================
	case OF_KEY_ALT:
		break;
	case OF_KEY_CONTROL:
		break;
	case OF_KEY_SHIFT:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

