#ifndef AMMONODE_HPP
#define AMMONODE_HPP

#include <entities/scenenode.h>
#include <resources/resourceholder.h>
#include <resources/resourceidentifiers.h>
#include <array>

class AmmoNode : public SceneNode
{
public:
    AmmoNode(TextureHolder& textures);


    bool    canShot() const;
    void    consumeAmmo();

private:
    virtual void    updateCurrent(sf::Time dt, CommandQueue &commands);
    virtual void    drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    std::size_t     mMaxAmmo;
    std::size_t     mCurrentAmmo;
    sf::Time        mReloadTime;

    sf::Sprite      mUi;
    sf::Sprite      mAmmo;
    sf::Sprite      mAmmoMissing;
    std::array<sf::Sprite, 5> mAmmos;
};

#endif // AMMONODE_HPP
