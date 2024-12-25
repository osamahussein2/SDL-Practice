#pragma once

#include <iostream>
#include <string>
#include <map>
#include "GameObject.h"

using namespace std;

class BaseCreator
{
public:

	virtual GameObject* CreateGameObject() const = 0;
	virtual ~BaseCreator() {};
};

class GameObjectFactory
{
public:

	static GameObjectFactory* Instance()
	{
		if (gameObjectFactoryInstance == 0)
		{
			gameObjectFactoryInstance = new GameObjectFactory();
		}

		return gameObjectFactoryInstance;
	}

	bool RegisterType(string typeID_, BaseCreator* baseCreator_)
	{
		// Find the object type using the std::mapfind function
		map<string, BaseCreator*>::iterator it = baseCreator.find(typeID_);

		// If the type is found, then it is already registered
		if (it != baseCreator.end())
		{
			// Delete the passed in pointer and return false
			delete baseCreator_;
			return false;
		}

		// If the type is not already registered, then it can be assigned to the map and then true is returned
		baseCreator[typeID_] = baseCreator_;
		return true;
	}

	GameObject* Create(string typeID_)
	{
		// Find the object type using the std::mapfind function
		map<string, BaseCreator*>::iterator it = baseCreator.find(typeID_);

		// If the type is not found, return NULL and print to the console that it couldn't find the type
		if (it == baseCreator.end())
		{
			cout << "Couldn't find type: " << typeID_ << endl;
			return NULL;
		}

		/* If the type is found, then we use the Creator object for that type to return a new instance of it as a 
		pointer to GameObject */
		BaseCreator* baseCreator_ = (*it).second;
		return baseCreator_->CreateGameObject();
	}

private:

	GameObjectFactory() {}
	~GameObjectFactory() {}

	/* This map holds the important elements of our factory, the functions of the class essentially either add or remove
	from this map. */
	map<string, BaseCreator*> baseCreator;

	static GameObjectFactory* gameObjectFactoryInstance;
};

typedef GameObjectFactory TheGameObjectFactory;