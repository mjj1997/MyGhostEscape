#include "object_in_world.h"
#include "scene.h"

void ObjectInWorld::setScreenPosition(const glm::vec2& position)
{
    m_screenPosition = position;
    m_worldPosition = m_game.currentScene()->screen2World(position);
}

void ObjectInWorld::setWorldPosition(const glm::vec2& position)
{
    m_worldPosition = position;
    m_screenPosition = m_game.currentScene()->world2Screen(position);
}
