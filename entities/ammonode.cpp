#include <entities/ammonode.h>

#include <iostream>

AmmoNode::AmmoNode(TextureHolder &textures) :
    SceneNode(Category::None),
    mMaxAmmo(5),
    mCurrentAmmo(0),
    mReloadTime(sf::Time::Zero)
{
    mUi.setTexture(textures.get(Textures::UiAmmo));
    mUi.setPosition(sf::Vector2f(1280.f - mUi.getLocalBounds().width, 0.f));

    mAmmo.setTexture(textures.get(Textures::Ammo));
    mAmmo.setTextureRect(sf::IntRect(0, 0, 15, 15));
    mAmmo.setScale(sf::Vector2f(2.f, 2.f));
    mAmmoMissing.setTexture(textures.get(Textures::Ammo));
    mAmmoMissing.setTextureRect(sf::IntRect(15, 0, 15, 15));
    mAmmoMissing.setScale(sf::Vector2f(2.f, 2.f));

    for(int i = 0; i < 5; ++i)
    {
        mAmmos[i] = mAmmoMissing;
        mAmmos[i].setPosition(mUi.getPosition().x + i * 28.f + 7.f, 3.f);
    }
}



bool AmmoNode::canShot() const
{
    return mCurrentAmmo > 0;
}


void AmmoNode::consumeAmmo()
{
    if(mCurrentAmmo > 0)
        mCurrentAmmo--;

    int i = 0;
    for(; i < mCurrentAmmo; ++i)
    {
        mAmmos[i] = mAmmo;
        mAmmos[i].setPosition(mUi.getPosition().x + i * 28.f + 7.f, 3.f);
    }
    for(; i < mMaxAmmo; ++i)
    {
        mAmmos[i] = mAmmoMissing;
        mAmmos[i].setPosition(mUi.getPosition().x + i * 28.f + 7.f, 3.f);
    }
}

void AmmoNode::updateCurrent(sf::Time dt, CommandQueue &commands)
{
    mReloadTime += dt;

    if(mReloadTime >= sf::seconds(10.f))
    {
        mReloadTime = sf::Time::Zero;
        if(mCurrentAmmo < mMaxAmmo)
        {
            mCurrentAmmo++;
            playLocalSound(commands, Sounds::NewAmmo);
        }

        int i = 0;
        for(; i < mCurrentAmmo; ++i)
        {
            mAmmos[i] = mAmmo;
            mAmmos[i].setPosition(mUi.getPosition().x + i * 28.f + 7.f, 3.f);
        }
        for(; i < mMaxAmmo; ++i)
        {
            mAmmos[i] = mAmmoMissing;
            mAmmos[i].setPosition(mUi.getPosition().x + i * 28.f + 7.f, 3.f);
        }
    }
}

void AmmoNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mUi, states);

    for(int i = 0; i < 5; ++i)
    {
        target.draw(mAmmos[i], states);
    }
}
