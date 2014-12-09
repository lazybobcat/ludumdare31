#include <states/titlestate.h>
#include <utils.h>

#include <iostream>

TitleState::TitleState(StateStack &stack, Context context) :
    State(stack, context),
    mText(),
    mShowText(false),
    mShowPresentsText(true),
    mLightning(false),
    mTextEffectTime(sf::Time::Zero),
    mLightningCount(0)
{
    mScreen.setSize(context.window->getView().getSize() * 1.f);
    mScreen.setFillColor(sf::Color::White);

    mPresentsText.setFont(context.fonts->get(Fonts::Main));
    mPresentsText.setString("MONSTRUOSOR GAMES PRESENTS...");
    centerOrigin(mPresentsText);
    mPresentsText.setPosition(sf::Vector2f(context.window->getView().getSize().x / 2.f, context.window->getView().getSize().y / 2.f));

    mText.setFont(context.fonts->get(Fonts::Main));
    mText.setCharacterSize(80);
    mText.setColor(sf::Color::Black);
    mText.setString("Dark Rabbit");
    centerOrigin(mText);
    mText.setPosition(sf::Vector2f(context.window->getView().getSize().x / 2.f, 250.f));

    mRabbitHead.setTexture(context.textures->get(Textures::RabbitHead));
    mRabbitHead.setOrigin(mRabbitHead.getLocalBounds().width / 2.f, mRabbitHead.getLocalBounds().height);
    mRabbitHead.setPosition(sf::Vector2f(context.window->getView().getSize().x / 2.f, context.window->getView().getSize().y));


    // Music !
    context.music->play(Musics::MainTheme);
    context.music->setVolume(10.f);
}


void TitleState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    if(mShowPresentsText)
        window.draw(mPresentsText);

    if(mShowText && mLightning)
    {
        window.draw(mScreen);

        window.draw(mText);
        window.draw(mRabbitHead);
    }
}

bool TitleState::update(sf::Time dt)
{
    mTextEffectTime += dt;
    mNextScreenTime += dt;

    if(mNextScreenTime >= sf::seconds(6.f))
    {
        requestStackClear();
        requestStackPush(States::Game);
    }

    if(mTextEffectTime >= sf::seconds(2.3f))
        return true;

    if(mTextEffectTime >= sf::seconds(2.f))
    {
        mShowText = true;
        mShowPresentsText = false;
        mLightningTime += dt;
        if(mLightningTime >= sf::seconds(0.15f))
        {
            mLightning = false;
            mLightningTime = sf::Time::Zero;
            mLightningCount++;
            if(mLightningCount >= 4)
            {
                //mTextEffectTime = sf::Time::Zero;
                mLightningCount = 0;
            }
        }
        else if(mLightningTime >= sf::seconds(0.1f))
        {
            mLightning = true;
        }
        else
        {
            mLightning = false;
        }
    }

    return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
    // If any key is pressed, we leave
    if (event.type == sf::Event::KeyReleased)
    {
        requestStackClear();
        requestStackPush(States::Game);
    }

    return true;
}
