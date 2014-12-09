#ifndef CAMERANODE_H
#define CAMERANODE_H

#include <entities/scenenode.h>
#include <utils.h>

class CameraNode : public SceneNode
{
public:
    CameraNode(sf::View& camera);

    void    shake(sf::Time duration);

private:
    virtual void    updateCurrent(sf::Time dt, CommandQueue &commands);

private:
    sf::View&   mCamera;
    sf::Vector2f mOriginalCenter;

    bool        mShaking;
    sf::Time    mShakingDuration;
    sf::Time    mShakingET;
};

#endif // CAMERANODE_H
