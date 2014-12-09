#ifndef WAVEGENERATOR_H
#define WAVEGENERATOR_H

#include <entities/scenenode.h>
#include <resources/resourceholder.h>
#include <resources/resourceidentifiers.h>
#include <resources/musicplayer.h>
#include <utils.h>
#include <datatables.h>
#include <vector>

class World;

class WaveGenerator : public SceneNode
{
public:
    friend class World;

    enum State
    {
        Paused,
        WaitInitTime,
        PopingAdds,
        WaitingTheEnd
    };

public:
    WaveGenerator(TextureHolder &textures, FontHolder& fonts, MusicPlayer& musics);

    void    kidKilled();

    void    popKid(CommandQueue &commands, int minIntel, float speed);

private:
    virtual void    updateCurrent(sf::Time dt, CommandQueue &commands);
    virtual void    drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

    void    nextWave();
    void    refreshDisplay();

private:
    TextureHolder&          mTextures;
    MusicPlayer&            mMusicPlayer;
    std::vector<Wave>       mWaves;
    std::size_t             mCurrentWaveIndex;
    std::size_t             mCurrentWaveNumber;
    unsigned int            mPoints;
    unsigned int            mKidsRemaining;

    // State
    State                   mWaveState;
    sf::Time                mWaveTimer;
    unsigned int            mNbKidPoped;

    sf::Text                mDisplay;

    bool                    mGaveTraps;
};

#endif // WAVEGENERATOR_H
