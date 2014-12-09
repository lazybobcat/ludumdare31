#ifndef TRAPLISTNODE_HPP
#define TRAPLISTNODE_HPP

#include <entities/scenenode.h>
#include <resources/resourceholder.h>
#include <resources/resourceidentifiers.h>
#include <deque>
#include <string>

class TraplistNode : public SceneNode
{
public:
    enum TrapTypes
    {
        None = 0,
        Hole = 1,
        Burger = 2,
        Tnt = 3,
        Count
    };

    enum TelegraphTypes
    {
        Ally,
        Enemy
    };

    enum TelegraphShapes
    {
        Square,
        Line
    };

    struct Trap
    {
        Trap() :
            type(None),
            name(),
            telegraphType(Ally),
            telegraphShape(Square)
        {
        }

        ~Trap() {}

        TrapTypes       type;
        std::string     name;
        TelegraphTypes  telegraphType;
        TelegraphShapes telegraphShape;
    };

public:
    TraplistNode(TextureHolder& textures, FontHolder& fonts);
    virtual ~TraplistNode() { mTrapList.clear(); }

    void    generateTraps(unsigned int number);
    void    grantTrap(unsigned int number = 1);
    void    setTrap(sf::Vector2i pos);
    Trap    nextTrap();

private:
    Trap            buildTrap(TrapTypes type);
    virtual void    updateCurrent(sf::Time dt, CommandQueue &commands);
    virtual void    drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    TextureHolder&      mTextures;
    FontHolder&         mFonts;

    std::deque<Trap>    mTrapList;

    sf::Sprite          mUi;
    sf::Sprite          mHoleSprite;
    sf::Sprite          mTntSprite;
    sf::Sprite          mBurgerSprite;
    sf::Text            mFirstTrapName;

    bool                mSetTrap;
    Command             mSetTrapCommand;
};

#endif // TRAPLISTNODE_HPP
