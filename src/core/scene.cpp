#include "scene.h"

void Scene::setCameraPosition(const glm::vec2& cameraPosition)
{
    m_cameraPosition = cameraPosition;
    m_cameraPosition = glm::clamp(m_cameraPosition,
                                  glm::vec2{ -30.0f },
                                  m_worldSize - m_game.screenSize() + glm::vec2{ 30.0f });
}
