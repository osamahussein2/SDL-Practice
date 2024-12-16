#include "SDLGameObject.h"

SDLGameObject::SDLGameObject(const LoaderParams* loaderParams_) : GameObject(loaderParams_),
position(loaderParams_->GetX(), loaderParams_->GetY()), velocity(0, 0), acceleration(0, 0)
{
	width = loaderParams_->GetWidth();
	height = loaderParams_->GetHeight();
	textureID = loaderParams_->GetTextureID();

	currentRow = 0;
	currentFrame = 1;
}

void SDLGameObject::Draw()
{
	TextureManager::TextureManagerInstance()->DrawFrame(textureID, (int)position.GetX(), (int)position.GetY(), 
		width, height, currentRow, currentFrame, Window::WindowInstance()->GetRenderer(), SDL_FLIP_NONE);
}

void SDLGameObject::Update()
{
	velocity += acceleration;
	position += velocity;
}

void SDLGameObject::Clean()
{
}
