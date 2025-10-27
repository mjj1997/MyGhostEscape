#include "scene_main.h"

void SceneMain::init()
{
    m_worldSize = m_game.screenSize() * 3.0f; // 世界大小为屏幕大小的3倍
    m_cameraPosition = glm::vec2{ -100.0f };  // 初始相机位置
}

void SceneMain::handleEvents(SDL_Event& event) {}

void SceneMain::update(float deltaTime)
{
    m_cameraPosition += glm::vec2{ 10.0f, 10.0f } * deltaTime;
}

void SceneMain::render()
{
    renderBackground();
}

void SceneMain::clean() {}

void SceneMain::renderBackground()
{
    auto start{ glm::vec2{ 0.0f } - m_cameraPosition };
    auto end{ m_worldSize - m_cameraPosition };
    m_game.drawGrid(start, end, 80.0f, SDL_FColor{ 0.5f, 0.5f, 0.5f, 1.0f });
    m_game.drawBoundary(start, end, 5.0f, SDL_FColor{ 1.0f, 1.0f, 1.0f, 1.0f });
}
