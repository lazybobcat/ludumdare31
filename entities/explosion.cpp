#include <entities/explosion.h>
#include <entities/cameranode.h>
#include <utils.h>

ExplosionNode::ExplosionNode(TextureHolder &textures, sf::Vector2i tileToExplode, sf::Time delay) :
    Entity(Entity::Explosion),
    mTileToExplode(tileToExplode),
    mDelay(delay),
    mDelayTimer(sf::Time::Zero),
    mActive(false)
{
    mAnimation.setTexture(textures.get(Textures::Explosion));
    mAnimation.setFrameSize(sf::Vector2i(120, 150));
    mAnimation.setNumFrames(6);
    mAnimation.setDuration(sf::seconds(0.5f));
    mAnimation.setRepeating(false);
    mAnimation.setOrigin(sf::Vector2f(0.f, 90.f));
}

void ExplosionNode::updateCurrent(sf::Time dt, CommandQueue &commands)
{
    if(isDestroyed())
        return;

    mDelayTimer += dt;
    if(mDelayTimer > mDelay && !mActive)
    {
        mActive = true;
        setGridPosition(mTileToExplode);
        setPosition(toIsoCoord(mTileToExplode.x, mTileToExplode.y));
        Command command;
        command.category = Category::Camera;
        command.action = derivedAction<CameraNode>([&](CameraNode& c, sf::Time) {
            c.shake(sf::seconds(0.05f));
        });
        commands.push(command);
        playLocalSound(commands, Sounds::Explosion);
    }

    if(mActive)
    {
        if(mAnimation.isFinished())
            destroy();
        else
            mAnimation.update(dt);
    }
}

void ExplosionNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(isDestroyed() || !mActive)
        return;

    target.draw(mAnimation, states);
}
