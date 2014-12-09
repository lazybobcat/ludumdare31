#ifndef WORLD_H
#define WORLD_H

#include <array>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <resources/resourceholder.h>
#include <resources/resourceidentifiers.h>
#include <resources/musicplayer.h>
#include <resources/soundplayer.h>
#include <resources/scriptplayer.h>
#include <controllers/playercontroller.h>
#include <events/category.h>
#include <events/commandqueue.h>
#include <entities/spritenode.h>
#include <entities/playerentity.h>

class World : public sf::NonCopyable
{
public:
    World(sf::RenderWindow& window, TextureHolder &textures, FontHolder &fonts, MusicPlayer &music, SoundPlayer &sounds, ScriptPlayer &scripts, PlayerController &player);

    void        update(sf::Time dt);
    void        draw();

    CommandQueue&   getCommandQueue();

    void        handleCollisions();

    bool        hasPlayerAlive();

private:
    void        loadTextures();
    void        buildScene();

private:
    enum Layer
    {
        Background,
        Tilemap,
        Decorations,
        Telegraphs,
        Entities,
        LayerCount
    };

private:
    sf::RenderWindow&                   mWindow;
    sf::View                            mWorldView;
    TextureHolder&                      mTextures;
    FontHolder&                         mFonts;
    MusicPlayer&                        mMusic;
    SoundPlayer&                        mSounds;
    ScriptPlayer&                       mScripts;
    PlayerEntity*                       mPlayer;

    SceneNode                           mSceneGraph;
    std::array<SceneNode*,LayerCount>   mSceneLayers;
    CommandQueue                        mCommandQueue;

    Command                             mKidKilledCommand;

    // Player
};

#endif // WORLD_H
