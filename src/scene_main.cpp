#include "scene_main.h"
#include "player.h"

void SceneMain::init()
{
    m_worldSize = m_game.screenSize() * 3.0f; // 世界大小为屏幕大小的3倍
    m_cameraPosition = glm::vec2{ -100.0f };  // 初始相机位置
    m_player = new Player;
    m_player->init();
    m_player->setWorldPosition(m_worldSize / 2.0f);
}

void SceneMain::handleEvents(SDL_Event& event) {}

void SceneMain::update(float deltaTime)
{
    m_player->update(deltaTime);
}

void SceneMain::render()
{
    renderBackground();
    m_player->render();
}

void SceneMain::clean()
{
    if (m_player != nullptr) {
        m_player->clean();
        delete m_player;
    }
}

void SceneMain::renderBackground()
{
    auto start{ glm::vec2{ 0.0f } - m_cameraPosition };
    auto end{ m_worldSize - m_cameraPosition };
    m_game.drawGrid(start, end, 80.0f, SDL_FColor{ 0.5f, 0.5f, 0.5f, 1.0f });
    m_game.drawBoundary(start, end, 5.0f, SDL_FColor{ 1.0f, 1.0f, 1.0f, 1.0f });
}
