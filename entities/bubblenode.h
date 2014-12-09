#ifndef BUBBLENODE_H
#define BUBBLENODE_H

#include <entities/scenenode.h>
#include <resources/resourceholder.h>
#include <resources/resourceidentifiers.h>
#include <string>

class BubbleNode : public SceneNode
{
public:
    BubbleNode(TextureHolder& textures, FontHolder& fonts);

    void    setString(const std::string& str);

private:
    virtual void    drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
    {
        if(mShow)
        {
            target.draw(mSprite, states);
            target.draw(mText, states);
        }
    }

    virtual void    updateCurrent(sf::Time dt, CommandQueue &commands)
    {
        mTimer += dt;
        if(mShow)
        {
            mTimer += dt;
            if(mTimer >= sf::seconds(2.5f))
                mShow = false;
        }
    }

private:
    sf::Sprite      mSprite;
    sf::Text        mText;

    bool            mShow;
    sf::Time        mTimer;
};

#endif // BUBBLENODE_H
