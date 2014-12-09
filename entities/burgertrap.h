#ifndef BURGERTRAP_HPP
#define BURGERTRAP_HPP

#include <entities/entity.h>
#include <resources/resourceholder.h>
#include <resources/resourceidentifiers.h>

class BurgerTrap : public Entity
{
public:
    BurgerTrap(TextureHolder& textures);

    virtual void destroy();

private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt, CommandQueue &commands);

private:
    sf::Sprite  mSprite;
};

#endif // BURGERTRAP_HPP
