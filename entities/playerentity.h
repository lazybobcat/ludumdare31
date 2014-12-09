#ifndef PLAYERENTITY_HPP
#define PLAYERENTITY_HPP

#include <entities/entity.h>
#include <entities/ammonode.h>
#include <entities/bubblenode.h>
#include <resources/resourceholder.h>
#include <resources/resourceidentifiers.h>
#include <resources/animation.h>
#include <array>

class PlayerEntity : public Entity
{
public:
    typedef std::unique_ptr<PlayerEntity> Ptr;

    enum State
    {
        Resting,
        Walking,
        Firing
    };

public:
    PlayerEntity(TextureHolder& textures);
    virtual ~PlayerEntity() {}

    void        attack();
    void        setTrap();
    bool        isAttacking() const;

    void        move(Direction dir, sf::Vector2i whereTo);

    virtual bool isMarkedForRemoval() const { return false; }

    void        setBubble(BubbleNode* b) { mBubble = b; }
    BubbleNode* bubble() { return mBubble; }

    void        emote();


private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt, CommandQueue &commands);
    void         updateAnimation(sf::Time dt);
    void         updateDirection();

private:
    sf::Sprite                  mSprite;
    sf::Sprite                  mRestingUpSprite;
    sf::Sprite                  mRestingDownSprite;
    sf::Sprite                  mRestingLeftSprite;
    sf::Sprite                  mRestingRightSprite;
    sf::Sprite                  mDeadSprite;
    std::array<Animation, 4>    mWalkingAnimations;
    std::array<Animation, 4>    mFiringAnimations;
    sf::Vector2f                mAnimationOffset;
    State                       mState;
    bool                        mSpawnFiringSound;
    bool                        mSendSetTrapCommand;
    bool                        mSendFireCommand;
    bool                        mAmmoAttached;

    Command                     mFireCommand;
    Command                     mAttachAmmoCommand;

    AmmoNode*                   mAmmo;
    BubbleNode*                 mBubble;
};

#endif // PLAYERENTITY_HPP
