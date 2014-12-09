#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <entities/entity.h>
#include <resources/animation.h>
#include <resources/resourceholder.h>
#include <resources/resourceidentifiers.h>

class Projectile : public Entity
{
public:
    enum State
    {
        Resting,
        Walking
    };

public:
    Projectile(Entity::Type type, Entity::Direction dir, TextureHolder& textures);

    void            move(Direction dir, sf::Vector2i whereTo);

private:
    virtual void    updateCurrent(sf::Time dt, CommandQueue& commands);
    virtual void    drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


private:
    sf::Sprite      mSprite;
    sf::Vector2f    mAnimationOffset;
    State           mState;
};

#endif // PROJECTILE_H
