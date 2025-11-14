#pragma once

#include "core/actor.h"

class Player;

class Enemy : public Actor
{
public:
    void init() override;
    void handleEvents(SDL_Event& event) override;
    void update(float deltaTime) override;
    void render() override;
    void clean() override;

    void aimTarget(Player* target);

    Player* target() { return m_target; }
    void setTarget(Player* target) { m_target = target; }

private:
    Player* m_target{ nullptr };
};
