#pragma once

#include "core/actor.h"

class SpriteAnime;

class Player : public Actor
{
public:
    enum class State { Idle, Moving };

    void init() override;
    void handleEvents(SDL_Event& event) override;
    void update(float deltaTime) override;
    void render() override;
    void clean() override;

    void keyboardControl();
    void move(float deltaTime);
    void syncCamera();
    void checkState();
    void changeState(State state);

private:
    SpriteAnime* m_spriteIdle{ nullptr };
    SpriteAnime* m_spriteMove{ nullptr };

    State m_curentState{ State::Idle };
};
