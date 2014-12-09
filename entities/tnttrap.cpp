#include <entities/tnttrap.h>
#include <entities/explosion.h>
#include <utils.h>
#include <memory>

TntTrap::TntTrap(TextureHolder &textures, FontHolder &fonts) :
    Entity(Entity::Trap),
    mTextures(textures),
    mPopExplosions(false)
{
    mSprite.setTexture(textures.get(Textures::Tnt));
    mSprite.setOrigin(sf::Vector2f(0.f, 30.f));

    mText.setFont(fonts.get(Fonts::Main));
    mText.setString("3");
    mText.setOrigin(sf::Vector2f(-53.f, 10.f));
}


void TntTrap::destroy()
{
    // Pop explosions
    mPopExplosions = true;
}


void TntTrap::updateCurrent(sf::Time dt, CommandQueue &commands)
{
    if(mPopExplosions)
    {
        mPopExplosions = false;

        Command cmd;
        cmd.category = Category::EntityLayer;
        cmd.action = [&] (SceneNode& node, sf::Time dtime) {
            sf::Vector2i gridPos = gridPosition();

            std::unique_ptr<ExplosionNode> explo(new ExplosionNode(mTextures, gridPos, sf::seconds(0.f)));
            explo->setGridPosition(gridPos);
            node.attachChild(std::move(explo));

            for(int i = 1; i < 9; ++i)
            {
                // Up
                sf::Vector2i nPos = gridPos + sf::Vector2i(0, -1 * i);
                if(nPos.y >= 0)
                {
                    explo.reset(new ExplosionNode(mTextures, nPos, sf::seconds(i * 0.3f)));
                    explo->setGridPosition(gridPos);
                    node.attachChild(std::move(explo));
                }

                // Down
                nPos = gridPos + sf::Vector2i(0, 1 * i);
                if(nPos.y < 8)
                {
                    explo.reset(new ExplosionNode(mTextures, nPos, sf::seconds(i * 0.3f)));
                    explo->setGridPosition(gridPos);
                    node.attachChild(std::move(explo));
                }

                // Right
                nPos = gridPos + sf::Vector2i(1 * i, 0);
                if(nPos.x < 8)
                {
                    explo.reset(new ExplosionNode(mTextures, nPos, sf::seconds(i * 0.3f)));
                    explo->setGridPosition(gridPos);
                    node.attachChild(std::move(explo));
                }

                // Right
                nPos = gridPos + sf::Vector2i(-1 * i, 0);
                if(nPos.x >= 0)
                {
                    explo.reset(new ExplosionNode(mTextures, nPos, sf::seconds(i * 0.3f)));
                    explo->setGridPosition(gridPos);
                    node.attachChild(std::move(explo));
                }
            }

            Entity::destroy();
        };

        commands.push(cmd);

        return;
    }

    if(isDestroyed())
        return;

    mTimer += dt;
    if(mTimer >= sf::seconds(3.f))
    {
        destroy();
        return;
    }

    std::string oldstring = mText.getString().toAnsiString();
    std::string newstring = toString((int)(sf::seconds(3.f) - mTimer).asSeconds() + 1);
    mText.setString(newstring);
    if(oldstring != newstring && newstring != "0")
        playLocalSound(commands, Sounds::Tick);
}


void TntTrap::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(isDestroyed())
        return;

    target.draw(mSprite, states);
    target.draw(mText, states);
}

