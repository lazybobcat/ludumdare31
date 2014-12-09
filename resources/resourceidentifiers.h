#ifndef RESOURCE_IDENTIFIERS_H
#define RESOURCE_IDENTIFIERS_H

// Forward declarations
namespace sf
{
    class Texture;
    class Font;
    class Shader;
    class Music;
    class SoundBuffer;
}

template <typename Resource, typename Identifier>
class ResourceHolder;



// Textures
namespace Textures
{
    enum ID
    {
        Help,
        Particle,
        Background,
        RabbitHead,
        RabbitRight,
        RabbitLeft,
        RabbitUp,
        RabbitDown,
        RabbitFiringRight,
        RabbitFiringLeft,
        RabbitFiringUp,
        RabbitFiringDown,
        RabbitDead,
        KidRight,
        KidLeft,
        KidUp,
        KidDown,
        KidFiringRight,
        KidFiringLeft,
        KidFiringUp,
        KidFiringDown,
        KidDead,
        Tile,
        TelegraphBlue,
        TelegraphRed,
        HoleStanding,
        HoleActive,
        Tnt,
        Burger,
        Explosion,
        UiTraplist,
        UiAmmo,
        Ammo,
        TraplistHole,
        TraplistTnt,
        TraplistBurger,
        CarrotProjectile,
        Bubble
    };
}

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;


// Fonts
namespace Fonts
{
    enum ID
    {
        Main,
        Title
    };
}

typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;


// Shaders
namespace Shaders
{
    enum ID
    {

    };
}
typedef ResourceHolder<sf::Shader, Shaders::ID> ShaderHolder;


// Musics
namespace Musics
{
    enum ID
    {
        TitleBackground,
        MainTheme
    };
}


// Sounds
namespace Sounds
{
    enum ID
    {
        Thunderish,
        Thundercomment,
        CarrotFire,
        CarrotHit,
        Explosion,
        Laugh,
        KidPop,
        KidWin,
        NewAmmo,
        RockShot,
        SetTrap,
        Slurp,
        Tick,
        NextWave
    };
}
typedef ResourceHolder<sf::SoundBuffer, Sounds::ID> SoundHolder;


// Scripts
namespace Scripts
{
    enum ID
    {
        HelloWorld
    };
}



#endif // RESOURCE_IDENTIFIERS_H
