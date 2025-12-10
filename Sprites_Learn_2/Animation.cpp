#include "Animation.h"


void PlayerAnim::addAnimation(const std::string& key, const Animation& anim) {
    animations[key] = anim;
}

void PlayerAnim::play(const std::string& key) {
    if (key != currentKey) {
        currentKey = key;
        currentFrameIndex = 0;
        elapsedTime = 0.0f;
        finished = false;
    }
}

void PlayerAnim::update(float deltaTime) {
    if (animations.find(currentKey) == animations.end()) return;

    const Animation& anim = animations[currentKey];
    if (finished) return;

    elapsedTime += deltaTime;

    if (elapsedTime >= anim.framesDuration) {
        elapsedTime -= anim.framesDuration;
        currentFrameIndex++;

        if (currentFrameIndex >= anim.framesCount) {
            if (anim.animLooping) {
                currentFrameIndex = 0;
            }
            else {
                currentFrameIndex = anim.framesCount - 1;
                finished = true;
            }
        }
    }
}

int PlayerAnim::getCurrentFrame() const {
    if (animations.find(currentKey) == animations.end()) return 0;

    const Animation& anim = animations.at(currentKey);
    return anim.startingFrame + currentFrameIndex;
}

bool PlayerAnim::isFinished() const {
    return finished;
}
