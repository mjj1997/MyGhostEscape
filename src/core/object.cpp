#include "object.h"

void Object::handleEvents(SDL_Event& event)
{
    for (const auto& child : m_children) {
        child->handleEvents(event);
    }
}

void Object::update(float deltaTime)
{
    for (const auto& child : m_children) {
        child->update(deltaTime);
    }
}

void Object::render()
{
    for (const auto& child : m_children) {
        child->render();
    }
}

void Object::clean()
{
    for (const auto& child : m_children) {
        child->clean();
        delete child;
    }
    m_children.clear();
}
