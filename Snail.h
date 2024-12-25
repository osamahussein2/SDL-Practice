#pragma once

#include "Enemy.h"
#include "GameObjectFactory.h"
#include "Camera.h"
#include "TileLayer.h"
#include <iostream>

class Snail : public Enemy
{
public:
	Snail() : Enemy()
	{
		moveLeft = true;
	}

    virtual void Update()
    {
        if (moveLeft)
        {
            velocity.x = -2;
        }
        else if (moveRight)
        {
            velocity.x = 2;
        }
        else
        {
            velocity.x = 0;
        }

        velocity.y = 5;

        HandleMovement(velocity);
        HandleAnimation();
    }

    virtual void LoadGameObject(unique_ptr<LoaderParams> const& loaderParams_)
    {
        PlatformerObject::LoadGameObject(move(loaderParams_));
    }

    virtual void Draw()
    {
        if (flipped)
        {
            TextureManager::TextureManagerInstance()->DrawFrame(textureID, 
                (Uint32)position.GetX() - TheCamera::CameraInstance()->GetPosition().x, 
                (Uint32)position.GetY() - TheCamera::CameraInstance()->GetPosition().y,
                width, height, currentRow, currentFrame, TheWindow::WindowInstance()->GetRenderer(), angle, alpha, 
                SDL_FLIP_HORIZONTAL);
        }

        else
        {
            TextureManager::TextureManagerInstance()->DrawFrame(textureID, 
                (Uint32)position.GetX() - TheCamera::CameraInstance()->GetPosition().x, 
                (Uint32)position.GetY() - TheCamera::CameraInstance()->GetPosition().y,
                width, height, currentRow, currentFrame, TheWindow::WindowInstance()->GetRenderer(), angle, alpha,
                SDL_FLIP_NONE);
        }
    }

private:

    void HandleMovement(Vector2 velocity)
    {
        Vector2 newPos = position;
        newPos.x = position.x + velocity.x;

        if (!CheckCollideTile(newPos))
        {
            position.x = newPos.x;
        }

        else
        {
            if (moveLeft)
            {
                moveLeft = false;
                moveRight = true;
            }

            else if (moveRight)
            {
                moveLeft = true;
                moveRight = false;
            }
        }

        newPos = position;
        newPos.y += velocity.y;

        if (!CheckCollideTile(newPos))
        {
            if (velocity.y == 0)
            {
                if (moveLeft)
                {
                    moveLeft = false;
                    moveRight = true;
                }

                else if (moveRight)
                {
                    moveLeft = true;
                    moveRight = false;
                }
            }

            position.y = newPos.y;
        }

        else
        {
            velocity.y = 0;
        }
    }

    void HandleAnimation()
    {

        if (velocity.GetX() < 0)
        {
            flipped = true;
        }

        else if (velocity.GetX() > 0)
        {
            flipped = false;
        }

        else
        {
            currentRow = 0;
            numberOfFrames = 1;
        }

        currentFrame = int(((SDL_GetTicks() / (100)) % numberOfFrames));
    }

    bool moveLeft;
    bool moveRight;
    bool flipped;
};

class SnailCreator : public BaseCreator
{
    GameObject* CreateGameObject() const
    {
        return new Snail();
    }
};