#pragma once

#include "ofMain.h"
#include "BaseObject.h"

typedef enum { game, menu, difficulty, scores, over, starting } Screen;

// A class that represents a button for the UI by storing x and y values (the center of the button), and 
// the width and height. The default button functionality is to redirect the user to a different screen.
//

class Button : public BaseObject {
public:
	Button();
	Button(ofVec3f);
	void draw();
	void click();
	Screen unclick();
	bool inside(ofVec3f);

	void setText(string s) { text = s; }
	void setWidth(float w) { width = w; }
	void setHeight(float h) { height = h; }
	void setColor(ofColor c) { color = c; }
	void setScreen(Screen scr) { screen = scr; }
	void setPosition(float x, float y) { trans.x = x; trans.y = y; }

	float width, height;
	string text;
	bool highlighted, clicked;
	ofColor color, edge;
	ofTrueTypeFont font;
	Screen screen;
};

// A subclass of the Button class that, rather than sending you to a new screen, cycles
// through preset options. Used for the difficulty screen.
//

class OptionButton : public Button {
public:
	OptionButton(ofVec3f);
	void draw();
	void unclick();

	void addOption(string);

	int currentOption;
	vector<string> options;
};