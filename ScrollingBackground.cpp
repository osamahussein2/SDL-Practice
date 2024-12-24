#include "ScrollingBackground.h"
#include "Window.h"
#include "TextureManager.h"

typedef Window TheWindow;
typedef TextureManager TheTextureManager;

ScrollingBackground::ScrollingBackground() : ShooterObject()
{

}

void ScrollingBackground::Draw()
{
	// Draw first rectangle
	SDL_RenderCopyEx(TheWindow::WindowInstance()->GetRenderer(), 
		TheTextureManager::TextureManagerInstance()->GetTextureMap() [textureID],
		&srcRect1, &destRect1, 0, 0, SDL_FLIP_NONE);

	// Draw second rectangle
	SDL_RenderCopyEx(TheWindow::WindowInstance()->GetRenderer(),
		TheTextureManager::TextureManagerInstance()->GetTextureMap()[textureID],
		&srcRect2, &destRect2, 0, 0, SDL_FLIP_NONE);
}

void ScrollingBackground::Update()
{
	if (count == maxCount)
	{
		// Make first rectangle smaller
		srcRect1.x += scrollSpeed;
		srcRect1.w -= scrollSpeed;
		destRect1.w -= scrollSpeed;

		// Make second rectangle bigger
		srcRect2.w += scrollSpeed;
		destRect2.w += scrollSpeed;
		destRect2.x -= scrollSpeed;

		// Reset and start again
		if (destRect2.w >= width)
		{
			srcRect1.x = 0;
			destRect1.x = position.GetX();
			srcRect1.y = 0;
			destRect1.y = position.GetY();

			srcRect1.w = destRect1.w = srcRect2Width = destRect1Width = width;
			srcRect1.h = destRect1.h = height;

			srcRect2.x = 0;
			destRect2.x = position.GetX() + width;
			srcRect2.y = 0;
			destRect2.y = position.GetY();

			srcRect2.w = destRect2.w = srcRect2Width = destRect2Width = 0;
			srcRect2.h = destRect2.h = height;
		}
		
		count = 0;
	}

	count++;
}

void ScrollingBackground::LoadGameObject(unique_ptr<LoaderParams> const& loaderParams_)
{
	ShooterObject::LoadGameObject(move(loaderParams_));
	scrollSpeed = loaderParams_->GetAnimationSpeed();

	scrollSpeed = 1;

	srcRect1.x = 0;
	destRect1.x = position.GetX();
	srcRect1.y = 0;
	destRect1.y = position.GetY();

	srcRect1.w = destRect1.w = srcRect2Width = destRect1Width = width;
	srcRect1.h = destRect1.h = height;

	srcRect2.x = 0;
	destRect2.x = position.GetX() + width;
	srcRect2.y = 0;
	destRect2.y = position.GetY();

	srcRect2.w = destRect2.w = srcRect2Width = destRect2Width = 0;
	srcRect2.h = destRect2.h = height;
}

void ScrollingBackground::Clean()
{
}