#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System/Time.hpp>

#include <entities/scenenode.h>
#include <entities/soundnode.h>

class CommandQueue;

class Entity : public SceneNode
{
public:
    enum Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    enum Type
    {
        Player,
        Kid,
        Trap,
        Explosion,
        RabbitBullet,
        KidBullet,
        TypeCount
    };

public:
    Entity(Type type);
    virtual ~Entity() { }

    void        damage(int points);
    void        heal(int points);
    virtual void destroy();
    int         getHealthpoints() const;
    bool        isDestroyed() const;

    virtual unsigned int    getCategory() const
    {
        switch(mType)
        {
            case Player:
                return Category::Player;

            case Kid:
                return Category::Enemy;

            case Trap:
                return Category::Trap;

            case Explosion:
                return Category::Explosion;

            case RabbitBullet:
                return Category::FriendlyBullet;

            case KidBullet:
                return Category::EnemyBullet;

            default:return Category::Enemy;
        }
    }

    virtual bool isCollidable() { return true; }

    virtual bool isMarkedForRemoval() const { return isDestroyed(); }

protected:
    virtual void    updateCurrent(sf::Time, CommandQueue& commands);

public:
    Type        mType;
    int         mHealthpoints;
    float       mSpeed;
    Direction   mDirection;
    sf::Time    mMovementTime;
    bool        mIsMoving;
};

#endif // ENTITY_H
