#include "object.h"

void Object::handleEvents(SDL_Event& event)
{
    for (auto& child : m_children) {
        if (child->isActive())
            child->handleEvents(event);
    }
}

void Object::update(float deltaTime)
{
    for (auto& child : m_children) {
        if (child->isActive())
            child->update(deltaTime);
    }
}

void Object::render()
{
    for (auto& child : m_children) {
        if (child->isActive())
            child->render();
    }
}

void Object::clean()
{
    for (auto& child : m_children) {
        child->clean();
        delete child;
    }
    m_children.clear();
}
