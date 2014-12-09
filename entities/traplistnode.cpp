#include <entities/traplistnode.h>
#include <entities/burgertrap.h>
#include <entities/holetrap.h>
#include <entities/tnttrap.h>
#include <utils.h>
#include <iostream>

TraplistNode::TraplistNode(TextureHolder &textures, FontHolder &fonts) :
    SceneNode(Category::Traplist),
    mTextures(textures),
    mFonts(fonts),
    mSetTrap(false)
{
    mUi.setTexture(textures.get(Textures::UiTraplist));
    mHoleSprite.setTexture(textures.get(Textures::TraplistHole));
    mTntSprite.setTexture(textures.get(Textures::TraplistTnt));
    mBurgerSprite.setTexture(textures.get(Textures::TraplistBurger));

    mFirstTrapName.setFont(fonts.get(Fonts::Main));
    mFirstTrapName.setPosition(145.f, 0.f);
}


void TraplistNode::setTrap(sf::Vector2i pos)
{
    if(!mTrapList.empty())
    {
        // Create trap and add the node
        mSetTrapCommand.category = Category::EntityLayer;
        mSetTrapCommand.action = [&, pos] (SceneNode& node, sf::Time dt) {
            Trap t = mTrapList.front();
            mTrapList.pop_front();

            if(t.type == TrapTypes::Hole)
            {
                std::unique_ptr<HoleTrap> hole(new HoleTrap(mTextures));
                hole->setPosition(toIsoCoord(pos.x, pos.y));
                hole->setGridPosition(sf::Vector2i(pos.x, pos.y));
                node.attachChild(std::move(hole));
            }
            else if(t.type == TrapTypes::Burger)
            {
                std::unique_ptr<BurgerTrap> burger(new BurgerTrap(mTextures));
                burger->setPosition(toIsoCoord(pos.x, pos.y));
                burger->setGridPosition(sf::Vector2i(pos.x, pos.y));
                node.attachChild(std::move(burger));
            }
            else if(t.type == TrapTypes::Tnt)
            {
                std::unique_ptr<TntTrap> tnt(new TntTrap(mTextures, mFonts));
                tnt->setPosition(toIsoCoord(pos.x, pos.y));
                tnt->setGridPosition(sf::Vector2i(pos.x, pos.y));
                node.attachChild(std::move(tnt));
            }
            else
            {
                std::cout << "Unhandled type " << (int)t.type << " !" << std::endl;
            }

            if(!mTrapList.empty())
                mFirstTrapName.setString(mTrapList.front().name);
            else
                mFirstTrapName.setString("No More Traps :(");
        };

        mSetTrap = true;
    }
}

TraplistNode::Trap TraplistNode::nextTrap()
{
    if(mTrapList.empty())
        return buildTrap(None);

    return mTrapList.front();
}


void TraplistNode::generateTraps(unsigned int number)
{
    mTrapList.clear();

    for(unsigned int i = 0; i < number; ++i)
    {
        int r = randomInt((int)TrapTypes::Count -1) + 1;
        std::cout << "Build trap #" << r << std::endl;
        mTrapList.push_back(buildTrap((TrapTypes)r));
    }

    mFirstTrapName.setString(mTrapList.front().name);
}

void TraplistNode::grantTrap(unsigned int number)
{
    for(unsigned int i = 0; i < number; ++i)
    {
        int r = randomInt((int)TrapTypes::Count -1) + 1;
        std::cout << "Build trap #" << r << std::endl;
        mTrapList.push_back(buildTrap((TrapTypes)r));
    }

    mFirstTrapName.setString(mTrapList.front().name);
}


TraplistNode::Trap TraplistNode::buildTrap(TrapTypes type)
{
    Trap t;
    t.type = type;
    switch(type)
    {
        case Hole:
            t.name = "Rabbit Hole";
            t.telegraphShape = Square;
            t.telegraphType  = Ally;
            break;

        case Burger:
            t.name = "Razor Burger";
            t.telegraphShape = Square;
            t.telegraphType  = Ally;
            break;

        case Tnt:
            t.name = "T.N.T, Be Cautious !";
            t.telegraphShape = Square;
            t.telegraphType  = Enemy;
            break;

        default:
            t.name = "This is probably a bug";
            t.type = None;
            t.telegraphShape = Square;
            t.telegraphType  = Ally;
            break;
    }

    return t;
}

void TraplistNode::updateCurrent(sf::Time dt, CommandQueue &commands)
{
    if(mSetTrap)
    {
        mSetTrap = false;
        commands.push(mSetTrapCommand);
        playLocalSound(commands, Sounds::SetTrap);
    }
}


void TraplistNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mUi, states);
    target.draw(mFirstTrapName, states);

    sf::Sprite spr;
    for(std::size_t i = 0; i < mTrapList.size(); ++i)
    {
        switch(mTrapList[i].type)
        {
            case Hole:
                spr = mHoleSprite;
                break;

            case Burger:
                spr = mBurgerSprite;
                break;

            case Tnt:
            default:
                spr = mTntSprite;
                break;
        }

        spr.setPosition(0.f, i * 120.f);

        if(i > 0)
        {
            spr.setColor(sf::Color(255,255,255,100));
        }

        target.draw(spr, states);
    }
}


