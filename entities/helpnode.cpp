#include <entities/helpnode.h>

HelpNode::HelpNode(TextureHolder &textures) :
    SceneNode(Category::None),
    mFakePosition(152.f, -2.f)
{
    mSprite.setTexture(textures.get(Textures::Help));
    mSprite.setPosition(150.f, 55.f);
}
