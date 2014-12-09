#include <entities/projectile.h>
#include <utils.h>

#include <iostream>

Projectile::Projectile(Type type, Direction dir, TextureHolder &textures) :
    Entity(type),
    mAnimationOffset(0.f, 0.f),
    mState(Resting)
{
    if(type == RabbitBullet)
    {
        switch(dir)
        {
            case Right:
                mSprite.setTexture(textures.get(Textures::CarrotProjectile));
                mSprite.setTextureRect(sf::IntRect(0, 0, 15, 15));
                mSprite.setOrigin(sf::Vector2f(-60.f, 15.f));
                break;

            case Down:
                mSprite.setTexture(textures.get(Textures::CarrotProjectile));
                mSprite.setTextureRect(sf::IntRect(15, 0, 15, 15));
                mSprite.setOrigin(sf::Vector2f(-30.f, 15.f));
                break;

            case Left:
                mSprite.setTexture(textures.get(Textures::CarrotProjectile));
                mSprite.setTextureRect(sf::IntRect(30, 0, 15, 15));
                mSprite.setOrigin(sf::Vector2f(-30.f, 20.f));
                break;

            case Up:
                mSprite.setTexture(textures.get(Textures::CarrotProjectile));
                mSprite.setTextureRect(sf::IntRect(45, 0, 15, 15));
                mSprite.setOrigin(sf::Vector2f(-60.f, 15.f));
                break;
        }
        mSpeed = 0.15f;
    }
    else
    {

    }

    mDirection = dir;
}


void Projectile::updateCurrent(sf::Time dt, CommandQueue &commands)
{
    if(isDestroyed())
    {
        return;
    }

    if(mState == Walking)
    {
        switch(mDirection)
        {
            case Up:
            {
                sf::Vector2f mov(1.f, -1.f);
                mAnimationOffset += sf::Vector2f(
                            (dt.asSeconds() / mSpeed) *
                            sf::Vector2f(60.f * mov.x, 30.f * mov.y)
                );

                if(mAnimationOffset.x >= 60.f * mov.x && mAnimationOffset.y <= 30.f * mov.y)
                {
                    mState = Resting;
                    mAnimationOffset = sf::Vector2f(0.f, 0.f);
                    mOldGridPosition = mGridPosition;
                    setPosition(toIsoCoord(mOldGridPosition.x, mOldGridPosition.y));
                    move(Up, mGridPosition + sf::Vector2i(0, -1));
                }
            }
            break;

            case Down:
            {
                sf::Vector2f mov(-1.f, 1.f);
                mAnimationOffset += sf::Vector2f(
                            (dt.asSeconds() / mSpeed) *
                            sf::Vector2f(60.f * mov.x, 30.f * mov.y)
                );

                if(mAnimationOffset.x <= 60.f * mov.x && mAnimationOffset.y >= 30.f * mov.y)
                {
                    mState = Resting;
                    mAnimationOffset = sf::Vector2f(0.f, 0.f);
                    mOldGridPosition = mGridPosition;
                    setPosition(toIsoCoord(mOldGridPosition.x, mOldGridPosition.y));
                    move(Down, mGridPosition + sf::Vector2i(0, 1));
                }
            }
            break;

            case Right:
            {
                sf::Vector2f mov(1.f, 1.f);
                mAnimationOffset += sf::Vector2f(
                            (dt.asSeconds() / mSpeed) *
                            sf::Vector2f(60.f * mov.x, 30.f * mov.y)
                );

                if(mAnimationOffset.x >= 60.f * mov.x && mAnimationOffset.y >= 30.f * mov.y)
                {
                    mState = Resting;
                    mAnimationOffset = sf::Vector2f(0.f, 0.f);
                    mOldGridPosition = mGridPosition;
                    setPosition(toIsoCoord(mOldGridPosition.x, mOldGridPosition.y));
                    move(Right, mGridPosition + sf::Vector2i(1, 0));
                }
            }
            break;

            case Left:
            {
                sf::Vector2f mov(-1.f, -1.f);
                mAnimationOffset += sf::Vector2f(
                            (dt.asSeconds() / mSpeed) *
                            sf::Vector2f(60.f * mov.x, 30.f * mov.y)
                );

                if(mAnimationOffset.x <= 60.f * mov.x && mAnimationOffset.y <= 30.f * mov.y)
                {
                    mState = Resting;
                    mAnimationOffset = sf::Vector2f(0.f, 0.f);
                    mOldGridPosition = mGridPosition;
                    setPosition(toIsoCoord(mOldGridPosition.x, mOldGridPosition.y));
                    move(Left, mGridPosition + sf::Vector2i(-1, 0));
                }
            }
            break;

            default:break;
        }
    }

    Entity::updateCurrent(dt, commands);
}


void Projectile::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform.translate(mAnimationOffset);

    if(isDestroyed())
        return;

    target.draw(mSprite, states);
}



void Projectile::move(Direction dir, sf::Vector2i whereTo)
{
    if(mState != Resting || isDestroyed()) {
        return;
    }

    if(whereTo.x > 7 || whereTo.y > 7 || whereTo.x < 0 || whereTo.y < 0)
    {
        destroy();
    }

    mDirection = dir;
    mGridPosition = whereTo;
    mState = Walking;
}

