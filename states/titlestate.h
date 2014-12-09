#ifndef TITLESTATE_H
#define TITLESTATE_H

#include <SFML/Graphics.hpp>

#include <states/state.h>

class TitleState : public State
{
public:
    TitleState(StateStack& stack, Context context);
    virtual void        draw();
    virtual bool        update(sf::Time dt);
    virtual bool        handleEvent(const sf::Event &event);

private:
    sf::Text            mText;
    sf::Text            mPresentsText;
    sf::Sprite          mRabbitHead;
    sf::RectangleShape  mScreen;

    bool                mShowText;
    bool                mShowPresentsText;
    bool                mLightning;
    sf::Time            mTextEffectTime;
    sf::Time            mLightningTime;
    int                 mLightningCount;

    sf::Time            mNextScreenTime;
};

#endif // TITLESTATE_H
