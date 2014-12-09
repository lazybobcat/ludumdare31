#ifndef HOLETRAP_H
#define HOLETRAP_H

#include <entities/entity.h>
#include <resources/animation.h>
#include <resources/resourceholder.h>
#include <resources/resourceidentifiers.h>

class HoleTrap : public Entity
{
public:
    HoleTrap(TextureHolder& textures);

    virtual void destroy();

private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt, CommandQueue &commands);

private:
    bool            mActive;
    bool            mPlaySound;
    Animation       mAnimation;
    Animation       mActiveAnimation;
    sf::Sprite      mEndSprite;

    sf::Time        mDepopTime;
};

#endif // HOLETRAP_H
