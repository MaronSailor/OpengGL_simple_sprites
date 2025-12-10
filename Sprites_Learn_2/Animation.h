#pragma once

#include <unordered_map>
#include <string>

struct Animation {
    int startingFrame;       // Linear frame index in the sprite sheet (row * columns + col)
    int framesCount;
    float framesDuration;
    bool animLooping;

    Animation() = default;
    Animation(int Start, int Count, float Duration, bool Looping)
        : startingFrame(Start), framesCount(Count), framesDuration(Duration), animLooping(Looping) {
    }
};


class PlayerAnim {
public:
    void addAnimation(const std::string& key, const Animation& anim);
    void play(const std::string& key);
    void update(float deltaTime);
    int getCurrentFrame() const;
    bool isFinished() const;

private:
    std::unordered_map<std::string, Animation> animations;
    std::string currentKey;

    int currentFrameIndex = 0;
    float elapsedTime = 0.0f;
    bool finished = false;
};
