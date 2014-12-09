#ifndef BASICKIDNODE_HPP
#define BASICKIDNODE_HPP

#include <entities/entity.h>
#include <resources/animation.h>
#include <resources/resourceholder.h>
#include <resources/resourceidentifiers.h>
#include <array>

#include <iostream>

class BasicKidNode : public Entity
{
public:
    enum State
    {
        Resting,
        Walking
    };

public:
    BasicKidNode(TextureHolder& textures, float speed = 1.5f);

    void        move(Direction dir, sf::Vector2i whereTo);

    void        setInteligence(int i); // small i mean huge intel, min = 1, max = 50

    virtual bool            isCollidable()
    {
        return mExistanceTimer >= sf::seconds(2.3f);
    }

private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt, CommandQueue &commands);
    void         updateAnimation(sf::Time dt);
    void         updateDirection();

private:
    sf::Time                    mExistanceTimer;
    sf::Time                    mTimer;
    sf::Time                    mTimeToRelocate;
    sf::Sprite                  mSprite;
    sf::Sprite                  mRestingUpSprite;
    sf::Sprite                  mRestingDownSprite;
    sf::Sprite                  mRestingLeftSprite;
    sf::Sprite                  mRestingRightSprite;
    std::array<Animation, 4>    mWalkingAnimations;
    sf::Vector2f                mAnimationOffset;
    State                       mState;
    int                         mIntelligence;
};

#endif // BASICKIDNODE_HPP
