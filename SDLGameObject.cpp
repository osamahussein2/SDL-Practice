#include "SDLGameObject.h"

SDLGameObject::SDLGameObject() : GameObject(), position(0, 0), velocity(0, 0), acceleration(0, 0)
{

}

void SDLGameObject::Draw()
{
	if (velocity.GetX() > 0)
	{
		TextureManager::TextureManagerInstance()->DrawFrame(textureID,
			position.GetX(), position.GetY(),
			width, height, currentRow, currentFrame,
			Window::WindowInstance()->GetRenderer(), SDL_FLIP_HORIZONTAL);
	}
	else
	{
		TextureManager::TextureManagerInstance()->DrawFrame(textureID,
			position.GetX(), position.GetY(),
			width, height, currentRow, currentFrame,
			Window::WindowInstance()->GetRenderer(), SDL_FLIP_NONE);
	}
}

void SDLGameObject::Update()
{
	velocity += acceleration;
	position += velocity;
}

void SDLGameObject::Clean()
{
}

void SDLGameObject::LoadGameObject(const LoaderParams* loaderParams_)
{
	position = Vector2(loaderParams_->GetX(), loaderParams_->GetY());
	velocity = Vector2(0, 0);
	acceleration = Vector2(0, 0);

	width = loaderParams_->GetWidth();
	height = loaderParams_->GetHeight();
	textureID = loaderParams_->GetTextureID();

	currentRow = 0;
	currentFrame = 1;
}
