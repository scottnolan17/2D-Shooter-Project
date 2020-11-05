#pragma once

#include "ofMain.h"
#include "ofxGui.h"

// This is a base object that all drawable object inherit from
// It is possible this will be replaced by ofNode when we move to 3D
//
class BaseObject {
public:
	BaseObject();
	ofVec2f trans, scale;
	float	rot;
	bool	bSelected;
	void setPosition(ofVec3f);
};
