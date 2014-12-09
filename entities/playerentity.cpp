#include <entities/playerentity.h>
#include <entities/traplistnode.h>
#include <entities/projectile.h>
#include <utils.h>

#include <iostream>

PlayerEntity::PlayerEntity(TextureHolder &textures) :
    Entity(Entity::Player),
    mSprite(textures.get(Textures::RabbitRight), sf::IntRect(0, 0, 60, 120)),
    mRestingUpSprite(textures.get(Textures::RabbitUp), sf::IntRect(0, 0, 60, 120)),
    mRestingDownSprite(textures.get(Textures::RabbitDown), sf::IntRect(0, 0, 60, 120)),
    mRestingLeftSprite(textures.get(Textures::RabbitLeft), sf::IntRect(0, 0, 60, 120)),
    mRestingRightSprite(textures.get(Textures::RabbitRight), sf::IntRect(0, 0, 60, 120)),
    mDeadSprite(textures.get(Textures::RabbitDead)),
    mState(Resting),
    mSpawnFiringSound(false),
    mSendSetTrapCommand(false),
    mSendFireCommand(false),
    mAmmoAttached(false),
    mAmmo(nullptr),
    mBubble(nullptr)
{
    // RESTING
    mSprite.setOrigin(sf::Vector2f(-30.f, 80.f));
    mRestingUpSprite.setOrigin(sf::Vector2f(-30.f, 80.f));
    mRestingDownSprite.setOrigin(sf::Vector2f(-30.f, 80.f));
    mRestingLeftSprite.setOrigin(sf::Vector2f(-30.f, 80.f));
    mRestingRightSprite.setOrigin(sf::Vector2f(-30.f, 80.f));
    mDeadSprite.setOrigin(sf::Vector2f(0.f, 10.f));
    //mSprite.setScale(sf::Vector2f(2.f, 2.f));



    // WALKING
    mWalkingAnimations[Entity::Right].setTexture(textures.get(Textures::RabbitRight));
    mWalkingAnimations[Entity::Right].setFrameSize(sf::Vector2i(60, 120));
    mWalkingAnimations[Entity::Right].setNumFrames(10);
    mWalkingAnimations[Entity::Right].setDuration(sf::seconds(mSpeed));
    mWalkingAnimations[Entity::Right].setRepeating(true);
    mWalkingAnimations[Entity::Right].setOrigin(sf::Vector2f(-30.f, 80.f));
    //mWalkingAnimations[Entity::Right].setScale(sf::Vector2f(2.f, 2.f));

    mWalkingAnimations[Entity::Left].setTexture(textures.get(Textures::RabbitLeft));
    mWalkingAnimations[Entity::Left].setFrameSize(sf::Vector2i(60, 120));
    mWalkingAnimations[Entity::Left].setNumFrames(10);
    mWalkingAnimations[Entity::Left].setDuration(sf::seconds(mSpeed));
    mWalkingAnimations[Entity::Left].setRepeating(true);
    mWalkingAnimations[Entity::Left].setOrigin(sf::Vector2f(-30.f, 80.f));
    //mWalkingAnimations[Entity::Left].setScale(sf::Vector2f(2.f, 2.f));

    mWalkingAnimations[Entity::Up].setTexture(textures.get(Textures::RabbitUp));
    mWalkingAnimations[Entity::Up].setFrameSize(sf::Vector2i(60, 120));
    mWalkingAnimations[Entity::Up].setNumFrames(10);
    mWalkingAnimations[Entity::Up].setDuration(sf::seconds(mSpeed));
    mWalkingAnimations[Entity::Up].setRepeating(true);
    mWalkingAnimations[Entity::Up].setOrigin(sf::Vector2f(-30.f, 80.f));
    //mWalkingAnimations[Entity::Up].setScale(sf::Vector2f(2.f, 2.f));

    mWalkingAnimations[Entity::Down].setTexture(textures.get(Textures::RabbitDown));
    mWalkingAnimations[Entity::Down].setFrameSize(sf::Vector2i(60, 120));
    mWalkingAnimations[Entity::Down].setNumFrames(10);
    mWalkingAnimations[Entity::Down].setDuration(sf::seconds(mSpeed));
    mWalkingAnimations[Entity::Down].setRepeating(true);
    mWalkingAnimations[Entity::Down].setOrigin(sf::Vector2f(-30.f, 80.f));
    //mWalkingAnimations[Entity::Down].setScale(sf::Vector2f(2.f, 2.f));


    // FIRING
    mFiringAnimations[Entity::Right].setTexture(textures.get(Textures::RabbitFiringRight));
    mFiringAnimations[Entity::Right].setFrameSize(sf::Vector2i(60, 120));
    mFiringAnimations[Entity::Right].setNumFrames(5);
    mFiringAnimations[Entity::Right].setDuration(sf::seconds(mSpeed));
    mFiringAnimations[Entity::Right].setRepeating(false);
    mFiringAnimations[Entity::Right].setOrigin(sf::Vector2f(-30.f, 80.f));
    //mFiringAnimations[Entity::Right].setScale(sf::Vector2f(2.f, 2.f));

    mFiringAnimations[Entity::Left].setTexture(textures.get(Textures::RabbitFiringLeft));
    mFiringAnimations[Entity::Left].setFrameSize(sf::Vector2i(60, 120));
    mFiringAnimations[Entity::Left].setNumFrames(5);
    mFiringAnimations[Entity::Left].setDuration(sf::seconds(mSpeed));
    mFiringAnimations[Entity::Left].setRepeating(false);
    mFiringAnimations[Entity::Left].setOrigin(sf::Vector2f(-30.f, 80.f));
    //mFiringAnimations[Entity::Left].setScale(sf::Vector2f(2.f, 2.f));

    mFiringAnimations[Entity::Up].setTexture(textures.get(Textures::RabbitFiringUp));
    mFiringAnimations[Entity::Up].setFrameSize(sf::Vector2i(60, 120));
    mFiringAnimations[Entity::Up].setNumFrames(5);
    mFiringAnimations[Entity::Up].setDuration(sf::seconds(mSpeed));
    mFiringAnimations[Entity::Up].setRepeating(false);
    mFiringAnimations[Entity::Up].setOrigin(sf::Vector2f(-30.f, 80.f));
    //mFiringAnimations[Entity::Up].setScale(sf::Vector2f(2.f, 2.f));

    mFiringAnimations[Entity::Down].setTexture(textures.get(Textures::RabbitFiringDown));
    mFiringAnimations[Entity::Down].setFrameSize(sf::Vector2i(60, 120));
    mFiringAnimations[Entity::Down].setNumFrames(5);
    mFiringAnimations[Entity::Down].setDuration(sf::seconds(mSpeed));
    mFiringAnimations[Entity::Down].setRepeating(false);
    mFiringAnimations[Entity::Down].setOrigin(sf::Vector2f(-30.f, 80.f));
    //mFiringAnimations[Entity::Down].setScale(sf::Vector2f(2.f, 2.f));


    // COMMANDS
    mFireCommand.category = Category::EntityLayer;
    mFireCommand.action = [&](SceneNode& node, sf::Time dt) {
        sf::Vector2i pos = gridPosition();
        sf::Vector2i dirM = gridPosition();
        switch(mDirection)
        {
            case Up:
                dirM += sf::Vector2i(0, -1);
                break;

            case Down:
                dirM += sf::Vector2i(0, 1);
                break;

            case Left:
                dirM += sf::Vector2i(-1, 0);
                break;

            case Right:
                dirM += sf::Vector2i(1, 0);
                break;

            default:break;
        }
        if(pos.x >= 0 && pos.x < 8 && pos.y >= 0 && pos.y < 8)
        {
            std::unique_ptr<Projectile> projectile(new Projectile(Entity::RabbitBullet, mDirection, textures));
            projectile->setPosition(toIsoCoord(pos.x, pos.y));
            projectile->setGridPosition(sf::Vector2i(pos.x, pos.y));
            projectile->move(mDirection, dirM);
            node.attachChild(std::move(projectile));
            std::cout << "Projectile cmd launched" << std::endl;
        }
    };


    // Create Ammo reloader
    mAttachAmmoCommand.category = Category::EntityLayer;
    mAttachAmmoCommand.action = [&](SceneNode& node, sf::Time dt) {
        std::unique_ptr<AmmoNode> ammo(new AmmoNode(textures));
        mAmmo = ammo.get();
        node.attachChild(std::move(ammo));
    };
}

