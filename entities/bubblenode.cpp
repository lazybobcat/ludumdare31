#include <entities/bubblenode.h>
#include <utils.h>

BubbleNode::BubbleNode(TextureHolder &textures, FontHolder &fonts) :
    SceneNode(),
    mShow(false),
    mTimer(sf::Time::Zero)
{
    mSprite.setTexture(textures.get(Textures::Bubble));
    centerOrigin(mSprite);

    mText.setFont(fonts.get(Fonts::Main));
    mText.setCharacterSize(24);
    mText.setString("Hello World!");
    mText.setColor(sf::Color::Black);
    centerOrigin(mText);
    mText.setPosition(0.f, -5.f);

    setPosition(70.f, -80.f);
}

void BubbleNode::setString(const std::string &str)
{
    mText.setString(str);
    centerOrigin(mText);

    mShow = true;
    mTimer = sf::Time::Zero;
}
