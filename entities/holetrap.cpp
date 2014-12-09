#include <entities/holetrap.h>

HoleTrap::HoleTrap(TextureHolder &textures) :
    Entity(Entity::Trap),
    mActive(false),
    mPlaySound(false),
    mDepopTime(sf::Time::Zero)
{
    mSpeed = 1.5f;

    // Standing animation
    mAnimation.setTexture(textures.get(Textures::HoleStanding));
    mAnimation.setFrameSize(sf::Vector2i(120, 60));
    mAnimation.setNumFrames(6);
    mAnimation.setDuration(sf::seconds(mSpeed));
    mAnimation.setRepeating(true);
    mAnimation.setOrigin(sf::Vector2f(0.f, 0.f));

    // Active animation
    mActiveAnimation.setTexture(textures.get(Textures::HoleActive));
    mActiveAnimation.setFrameSize(sf::Vector2i(120, 60));
    mActiveAnimation.setNumFrames(6);
    mActiveAnimation.setDuration(sf::seconds(0.5f));
    mActiveAnimation.setRepeating(false);
    mActiveAnimation.setOrigin(sf::Vector2f(0.f, 0.f));

    mEndSprite.setTexture(textures.get(Textures::HoleActive));
    mEndSprite.setTextureRect(sf::IntRect(5*120, 0, 120, 60));
}


void HoleTrap::destroy()
{
    mActive = true;
    mPlaySound = true;
}


void HoleTrap::updateCurrent(sf::Time dt, CommandQueue &commands)
{
    if(isDestroyed())
        return;

    if(mPlaySound)
    {
        mPlaySound = false;
        playLocalSound(commands, Sounds::Slurp);
    }

    if(mActive)
    {
        if(mActiveAnimation.isFinished())
        {
            mDepopTime += dt;
            if(mDepopTime >= sf::seconds(3.f))
                Entity::destroy();
        }
        else
            mActiveAnimation.update(dt);
    }
    else
    {
        mAnimation.update(dt);
    }
}

void HoleTrap::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(isDestroyed())
        return;

    if(mActive && mDepopTime == sf::Time::Zero)
    {
        target.draw(mActiveAnimation, states);
    }
    else if(mActive)
    {
        target.draw(mEndSprite, states);
    }
    else
    {
        target.draw(mAnimation, states);
    }
}

