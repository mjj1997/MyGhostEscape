#pragma once

#include "core/scene.h"

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

    glm::vec2 m_worldSize{ glm::vec2{ 0.0f } }; // 世界大小
};
