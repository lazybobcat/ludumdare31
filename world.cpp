#include <world.h>
#include <utils.h>
#include <entities/playerentity.h>
#include <entities/traplistnode.h>
#include <entities/burgertrap.h>
#include <entities/basickidnode.h>
#include <entities/tnttrap.h>
#include <events/category.h>
#include <entities/cameranode.h>
#include <entities/wavegenerator.h>
#include <entities/helpnode.h>

World::World(sf::RenderWindow& window, TextureHolder &textures, FontHolder &fonts, MusicPlayer &music, SoundPlayer &sounds, ScriptPlayer &scripts, PlayerController &player) :
    mWindow(window),
    mWorldView(window.getDefaultView()),
    mTextures(textures),
    mFonts(fonts),
    mMusic(music),
    mSounds(sounds),
    mScripts(scripts),
    mPlayer(nullptr),
    mSceneGraph(),
    mSceneLayers()
{
    loadTextures();
    buildScene();

    // Other things here, like setting the view center on the player, scores, etc...
    mKidKilledCommand.category = Category::WaveGenerator;
    mKidKilledCommand.action = derivedAction<WaveGenerator>([&](WaveGenerator& gen, sf::Time dt) {
        gen.kidKilled();
    });
}


void World::loadTextures()
{
    mTextures.load(Textures::Help,          "assets/textures/help.png");
    mTextures.load(Textures::Background,    "assets/textures/background.png");
    mTextures.load(Textures::RabbitRight,   "assets/textures/rabbit-right.png");
    mTextures.load(Textures::RabbitLeft,    "assets/textures/rabbit-left.png");
    mTextures.load(Textures::RabbitUp,      "assets/textures/rabbit-up.png");
    mTextures.load(Textures::RabbitDown,    "assets/textures/rabbit-down.png");
    mTextures.load(Textures::RabbitFiringRight,   "assets/textures/rabbit-firing-right.png");
    mTextures.load(Textures::RabbitFiringLeft,    "assets/textures/rabbit-firing-left.png");
    mTextures.load(Textures::RabbitFiringUp,      "assets/textures/rabbit-firing-up.png");
    mTextures.load(Textures::RabbitFiringDown,    "assets/textures/rabbit-firing-down.png");
    mTextures.load(Textures::RabbitDead,    "assets/textures/rabbit-dead.png");
    mTextures.load(Textures::KidRight,      "assets/textures/kid-right.png");
    mTextures.load(Textures::KidLeft,       "assets/textures/kid-left.png");
    mTextures.load(Textures::KidUp,         "assets/textures/kid-up.png");
    mTextures.load(Textures::KidDown,       "assets/textures/kid-down.png");
    mTextures.load(Textures::Tile,          "assets/textures/tile.png");
    mTextures.load(Textures::TelegraphBlue, "assets/textures/telegraph-blue.png");
    mTextures.load(Textures::TelegraphRed,  "assets/textures/telegraph-red.png");
    mTextures.load(Textures::HoleStanding,  "assets/textures/hole-standing.png");
    mTextures.load(Textures::HoleActive,    "assets/textures/hole-active.png");
    mTextures.load(Textures::Tnt,           "assets/textures/tnt.png");
    mTextures.load(Textures::Burger,        "assets/textures/burger.png");
    mTextures.load(Textures::Explosion,     "assets/textures/explosion.png");
    mTextures.load(Textures::UiTraplist,    "assets/textures/ui-traps.png");
    mTextures.load(Textures::UiAmmo,        "assets/textures/ui-ammo.png");
    mTextures.load(Textures::Ammo,          "assets/textures/ammo.png");
    mTextures.load(Textures::TraplistHole,  "assets/textures/traplist-hole.png");
    mTextures.load(Textures::TraplistTnt,   "assets/textures/traplist-tnt.png");
    mTextures.load(Textures::TraplistBurger,"assets/textures/traplist-burger.png");
    mTextures.load(Textures::CarrotProjectile,"assets/textures/carrot.png");
    mTextures.load(Textures::Bubble,        "assets/textures/bubble.png");
}

void World::buildScene()
{
    // Initialize layers
    for(std::size_t i = 0; i < LayerCount; ++i)
    {
        Category::Type type = (i == (int)Entities) ? Category::EntityLayer : Category::None;

        SceneNode::Ptr layer(new SceneNode(type));
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    // Background
    std::unique_ptr<SpriteNode> background(new SpriteNode(mTextures.get(Textures::Background)));
    background->setScale(sf::Vector2f(2.f, 2.f));
    mSceneLayers[Background]->attachChild(std::move(background));


    // Tilemap
    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            std::unique_ptr<SpriteNode> tile(new SpriteNode(mTextures.get(Textures::Tile)));
            tile->setPosition(toIsoCoord(j, i));
            mSceneLayers[Tilemap]->attachChild(std::move(tile));
        }
    }


    // Camera
    std::unique_ptr<CameraNode> camera(new CameraNode(mWorldView));
    mSceneGraph.attachChild(std::move(camera));

    // Sounds
    std::unique_ptr<SoundNode> sound(new SoundNode(mSounds));
    mSceneLayers[Decorations]->attachChild(std::move(sound));

    // Help
    std::unique_ptr<HelpNode> help(new HelpNode(mTextures));
    mSceneGraph.attachChild(std::move(help));


    // Add the Traplist Node, that handle trap creation
    std::unique_ptr<TraplistNode> traplist(new TraplistNode(mTextures, mFonts));
    mSceneLayers[Entities]->attachChild(std::move(traplist));

    Command cmd;
    cmd.action = derivedAction<TraplistNode>([](TraplistNode& node, sf::Time dt) {
        node.generateTraps(5);
    });
    cmd.category = Category::Traplist;
    mCommandQueue.push(cmd);


    // Player
    std::unique_ptr<PlayerEntity> player(new PlayerEntity(mTextures));
    player->setPosition(toIsoCoord(1, 1));
    player->setGridPosition(sf::Vector2i(1, 1));
    mPlayer = player.get();

    std::unique_ptr<BubbleNode> bubble(new BubbleNode(mTextures, mFonts));
    mPlayer->setBubble(bubble.get());
    bubble->setString("KILL KIDS! EXTEMINATE!");
    player->attachChild(std::move(bubble));

    mSceneLayers[Entities]->attachChild(std::move(player));


    // Ennemies
    /*std::unique_ptr<BasicKidNode> kid(new BasicKidNode(mTextures));
    kid->setPosition(toIsoCoord(0, 0));
    kid->setGridPosition(sf::Vector2i(0, 0));
    mSceneLayers[Entities]->attachChild(std::move(kid));

    kid.reset(new BasicKidNode(mTextures));
    kid->setPosition(toIsoCoord(0, 2));
    kid->setGridPosition(sf::Vector2i(0, 2));
    mSceneLayers[Entities]->attachChild(std::move(kid));*/


    // Waves & Points
    std::unique_ptr<WaveGenerator> waves(new WaveGenerator(mTextures, mFonts, mMusic));
    waves->nextWave();
    mSceneLayers[Entities]->attachChild(std::move(waves));
}

