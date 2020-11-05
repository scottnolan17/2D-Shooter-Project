
#include "Button.h"

// See Button.h for explanation of the button class
//


// Declaring a button with no given vector: default to (0,0) and being wide and thin in shape.
Button::Button() {
	trans = ofVec3f(0);
	width = ofGetWindowWidth() / 3;
	height = ofGetWindowHeight() / 18;
	text = "New Button";
	highlighted = clicked = false;
	color = ofColor(0);
	edge = ofColor(255);

	if (!font.load("slkscr.ttf", ofGetWindowHeight() / 30)) {
		ofLogFatalError("can't load font: slkscr.ttf");
		ofExit();
	}
	font.setLetterSpacing(0.8);
}

// Declare a button centered at the given vector. Same default shape as above.
Button::Button(ofVec3f pos) {
	trans = pos;
	width = ofGetWindowWidth() / 3;
	height = ofGetWindowHeight() / 18;
	text = "New Button";
	highlighted = clicked = false;
	color = ofColor(0, 0, 0, 100);
	edge = ofColor(255);

	if (!font.load("slkscr.ttf", ofGetWindowHeight() / 30)) {
		ofLogFatalError("can't load font: slkscr.ttf");
		ofExit();
	}
	font.setLetterSpacing(0.8);
}


void Button::draw() {
	ofSetColor(color);
	if (highlighted) ofSetColor(100, 100, 100, 100);
	if (clicked) ofSetColor(200, 200, 200, 100);
	ofDrawRectangle(trans.x - width / 2, trans.y - height / 2, width, height);
	ofSetColor(edge);
	ofNoFill();
	ofDrawRectangle(trans.x - width / 2, trans.y - height / 2, width, height);
	ofFill();
	ofRectangle rect = font.getStringBoundingBox(text, 0, 0);
	font.drawString(text, trans.x - rect.width/2 , trans.y+rect.height/2);
	ofSetColor(255);
}

void Button::click() {
	clicked = true;
}

// This passes uo the button's stored screen transition, so that the effect occurs when the user releases the button.
Screen Button::unclick() {
	clicked = false;
	if (highlighted) return screen;
}

// Returns true if the given vector (generally the mouse pointer) is inside this button's bounds.
// Also highlights the button if true.
bool Button::inside(ofVec3f pos) {
	highlighted = (trans.x - width/2 <= pos.x &&
		pos.x <= trans.x + width/2 &&
		trans.y - height/2 <= pos.y &&
		pos.y <= trans.y + height/2);
	return highlighted;
}


// A specialized btton for the options menu
OptionButton::OptionButton(ofVec3f pos) {
	trans = pos;
	width = ofGetWindowWidth() / 3;
	height = ofGetWindowHeight() / 18;
	text = "New Button";
	highlighted = clicked = false;
	color = ofColor(0, 0, 0, 100);
	edge = ofColor(255);

	if (!font.load("slkscr.ttf", ofGetWindowHeight() / 30)) {
		ofLogFatalError("can't load font: slkscr.ttf");
		ofExit();
	}
	font.setLetterSpacing(0.8);
}

void OptionButton::draw() {
	ofSetColor(color);
	if (highlighted) ofSetColor(100, 100, 100, 100);
	if (clicked) ofSetColor(200, 200, 200, 100);
	ofDrawRectangle(trans.x - width / 2, trans.y - height / 2, width, height);
	ofSetColor(edge);
	ofNoFill();
	ofDrawRectangle(trans.x - width / 2, trans.y - height / 2, width, height);
	ofFill();
	ofRectangle rect = font.getStringBoundingBox(text + options[currentOption], 0, 0);
	font.drawString(text + options[currentOption], trans.x - rect.width / 2, trans.y + rect.height / 2);
	ofSetColor(255);
}

// Similar functionality as the base Button, but just cycles the string displayed on the button and returns nothing.
void OptionButton::unclick() {
	clicked = false;
	if (highlighted) {
		if (currentOption < options.size() - 1) currentOption++;
		else currentOption = 0;
	}
}

// Adds a new string that will enter the button's rotation.
void OptionButton::addOption(string s) {
	options.push_back(s);
	if (options.size() == 1) currentOption = 0;
}