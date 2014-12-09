#include <resources/musicplayer.h>

MusicPlayer::MusicPlayer() :
    mMusic(),
    mFilenames(),
    mVolume(100.f)
{
    // Fill mFilenames table here :
    mFilenames[Musics::TitleBackground] = "assets/musics/titlebackground.ogg";
    mFilenames[Musics::MainTheme] = "assets/musics/maintheme.ogg";
}

void MusicPlayer::play(Musics::ID song)
{
    std::string filename = mFilenames[song];

    if (!mMusic.openFromFile(filename))
        throw std::runtime_error("Music " + filename + " could not be loaded.");

    mMusic.setVolume(mVolume);
    mMusic.setPitch(1.f);
    mMusic.setLoop(true);
    mMusic.play();
}

void MusicPlayer::stop()
{
    mMusic.stop();
}

void MusicPlayer::setVolume(float volume)
{
    mVolume = volume;
    mMusic.setVolume(volume);
}

void MusicPlayer::setSpeed(float speed)
{
    mMusic.setPitch(speed);
}

void MusicPlayer::pause(bool flag)
{
    if (flag)
        mMusic.pause();
    else
        mMusic.play();
}
