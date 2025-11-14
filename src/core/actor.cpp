#include "actor.h"
#include "scene.h"

void Actor::move(float deltaTime)
{
    setWorldPosition(m_worldPosition + m_velocity * deltaTime);
    m_worldPosition = glm::clamp(m_worldPosition,
                                 glm::vec2{ 0.0f },
                                 m_game.currentScene()->worldSize());
}
