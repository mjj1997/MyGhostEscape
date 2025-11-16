#include "scene_main.h"
#include "enemy.h"
#include "player.h"

void SceneMain::init()
{
    m_worldSize = m_game.screenSize() * 3.0f;                           // 世界大小为屏幕大小的3倍
    m_cameraPosition = m_worldSize / 2.0f - m_game.screenSize() / 2.0f; // 初始相机位置

    m_player = new Player;
    m_player->init();
    m_player->setWorldPosition(m_worldSize / 2.0f);
    addChild(m_player);

    m_enemy = new Enemy;
    m_enemy->init();
    m_enemy->setTarget(m_player);
    m_enemy->setWorldPosition(m_worldSize / 2.0f + glm::vec2{ 100.0f });
    addChild(m_enemy);
}

void SceneMain::handleEvents(SDL_Event& event)
{
    Scene::handleEvents(event);
}

void SceneMain::update(float deltaTime)
{
    Scene::update(deltaTime);
}

void SceneMain::render()
{
    renderBackground();
    Scene::render();
}

void SceneMain::clean()
{
    Scene::clean();
}

void SceneMain::renderBackground()
{
    auto start{ glm::vec2{ 0.0f } - m_cameraPosition };
    auto end{ m_worldSize - m_cameraPosition };
    m_game.drawGrid(start, end, 80.0f, SDL_FColor{ 0.5f, 0.5f, 0.5f, 1.0f });
    m_game.drawBoundary(start, end, 5.0f, SDL_FColor{ 1.0f, 1.0f, 1.0f, 1.0f });
}
