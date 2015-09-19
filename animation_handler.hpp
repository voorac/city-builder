#ifndef ANIMATION_HANDLER_HPP
#define ANIMATION_HANDLER_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
public:
    unsigned int startFrame;
    unsigned int endFrame;
    float duration;

    Animation(unsigned int startFrame, unsigned int endFrame, float duration);

    unsigned int getLength();
};


class AnimationHandler
{
private:
    std::vector<Animation> animations;
    float t;
    int currentAnim;

public:
    sf::IntRect bounds;
    sf::IntRect frameSize;

    AnimationHandler();
    AnimationHandler(const sf::IntRect& frameSize);

    void addAnim(Animation& anim);
    void update(const float dt);
    void changeAnim(unsigned int animNum);
};

#endif // ANIMATION_HANDLER_HPP
