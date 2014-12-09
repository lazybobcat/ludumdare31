#include <entities/entity.h>
#include <entities/scenenode.h>
#include <events/commandqueue.h>

Entity::Entity(Type type) :
    mType(type),
    mHealthpoints(1),
    mSpeed(0.5f),
    mDirection(Right),
    mMovementTime(sf::Time::Zero),
    mIsMoving(false)
{
}

void Entity::updateCurrent(sf::Time, CommandQueue &/*commands*/)
{

}

void Entity::damage(int points)
{
    mHealthpoints -= points;
}

void Entity::heal(int points)
{
    mHealthpoints += points;
}

void Entity::destroy()
{
    mHealthpoints = 0;
}

int Entity::getHealthpoints() const
{
    return mHealthpoints;
}

bool Entity::isDestroyed() const
{
    return (mHealthpoints <= 0);
}

