#ifndef TNTTRAP_H
#define TNTTRAP_H

#include <entities/entity.h>
#include <resources/animation.h>
#include <resources/resourceholder.h>
#include <resources/resourceidentifiers.h>

class TntTrap : public Entity
{
public:
    TntTrap(TextureHolder& textures, FontHolder& fonts);

    virtual void destroy();

private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt, CommandQueue &commands);

private:
    TextureHolder&  mTextures;

    sf::Time        mTimer;
    sf::Sprite      mSprite;
    sf::Text        mText;

    bool            mPopExplosions;
};

#endif // TNTTRAP_H
