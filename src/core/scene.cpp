#include "scene.h"

void Scene::handleEvents(SDL_Event& event)
{
    Object::handleEvents(event);

    for (const auto& child : m_childrenInScreen)
        if (child->isActive())
            child->handleEvents(event);

    for (const auto& child : m_childrenInWorld)
        if (child->isActive())
            child->handleEvents(event);
}

void Scene::update(float deltaTime)
{
    Object::update(deltaTime);

    for (const auto& child : m_childrenInWorld)
        if (child->isActive())
            child->update(deltaTime);

    for (const auto& child : m_childrenInScreen)
        if (child->isActive())
            child->update(deltaTime);
}

void Scene::render()
{
    Object::render();

    for (const auto& child : m_childrenInWorld)
        if (child->isActive())
            child->render();

    for (const auto& child : m_childrenInScreen)
        if (child->isActive())
            child->render();
}

void Scene::clean()
{
    Object::clean();

    for (const auto& child : m_childrenInScreen) {
        child->clean();
        delete child;
    }
    m_childrenInScreen.clear();

    for (const auto& child : m_childrenInWorld) {
        child->clean();
        delete child;
    }
    m_childrenInWorld.clear();
}

void Scene::addChild(Object* child)
{
    switch (child->type()) {
    case ObjectType::World:
        m_childrenInWorld.push_back(static_cast<ObjectInWorld*>(child));
        break;
    case ObjectType::Screen:
        m_childrenInScreen.push_back(static_cast<ObjectInScreen*>(child));
        break;
    default:
        m_children.push_back(child);
        break;
    }
}

void Scene::removeChild(Object* child)
{
    switch (child->type()) {
    case ObjectType::World:
        m_childrenInWorld.erase(std::remove(m_childrenInWorld.begin(),
                                            m_childrenInWorld.end(),
                                            static_cast<ObjectInWorld*>(child)),
                                m_childrenInWorld.end());
        break;
    case ObjectType::Screen:
        m_childrenInScreen.erase(std::remove(m_childrenInScreen.begin(),
                                             m_childrenInScreen.end(),
                                             static_cast<ObjectInScreen*>(child)),
                                 m_childrenInScreen.end());
        break;
    default:
        m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
        break;
    }
}

void Scene::setCameraPosition(const glm::vec2& cameraPosition)
{
    m_cameraPosition = cameraPosition;
    m_cameraPosition = glm::clamp(m_cameraPosition,
                                  glm::vec2{ -30.0f },
                                  m_worldSize - m_game.screenSize() + glm::vec2{ 30.0f });
}