void PlayerEntity::updateCurrent(sf::Time dt, CommandQueue &commands)
{
    if(isDestroyed())
    {
        return;
    }

    if(!mAmmoAttached)
    {
        commands.push(mAttachAmmoCommand);
        mAmmoAttached = true;
    }

    if(mSendSetTrapCommand)
    {
        mSendSetTrapCommand = false;
        Command cmd;
        cmd.action = derivedAction<TraplistNode>([&](TraplistNode& node, sf::Time dt) {
            sf::Vector2i pos = gridPosition();
            switch(mDirection)
            {
                case Up:
                    pos += sf::Vector2i(0, -1);
                    break;

                case Down:
                    pos += sf::Vector2i(0, 1);
                    break;

                case Left:
                    pos += sf::Vector2i(-1, 0);
                    break;

                case Right:
                    pos += sf::Vector2i(1, 0);
                    break;

                default:break;
            }
            if(pos.x >= 0 && pos.x < 8 && pos.y >= 0 && pos.y < 8)
                node.setTrap(pos);
        });
        cmd.category = Category::Traplist;
        commands.push(cmd);
    }

    if(mSendFireCommand)
    {
        mSendFireCommand = false;
        commands.push(mFireCommand);
    }


    updateDirection();
    updateAnimation(dt);

    if(mState == Firing)
    {
        if(mFiringAnimations[mDirection].isFinished())
        {
            mState = Resting;
            mFiringAnimations[mDirection].restart();
        }

        if(mSpawnFiringSound)
        {
            mSpawnFiringSound = false;
            playLocalSound(commands, Sounds::CarrotFire);
        }
    }
    else if(mState == Walking)
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
                }
                setPosition(toIsoCoord(mOldGridPosition.x, mOldGridPosition.y) + mAnimationOffset);
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
                }
                setPosition(toIsoCoord(mOldGridPosition.x, mOldGridPosition.y) + mAnimationOffset);
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
                }
                setPosition(toIsoCoord(mOldGridPosition.x, mOldGridPosition.y) + mAnimationOffset);
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
                }
                setPosition(toIsoCoord(mOldGridPosition.x, mOldGridPosition.y) + mAnimationOffset);
            }
            break;

            default:break;
        }
    }

    Entity::updateCurrent(dt, commands);
}

