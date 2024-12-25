#pragma once

#include <iostream>
#include <vector>
#include "tinyxml.h"

class GameObject;

using namespace std;

class StateParser
{
public:
	StateParser() {}
	~StateParser() {}

	bool ParseState(const char* stateFile_, string stateID_, vector<GameObject*> *gameObjects_, vector<string>* textureIDs_);

private:
	void ParseObjects(TiXmlElement* stateRoot_, vector<GameObject*> *gameObjects_);
	void ParseTextures(TiXmlElement* stateRoot_, vector<string> *textureIDs_);
};