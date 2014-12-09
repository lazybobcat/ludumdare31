#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <entities/entity.h>
#include <resources/animation.h>
#include <resources/resourceholder.h>
#include <resources/resourceidentifiers.h>
#include <SFML/System.hpp>

class ExplosionNode : public Entity
{
public:
    ExplosionNode(TextureHolder& textures, sf::Vector2i tileToExplode, sf::Time delay);


private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt, CommandQueue &commands);

private:
    Animation       mAnimation;

    sf::Vector2i    mTileToExplode;
    sf::Time        mDelay;
    sf::Time        mDelayTimer;
    bool            mActive;
};

#endif // EXPLOSION_H
