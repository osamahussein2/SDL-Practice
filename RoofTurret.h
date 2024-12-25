#pragma once

#include "Turret.h"

class RoofTurret : public Turret
{
public:
	virtual ~RoofTurret() {}

	virtual void Draw()
	{
		TextureManager::TextureManagerInstance()->DrawFrame(textureID, (Uint32)position.GetX(), 
			(Uint32)position.GetY(), width, height, currentRow, currentFrame, TheWindow::WindowInstance()->GetRenderer(), 
			angle, alpha, SDL_FLIP_VERTICAL);
	}

	virtual void Update()
	{
        if (!isDying)
        {
            // we want to scroll this object with the rest
            Scroll(TheWindow::WindowInstance()->GetScrollSpeed());

            if (bulletCounter == bulletFiringSpeed)
            {
                TheBulletHandler::Instance()->AddEnemyBullet(position.GetX(), position.GetY() + 20, 16, 16,
                    "bullet2", 1, Vector2(-3, 3));
                TheBulletHandler::Instance()->AddEnemyBullet(position.GetX() + 20, position.GetY() + 20, 16, 16,
                    "bullet2", 1, Vector2(0, 3));
                TheBulletHandler::Instance()->AddEnemyBullet(position.GetX() + 40, position.GetY() + 20, 16, 16,
                    "bullet2", 1, Vector2(3, 3));
                
                bulletCounter = 0;
            }

            bulletCounter++;
        }
        else
        {
            Scroll(TheWindow::WindowInstance()->GetScrollSpeed());
            DoDyingAnimation();
        }
    }
};

class RoofTurretCreator : public BaseCreator
{
    GameObject* CreateGameObject() const
    {
        return new RoofTurret();
    }
};