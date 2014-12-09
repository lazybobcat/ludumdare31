#include <entities/burgertrap.h>

BurgerTrap::BurgerTrap(TextureHolder &textures) :
    Entity(Entity::Trap)
{
    mSprite.setTexture(textures.get(Textures::Burger));
    mSprite.setOrigin(sf::Vector2f(0.f, 30.f));
}


void BurgerTrap::destroy()
{
    // Animation ?
    Entity::destroy();
}


void BurgerTrap::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

void BurgerTrap::updateCurrent(sf::Time dt, CommandQueue &commands)
{
}
