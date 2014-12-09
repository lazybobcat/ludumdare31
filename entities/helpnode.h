#ifndef HELPNODE_H
#define HELPNODE_H

#include <entities/scenenode.h>
#include <resources/resourceholder.h>
#include <resources/resourceidentifiers.h>

class HelpNode : public SceneNode
{
public:
    HelpNode(TextureHolder& textures);


    virtual bool    isMarkedForRemoval() const { return mTimer >= sf::seconds(15.f); }

    const sf::Vector2f& getPosition() const
    {
        return mFakePosition;
    }

private:
    virtual void    drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(mSprite, states);
    }

    virtual void    updateCurrent(sf::Time dt, CommandQueue &commands)
    {
        mTimer += dt;
    }

private:
    sf::Sprite      mSprite;
    sf::Time        mTimer;

    sf::Vector2f    mFakePosition;
};

#endif // HELPNODE_H
