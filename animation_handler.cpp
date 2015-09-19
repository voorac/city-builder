#include "animation_handler.hpp"


Animation::Animation(unsigned int startFrame,
                     unsigned int endFrame,
                     float duration) : startFrame(startFrame),
                                       endFrame(endFrame),
                                       duration(duration)
{
}

unsigned int Animation::getLength()
{
    return endFrame - startFrame + 1;
}


AnimationHandler::AnimationHandler() : t(0.0f), currentAnim(-1)
{
}

AnimationHandler::AnimationHandler(const sf::IntRect& frameSize)
    : t(0.0f), currentAnim(-1), frameSize(frameSize)
{
}

void AnimationHandler::addAnim(Animation &anim)
{
    this->animations.push_back(anim);
}


void AnimationHandler::changeAnim(unsigned int animNum)
{
    this->t = 0.0f;
    this->currentAnim = animNum;
    sf::IntRect rect = this->frameSize;
    rect.top = rect.height * animNum;
    this->bounds = rect;
}

void AnimationHandler::update(const float dt)
{
    if (currentAnim < 0 || currentAnim >= animations.size()) {
        return;
    }
    auto duration = this->animations[currentAnim].duration;
    int lastFrame = t / duration;
    int currentFrame = (t + dt) / duration;
    if (currentFrame > lastFrame)
    {
        int frame = currentFrame % animations[currentAnim].getLength();
    
        sf::IntRect rect = this->frameSize;
        rect.left = rect.width * frame;
        rect.top = rect.height * currentAnim;
        this->bounds = rect;
    }
    this->t += dt;

    if (currentFrame > animations[currentAnim].getLength())
    {
        this->t = 0.0f;
    }
}
