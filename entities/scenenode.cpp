#include <entities/scenenode.h>
#include <entities/soundnode.h>
#include <resources/resourceidentifiers.h>

struct sort_by_y_axis
{
    inline bool operator() (const SceneNode::Ptr& ptr1, const SceneNode::Ptr& ptr2)
    {
        return ptr1->getPosition().y < ptr2->getPosition().y;
    }
};

//////////////////////////////////////////////////////////////////////////

SceneNode::SceneNode(Category::Type category) :
    mChildren(),
    mParent(nullptr),
    mDefaultCategory(category),
    mGridPosition(0, 0)
{
}


void SceneNode::attachChild(Ptr child)
{
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode &node)
{
    auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr& p) -> bool {
        return p.get() == &node;
    });

    assert(found != mChildren.end());

    Ptr result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found);
    return result;
}

void SceneNode::playLocalSound(CommandQueue &commands, Sounds::ID sound)
{
    Command command;
    command.category = Category::SoundEffect;
    command.action = derivedAction<SoundNode>(std::bind(&SoundNode::playSound, std::placeholders::_1, sound, getWorldPosition()));

    commands.push(command);
}

void SceneNode::update(sf::Time dt, CommandQueue &commands)
{
    updateCurrent(dt, commands);
    updateChildren(dt, commands);
}

void SceneNode::updateCurrent(sf::Time /*dt*/, CommandQueue &/*commands*/)
{
    // Sort children by Y axis
    std::sort(mChildren.begin(), mChildren.end(), sort_by_y_axis());

}

void SceneNode::updateChildren(sf::Time dt, CommandQueue &commands)
{
    for(Ptr& child : mChildren)
    {
        child->update(dt, commands);
    }
}

sf::Transform SceneNode::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;

    for(const SceneNode* node = this; node != nullptr; node = node->mParent)
    {
        transform = node->getTransform() * transform;
    }

    return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

sf::FloatRect SceneNode::getBoundingRect() const
{
    return sf::FloatRect();
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    drawCurrent(target, states);
    drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget &/*target*/, sf::RenderStates /*states*/) const
{

}

void SceneNode::drawChildren(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(const Ptr& child : mChildren)
    {
        child->draw(target, states);
    }
}

unsigned int SceneNode::getCategory() const
{
    return mDefaultCategory;
}

bool SceneNode::isCollidable()
{
    return false;
}

void SceneNode::onCommand(const Command &command, sf::Time dt)
{
    if(command.category & getCategory())
    {
        command.action(*this, dt);
    }

    for(Ptr& child : mChildren)
    {
        child->onCommand(command, dt);
    }
}

void SceneNode::checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs)
{
    checkNodeCollision(sceneGraph, collisionPairs);

    for(Ptr& child : sceneGraph.mChildren)
        checkSceneCollision(*child, collisionPairs);
}

void SceneNode::checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs)
{
    if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
        collisionPairs.insert(std::minmax(this, &node));

    for(Ptr& child : mChildren)
        child->checkNodeCollision(node, collisionPairs);
}

void SceneNode::removeWrecks()
{
    // Remove all children which request so
    auto wreckfieldBegin = std::remove_if (mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
    mChildren.erase(wreckfieldBegin, mChildren.end());

    // Call function recursively for all remaining children
    std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::removeWrecks));
}

/////////////////////////////////////////////////////////////

bool collision(const SceneNode& lhs, const SceneNode& rhs)
{
    return lhs.gridPosition() == rhs.gridPosition();
}
