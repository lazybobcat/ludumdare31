#include <entities/cameranode.h>

CameraNode::CameraNode(sf::View &camera) :
    SceneNode(Category::Camera),
    mCamera(camera),
    mOriginalCenter(camera.getCenter()),
    mShaking(false),
    mShakingDuration(sf::Time::Zero),
    mShakingET(sf::Time::Zero)
{
}

void CameraNode::shake(sf::Time duration)
{
    mShaking = true;
    mShakingDuration = duration;
    mShakingET = sf::Time::Zero;
}

void CameraNode::updateCurrent(sf::Time dt, CommandQueue &/*commands*/)
{
    if(mShaking)
    {
        mShakingET += dt;

        mCamera.setCenter(mOriginalCenter);
        mCamera.move(sf::Vector2f(0.f, randomFloat(-300.f, 300.f)*dt.asSeconds()));

        if(mShakingET >= mShakingDuration)
        {
            mShaking = false;
            mCamera.setCenter(mOriginalCenter);
        }
    }
}
