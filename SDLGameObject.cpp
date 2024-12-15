#include "SDLGameObject.h"

SDLGameObject::SDLGameObject(const LoaderParams* loaderParams_) : GameObject(loaderParams_)
{
	x = loaderParams_->GetX();
	y = loaderParams_->GetY();
	width = loaderParams_->GetWidth();
	height = loaderParams_->GetHeight();
	textureID = loaderParams_->GetTextureID();

	currentRow = 0;
	currentFrame = 1;
}

void SDLGameObject::Draw()
{
	TextureManager::TextureManagerInstance()->DrawFrame(textureID, x, y, width, height, currentRow, currentFrame,
		Window::WindowInstance()->GetRenderer(), SDL_FLIP_NONE);
}

void SDLGameObject::Update()
{
}

void SDLGameObject::Clean()
{
}
