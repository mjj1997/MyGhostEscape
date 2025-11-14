#pragma once

#include "core/scene.h"

class Player;
class Enemy;

class SceneMain : public Scene
{
public:
    SceneMain() = default;
    virtual ~SceneMain() override = default;

    void init() override;
    void handleEvents(SDL_Event& event) override;
    void update(float deltaTime) override;
    void render() override;
    void clean() override;

private:
    void renderBackground();

    Player* m_player{ nullptr };
    Enemy* m_enemy{ nullptr };
};