void World::update(sf::Time dt)
{
    // Game logic here

    // Forward commands to scene
    while(!mCommandQueue.isEmpty())
    {
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);
    }

    // Collision detection and response (may destroy entities)
    handleCollisions();

    // Remove all destroyed entities, create new ones
    mSceneGraph.removeWrecks();
    mSounds.removeStoppedSounds();

    // Set the listener position

    mSceneGraph.update(dt, mCommandQueue);
}

void World::draw()
{
    mWindow.setView(mWorldView);

    /*sf::Sprite tilemap(mTileMap.getTexture());
    mWindow.draw(tilemap);*/


    mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}

/*************************************************/

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
    unsigned int category1 = colliders.first->getCategory();
    unsigned int category2 = colliders.second->getCategory();

    // Make sure first pair entry has category type1 and second has type2
    if (type1 & category1 && type2 & category2)
    {
        return true;
    }
    else if (type1 & category2 && type2 & category1)
    {
        std::swap(colliders.first, colliders.second);
        return true;
    }
    else
    {
        return false;
    }
}

void World::handleCollisions()
{
    std::set<SceneNode::Pair> collisionPairs;
    mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

    for(SceneNode::Pair pair : collisionPairs)
    {
        if (matchesCategories(pair, Category::Enemy, Category::Trap))
        {
            auto& kid = static_cast<Entity&>(*pair.first);
            auto& trap = static_cast<Entity&>(*pair.second);

            if(!kid.isCollidable())
                break;

            kid.destroy();
            trap.destroy();
            mSounds.play(Sounds::CarrotHit);
            mCommandQueue.push(mKidKilledCommand);
            if(randomInt(5) == 0)
            {
                mSounds.play(Sounds::Laugh);
                mPlayer->emote();
            }
        }
        else if (matchesCategories(pair, Category::Enemy, Category::Explosion))
        {
            auto& kid = static_cast<Entity&>(*pair.first);

            if(!kid.isCollidable())
                break;

            kid.destroy();
            mSounds.play(Sounds::CarrotHit);
            mCommandQueue.push(mKidKilledCommand);
            if(randomInt(2) == 0)
            {
                mSounds.play(Sounds::Laugh);
                mPlayer->emote();
            }
        }
        else if (matchesCategories(pair, Category::Trap, Category::Trap))
        {
            auto& trap = static_cast<Entity&>(*pair.first);

            trap.destroy();
        }
        else if (matchesCategories(pair, Category::Trap, Category::Explosion))
        {
            auto& trap = static_cast<Entity&>(*pair.first);

            trap.destroy();
        }
        else if (matchesCategories(pair, Category::Player, Category::Explosion))
        {
            auto& player = static_cast<Entity&>(*pair.first);

            mPlayer->bubble()->setString("Noooooooooooo!");
            player.destroy();
        }
        else if (matchesCategories(pair, Category::Player, Category::Enemy))
        {
            auto& player = static_cast<Entity&>(*pair.first);
            auto& kid = static_cast<Entity&>(*pair.second);

            if(!kid.isCollidable())
                break;

            mPlayer->bubble()->setString("Arrrrggg!");
            player.destroy();
        }
        else if (matchesCategories(pair, Category::FriendlyBullet, Category::Enemy))
        {
            auto& bullet = static_cast<Entity&>(*pair.first);
            auto& kid = static_cast<Entity&>(*pair.second);

            if(!kid.isCollidable())
                break;

            bullet.destroy();
            kid.destroy();

            mSounds.play(Sounds::CarrotHit);

            if(randomInt(3) == 0)
            {
                mSounds.play(Sounds::Laugh);
                mPlayer->emote();
            }

            mCommandQueue.push(mKidKilledCommand);
        }
        else if (matchesCategories(pair, Category::FriendlyBullet, Category::Trap))
        {
            auto& bullet = static_cast<Entity&>(*pair.first);
            auto trap = dynamic_cast<TntTrap*>(pair.second);

            if(trap) {
                bullet.destroy();
                trap->destroy();
            }

        }
    }
}

bool World::hasPlayerAlive()
{
    if(mPlayer)
        return !mPlayer->isDestroyed();

    return true;
}
