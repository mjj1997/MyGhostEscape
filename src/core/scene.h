#pragma once

#include "object.h"

#include <vector>

class Scene : public Object
{
public:
    Scene() = default;
    virtual ~Scene() override = default;

    virtual void init() override = 0;
    virtual void handleEvents(SDL_Event& event) override = 0;
    virtual void update(float deltaTime) override = 0;
    virtual void render() override = 0;
    virtual void clean() override = 0;

protected:
    glm::vec2 m_cameraPosition{ glm::vec2{ 0 } };
    std::vector<Object*> m_objects;
};
