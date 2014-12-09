#include <utils.h>
#include <random>
#include <ctime>

namespace
{
    std::default_random_engine createRandomEngine()
    {
        auto seed = static_cast<unsigned long>(std::time(nullptr));
        return std::default_random_engine(seed);
    }

    auto RandomEngine = createRandomEngine();
}

/////////////////////////////

void centerOrigin(sf::Sprite &sprite)
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::Text& text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(Animation& animation)
{
    sf::FloatRect bounds = animation.getLocalBounds();
    animation.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}


/////////////////////////////

sf::Vector2f toIsoCoord(int x, int y)
{
    float tileW = 120.f, offsetX = 1280/2.f + 130.f;
    float tileH = 60.f,  offsetY = 200.f;
    float isoX = (x - y) * (tileW / 2.f) - tileW/2 + offsetX;
    float isoY = (x + y) * (tileH / 2.f) + offsetY;
    return sf::Vector2f(isoX, isoY);
}


/////////////////////////////

int randomInt(int exclusiveMax)
{
    std::uniform_int_distribution<> distr(0, exclusiveMax - 1);
    return distr(RandomEngine);
}

float randomFloat(float min, float max)
{
    std::uniform_real_distribution<float> distr(min, max);
    return distr(RandomEngine);
}