void PlayerEntity::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    //states.transform.translate(mAnimationOffset);

    if(isDestroyed())
    {
        target.draw(mDeadSprite, states);
        return;
    }

    if(mState == Firing)
    {
         target.draw(mFiringAnimations[mDirection], states);
    }
    else if(mState == Walking)
    {
        target.draw(mWalkingAnimations[mDirection], states);
    }
    else
    {
        target.draw(mSprite, states);
    }
}

void PlayerEntity::updateAnimation(sf::Time dt)
{
    if(isDestroyed())
    {
        //mDieAnimation.update(dt);
    }
    else
    {
        if(mState == Firing)
        {
            mFiringAnimations[mDirection].update(dt);
        }
        else
        {
            mWalkingAnimations[mDirection].update(dt);
        }
    }
}

void PlayerEntity::updateDirection()
{
    /*switch(mDirection)
    {
        case Entity::Right:
            mSprite.setTextureRect(sf::IntRect(64,0,64,64));
            break;

        case Entity::Left:
            mSprite.setTextureRect(sf::IntRect(0,0,64,64));
            break;
    }*/
}

void PlayerEntity::attack()
{
    if(mState == Resting && mAmmo && mAmmo->canShot())
    {
        mState = Firing;
        mSpawnFiringSound = true;
        mSendFireCommand = true;
        mAmmo->consumeAmmo();
        if(mBubble && randomInt(2) == 0)
            mBubble->setString("PIOU! PIOU! Carrot Gun");
    }
}

void PlayerEntity::setTrap()
{
    if(mState == Resting)
    {
        mSendSetTrapCommand = true;
    }
}

bool PlayerEntity::isAttacking() const
{
    return mState == Firing;
}


void PlayerEntity::move(Direction dir, sf::Vector2i whereTo)
{
    if(whereTo.x > 7 || whereTo.y > 7 || whereTo.x < 0 || whereTo.y < 0 || mState != Resting || isDestroyed())
        return;

    mDirection = dir;
    mGridPosition = whereTo;
    mState = Walking;
}


void PlayerEntity::emote()
{
    static std::string emotes[] = {
        "Kill Kids! EXTERMINATE!",
        "Muahahahahaa!",
        "YOU'LL NEVER CATCH ME!",
        "C'mon fatty !",
        "I want explosions",
        "You gonna pay!"
    };

    if(mBubble)
    {
        mBubble->setString(emotes[randomInt(6)]);
    }
}

