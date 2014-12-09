#include <states/gameoverstate.h>
#include <utils.h>

GameOverState::GameOverState(StateStack &stack, Context context) :
    State(stack, context)
{
    mText.setFont(context.fonts->get(Fonts::Main));
    mText.setString("Game Over!");
    mText.setCharacterSize(80);
    centerOrigin(mText);
    mText.setPosition(context.window->getSize().x / 2.f, context.window->getSize().y / 2.f);
}

void GameOverState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    sf::RectangleShape back;
    back.setFillColor(sf::Color(0,0,0, 200));
    back.setSize(window.getView().getSize());
    back.setPosition(0.f, 60.f);

    window.draw(back);

    window.draw(mText);
}


bool GameOverState::update(sf::Time /*dt*/)
{
    return false;
}


bool GameOverState::handleEvent(const sf::Event &event)
{
    //CommandQueue& commands = mWorld.getCommandQueue();

    // If ESC/Q key is pressed : leave
    if (event.type == sf::Event::KeyReleased)
    {
        switch(event.key.code)
        {
            case sf::Keyboard::Escape:
            case sf::Keyboard::Q:
                requestStackClear();
                break;
        }
    }

    return false;
}
