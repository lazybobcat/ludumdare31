#include <entities/basickidnode.h>
#include <entities/playerentity.h>
#include <utils.h>

#include <iostream>

BasicKidNode::BasicKidNode(TextureHolder &textures, float speed) :
    Entity(Entity::Kid),
    mExistanceTimer(sf::Time::Zero),
    mTimer(sf::seconds(2.f)),
    mTimeToRelocate(sf::seconds(2.f)),
    mSprite(textures.get(Textures::KidRight), sf::IntRect(0, 0, 60, 80)),
    mRestingUpSprite(textures.get(Textures::KidUp), sf::IntRect(0, 0, 60, 80)),
    mRestingDownSprite(textures.get(Textures::KidDown), sf::IntRect(0, 0, 60, 80)),
    mRestingLeftSprite(textures.get(Textures::KidLeft), sf::IntRect(0, 0, 60, 80)),
    mRestingRightSprite(textures.get(Textures::KidRight), sf::IntRect(0, 0, 60, 80)),
    mState(Resting),
    mIntelligence(1)
{
    mSpeed = speed;

    // RESTING
    mSprite.setOrigin(sf::Vector2f(-30.f, 40.f));
    mRestingUpSprite.setOrigin(sf::Vector2f(-30.f, 40.f));
    mRestingDownSprite.setOrigin(sf::Vector2f(-30.f, 40.f));
    mRestingLeftSprite.setOrigin(sf::Vector2f(-30.f, 40.f));
    mRestingRightSprite.setOrigin(sf::Vector2f(-30.f, 40.f));


    // WALKING
    mWalkingAnimations[Entity::Right].setTexture(textures.get(Textures::KidRight));
    mWalkingAnimations[Entity::Right].setFrameSize(sf::Vector2i(60, 80));
    mWalkingAnimations[Entity::Right].setNumFrames(4);
    mWalkingAnimations[Entity::Right].setDuration(sf::seconds(0.9f));
    mWalkingAnimations[Entity::Right].setRepeating(true);
    mWalkingAnimations[Entity::Right].setOrigin(sf::Vector2f(-30.f, 40.f));

    mWalkingAnimations[Entity::Left].setTexture(textures.get(Textures::KidLeft));
    mWalkingAnimations[Entity::Left].setFrameSize(sf::Vector2i(60, 80));
    mWalkingAnimations[Entity::Left].setNumFrames(4);
    mWalkingAnimations[Entity::Left].setDuration(sf::seconds(0.9f));
    mWalkingAnimations[Entity::Left].setRepeating(true);
    mWalkingAnimations[Entity::Left].setOrigin(sf::Vector2f(-30.f, 40.f));

    mWalkingAnimations[Entity::Up].setTexture(textures.get(Textures::KidUp));
    mWalkingAnimations[Entity::Up].setFrameSize(sf::Vector2i(60, 80));
    mWalkingAnimations[Entity::Up].setNumFrames(4);
    mWalkingAnimations[Entity::Up].setDuration(sf::seconds(0.9f));
    mWalkingAnimations[Entity::Up].setRepeating(true);
    mWalkingAnimations[Entity::Up].setOrigin(sf::Vector2f(-30.f, 40.f));

    mWalkingAnimations[Entity::Down].setTexture(textures.get(Textures::KidDown));
    mWalkingAnimations[Entity::Down].setFrameSize(sf::Vector2i(60, 80));
    mWalkingAnimations[Entity::Down].setNumFrames(4);
    mWalkingAnimations[Entity::Down].setDuration(sf::seconds(0.9f));
    mWalkingAnimations[Entity::Down].setRepeating(true);
    mWalkingAnimations[Entity::Down].setOrigin(sf::Vector2f(-30.f, 40.f));
}


void BasicKidNode::updateCurrent(sf::Time dt, CommandQueue &commands)
{
    if(isDestroyed())
    {
        return;
    }

    mExistanceTimer += dt;


    // If time, target the player
    mTimer += dt;
    if(mTimer >= mTimeToRelocate)
    {
        mTimer = sf::Time::Zero;

        Command cmd;
        cmd.category = Category::Player;
        cmd.action = derivedAction<PlayerEntity>( [&] (PlayerEntity& player, sf::Time dt) {
            if(player.isDestroyed())
                return;
            sf::Vector2i playerPos = player.gridPosition();
            sf::Vector2i kidPos = gridPosition();
            sf::Vector2i diff = kidPos - playerPos;

            if((std::abs(diff.x) < std::abs(diff.y) && diff.x != 0) || (diff.y == 0 && diff.x != 0))
            {
                if(diff.x < 0)
                    move(Right, sf::Vector2i(kidPos + sf::Vector2i(1, 0)));
                else
                    move(Left, sf::Vector2i(kidPos + sf::Vector2i(-1, 0)));

                mState = Walking;
            }
            else if((std::abs(diff.x) >= std::abs(diff.y) && diff.y != 0) || (diff.x == 0 && diff.y != 0))
            {
                if(diff.y < 0)
                    move(Down, sf::Vector2i(kidPos + sf::Vector2i(0, 1)));
                else
                    move(Up, sf::Vector2i(kidPos + sf::Vector2i(0, -1)));

                mState = Walking;
            }
        });

        commands.push(cmd);
    }

    updateDirection();
    updateAnimation(dt);

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
                    mSprite = mRestingUpSprite;
                    setPosition(toIsoCoord(mOldGridPosition.x, mOldGridPosition.y));
                    if(randomInt(mIntelligence) == 0)
                        mTimer = mTimeToRelocate;
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
                    mSprite = mRestingDownSprite;
                    setPosition(toIsoCoord(mOldGridPosition.x, mOldGridPosition.y));
                    if(randomInt(mIntelligence) == 0)
                        mTimer = mTimeToRelocate;
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
                    mSprite = mRestingRightSprite;
                    setPosition(toIsoCoord(mOldGridPosition.x, mOldGridPosition.y));
                    if(randomInt(mIntelligence) == 0)
                        mTimer = mTimeToRelocate;
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
                    mSprite = mRestingLeftSprite;
                    setPosition(toIsoCoord(mOldGridPosition.x, mOldGridPosition.y));
                    if(randomInt(mIntelligence) == 0)
                        mTimer = mTimeToRelocate;
                }
            }
            break;

            default:break;
        }
    }

    Entity::updateCurrent(dt, commands);
}


void BasicKidNode::setInteligence(int i)
{
    if(i >= 1 && i <= 50);
        mIntelligence = i;
}


void BasicKidNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform.translate(mAnimationOffset);

    if(isDestroyed())
    {
        //target.draw(mDeadSprite, states);
        return;
    }

    if(mState == Walking)
    {
        target.draw(mWalkingAnimations[mDirection], states);
    }
    else
    {
        target.draw(mSprite, states);
    }
}

void BasicKidNode::updateAnimation(sf::Time dt)
{
    if(isDestroyed())
    {
        //mDieAnimation.update(dt);
    }
    else
    {
        if(mState == Walking)
        {
            mWalkingAnimations[mDirection].update(dt);
        }
    }
}

void BasicKidNode::updateDirection()
{
}


void BasicKidNode::move(Direction dir, sf::Vector2i whereTo)
{
    if(whereTo.x > 7 || whereTo.y > 7 || whereTo.x < 0 || whereTo.y < 0 || mState != Resting || isDestroyed())
        return;

    mDirection = dir;
    mGridPosition = whereTo;
    mState = Walking;

}

