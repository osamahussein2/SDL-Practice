#include "StateParser.h"
#include "TextureManager.h"
#include "Window.h"
#include "GameObjectFactory.h"

typedef TextureManager TheTextureManager;
typedef Window TheWindow;
typedef GameObjectFactory TheGameObjectFactory;

bool StateParser::ParseState(const char* stateFile_, string stateID_, vector<GameObject*> *gameObjects_, 
	vector<string>* textureIDs_)
{
	// Create the XML document object
	TiXmlDocument xmlDoc;

	// Load the state file
	if (!xmlDoc.LoadFile(stateFile_))
	{
		cerr << xmlDoc.ErrorDesc() << endl;
		return false;
	}

	// Get the root element
	TiXmlElement* root = xmlDoc.RootElement();

	// Pre declare the states root node
	TiXmlElement* stateRoot = 0;

	// Get the states root node and assign it to the state root
	for (TiXmlElement* element = root->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		if (element->Value() == stateID_)
		{
			stateRoot = element;
		}
	}

	// Pre declare the texture root
	TiXmlElement* textureRoot = 0;

	// Get the root of the texture elements
	for (TiXmlElement* element = stateRoot->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		if (element->Value() == string("TEXTURES"))
		{
			textureRoot = element;
		}
	}

	// Parse the textures
	ParseTextures(textureRoot, textureIDs_);

	// Pre declare the object root node
	TiXmlElement* objectRoot = 0;

	// Get the root node and assign it to the object root
	for (TiXmlElement* element = stateRoot->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		if (element->Value() == string("OBJECTS"))
		{
			objectRoot = element;
		}
	}

	// Parse the objects
	ParseObjects(objectRoot, gameObjects_);

	return true;
}

void StateParser::ParseObjects(TiXmlElement* stateRoot_, vector<GameObject*> *gameObjects_)
{
	for (TiXmlElement* element = stateRoot_->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		int x, y, width, height, numberOfFrames, callbackID, animationSpeed;
		string textureID;

		// Get the all the values from the current node
		element->Attribute("x", &x);
		element->Attribute("y", &y);
		element->Attribute("width", &width);
		element->Attribute("height", &height);
		element->Attribute("numFrames", &numberOfFrames);
		element->Attribute("callbackID", &callbackID);
		element->Attribute("animSpeed", &animationSpeed);
		
		textureID = element->Attribute("textureID");

		// Pass in the value from the type attribute and use that to create the correct object from the factory
		GameObject* gameObject = TheGameObjectFactory::Instance()->Create(element->Attribute("type"));
		gameObject->LoadGameObject(unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID,
			numberOfFrames, callbackID, animationSpeed)));

		// Push the local game object into the array of game objects passed into the parameter
		gameObjects_->push_back(gameObject);
	}
}

void StateParser::ParseTextures(TiXmlElement* stateRoot_, vector<string>* textureIDs_)
{
	for (TiXmlElement* element = stateRoot_->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		// Get the filename and ID attributes from each of the texture values in a part of the XML file
		string filenameAttribute = element->Attribute("filename");
		string idAttribute = element->Attribute("ID");

		textureIDs_->push_back(idAttribute); // Push ID attribute into a list of texture IDs

		// Add the filename and ID attributes to the texture manager to load our textures
		TheTextureManager::TextureManagerInstance()->LoadTexture(filenameAttribute, idAttribute,
			TheWindow::WindowInstance()->GetRenderer());
	}
}
