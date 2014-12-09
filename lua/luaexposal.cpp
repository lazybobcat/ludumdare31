#include <lua/luaexposal.h>
#include <SFML/System/Vector2.hpp>
#include <entities/entity.h>


void exposeVector()
{
    SLB::Class<sf::Vector2f>("Vector2f")
            .constructor<float, float>()
            .property("x", &sf::Vector2f::x)
            .property("y", &sf::Vector2f::y);
}

void exposeSceneNode()
{
    SLB::Class<SceneNode, SLB::Instance::NoCopy>("SceneNode")
            .constructor<Category::Type>()
            .set("getWorldPosition", &SceneNode::getWorldPosition);
}

void exposeEntity()
{

}


void exposeToLua()
{
    exposeVector();
    exposeSceneNode();
    exposeEntity();
}
