#include "ShooterObject.h"
#include "TextureManager.h"
#include "Window.h"

typedef Window TheWindow;

ShooterObject::ShooterObject() : GameObject(), bulletFiringSpeed(0), bulletCounter(0), moveSpeed(0), dyingTime(0),
dyingCounter(0), playedDeathSound(false)
{

}

void ShooterObject::Draw()
{
	if (velocity.GetX() > 0)
	{
		TextureManager::TextureManagerInstance()->DrawFrame(textureID,
			position.GetX(), position.GetY(),
			width, height, currentRow, currentFrame,
			TheWindow::WindowInstance()->GetRenderer(), angle, alpha, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		TextureManager::TextureManagerInstance()->DrawFrame(textureID,
			position.GetX(), position.GetY(),
			width, height, currentRow, currentFrame,
			TheWindow::WindowInstance()->GetRenderer(), angle, alpha, SDL_FLIP_NONE);
	}
}

void ShooterObject::Update()
{
	velocity += acceleration;
	position += velocity;
}

void ShooterObject::LoadGameObject(unique_ptr<LoaderParams> const &loaderParams_)
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

void ShooterObject::DoDyingAnimation()
{
	// Keep scrolling with the map
	Scroll(TheWindow::WindowInstance()->GetScrollSpeed());

	currentFrame = static_cast<int>(((SDL_GetTicks() / (1000 / 3)) % numberOfFrames));

	if (dyingCounter == dyingTime)
	{
		isDead = true;
	}

	dyingCounter++;
}