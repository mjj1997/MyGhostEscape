#pragma once

#include "object_in_world.h"

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

    glm::vec2 worldSize() const { return m_worldSize; }
    void setWorldSize(const glm::vec2& worldSize) { m_worldSize = worldSize; }

    glm::vec2 cameraPosition() const { return m_cameraPosition; }
    void setCameraPosition(const glm::vec2& cameraPosition);

    glm::vec2 world2Screen(const glm::vec2& worldPosition) const
    {
        return worldPosition - m_cameraPosition;
    }
    glm::vec2 screen2World(const glm::vec2& screenPosition) const
    {
        return screenPosition + m_cameraPosition;
    }

protected:
    glm::vec2 m_worldSize{ glm::vec2{ 0.0f } }; // 世界大小
    glm::vec2 m_cameraPosition{ glm::vec2{ 0.0f } };

    std::vector<ObjectInWorld*> m_childrenInWorld;
    std::vector<ObjectInScreen*> m_childrenInScreen;
};
