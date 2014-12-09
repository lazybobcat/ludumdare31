#include <entities/wavegenerator.h>
#include <entities/basickidnode.h>
#include <entities/traplistnode.h>
#include <world.h>

#include <iostream>

namespace
{
    const std::vector<Wave> WaveTable = initializeWaves();
}

WaveGenerator::WaveGenerator(TextureHolder& textures, FontHolder &fonts, MusicPlayer &musics) :
    SceneNode(Category::WaveGenerator),
    mTextures(textures),
    mMusicPlayer(musics),
    mCurrentWaveIndex(-1),
    mCurrentWaveNumber(-1),
    mPoints(0),
    mKidsRemaining(0),
    mWaveState(Paused),
    mWaveTimer(sf::Time::Zero),
    mNbKidPoped(0),
    mGaveTraps(false)
{
    mDisplay.setFont(fonts.get(Fonts::Main));
    mDisplay.setString("0 points - Wave 0");
    centerOrigin(mDisplay);
    mDisplay.setPosition(1280.f / 2 + 150.f, 16.f);

    mWaves = WaveTable;
}


void WaveGenerator::kidKilled()
{
    mPoints += 1;
    if(mKidsRemaining > 0) mKidsRemaining -= 1;

    refreshDisplay();
}

void WaveGenerator::nextWave()
{
    // Bonus Points
    if(mCurrentWaveIndex > 0 && mCurrentWaveIndex != -1)
    {
        if(mKidsRemaining == 0)
        {
            mPoints += (int)(mWaves[mCurrentWaveIndex].kidsToKill * 1.25f);
        }
    }

    if(mCurrentWaveIndex+1 < mWaves.size())
        mCurrentWaveIndex++;
    mCurrentWaveNumber++;

    mWaveState = WaitInitTime;
    mWaveTimer = sf::Time::Zero;
    mNbKidPoped = 0;
    mKidsRemaining += mWaves[mCurrentWaveIndex].kidsToKill;
    mGaveTraps = false;

    refreshDisplay();
}

void WaveGenerator::updateCurrent(sf::Time dt, CommandQueue &commands)
{
    mWaveTimer += dt;

    switch(mWaveState)
    {
        case WaitInitTime:
        {
            if(!mGaveTraps)
            {
                Command cmd;
                cmd.category = Category::Traplist;
                cmd.action = derivedAction<TraplistNode>([&](TraplistNode& traps, sf::Time dt) {
                    if(mCurrentWaveIndex == 0)
                        traps.generateTraps(5);
                    else if(mCurrentWaveIndex == 1)
                        traps.generateTraps(mWaves[mCurrentWaveIndex].nbTraps);
                    else
                        traps.grantTrap(mWaves[mCurrentWaveIndex].nbTraps);
                });
                commands.push(cmd);

                // New Wave sound
                playLocalSound(commands, Sounds::NextWave);

                mGaveTraps = true;
            }

            if(mWaveTimer >= mWaves[mCurrentWaveIndex].initialWaitTime)
            {
                mWaveState = PopingAdds;
                mWaveTimer = sf::Time::Zero;

                if(mWaves[mCurrentWaveIndex].kidsToKill == 0)
                    mWaveState = WaitingTheEnd;
            }
        }
            break;

        case PopingAdds:
            if(mWaveTimer >= mWaves[mCurrentWaveIndex].repopTime)
            {
                popKid(commands, mWaves[mCurrentWaveIndex].minIntel, mWaves[mCurrentWaveIndex].kidSpeed);
                mWaveTimer = sf::Time::Zero;


                if(mNbKidPoped >= mWaves[mCurrentWaveIndex].kidsToKill)
                {
                    mWaveState = WaitingTheEnd;
                    mWaveTimer = sf::Time::Zero;
                }
            }
            break;

        case WaitingTheEnd:
            if(mKidsRemaining == 0 || mWaveTimer >= mWaves[mCurrentWaveIndex].waveTotalTime)
            {
                nextWave();
            }

        default:break;
    }
}

void WaveGenerator::popKid(CommandQueue& commands, int minIntel, float speed)
{
    Command cmd;
    cmd.category = Category::EntityLayer;
    cmd.action = [&,speed](SceneNode& node, sf::Time dt) {
        std::unique_ptr<BasicKidNode> kid(new BasicKidNode(mTextures, speed));
        if(randomInt(2) == 0)
        {
            int y = randomInt(8);
            kid->setPosition(toIsoCoord(0, y));
            kid->setGridPosition(sf::Vector2i(0, y));
        }
        else
        {
            int x = randomInt(7)+1;
            kid->setPosition(toIsoCoord(x, 0));
            kid->setGridPosition(sf::Vector2i(x, 0));
        }
        node.attachChild(std::move(kid));
    };
    commands.push(cmd);

    mNbKidPoped++;
}


void WaveGenerator::refreshDisplay()
{
    mDisplay.setString(toString(mPoints) + " points - Wave " + toString(mCurrentWaveNumber));
    centerOrigin(mDisplay);
}


void WaveGenerator::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mDisplay, states);
}
