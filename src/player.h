#pragma once

#include "core/actor.h"

class Player : public Actor
{
public:
    void init() override;
    void handleEvents(SDL_Event& event) override;
    void update(float deltaTime) override;
    void render() override;
    void clean() override;

    void keyboardControl();
};
