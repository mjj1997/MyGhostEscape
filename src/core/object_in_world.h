#pragma once

#include "object_in_screen.h"

class CollisionDetector;

class ObjectInWorld : public ObjectInScreen
{
public:
    virtual void init() override { m_type = ObjectType::World; }
    virtual void update(float deltaTime) override;

    void setScreenPosition(const glm::vec2& position) override;

    glm::vec2 worldPosition() const { return m_worldPosition; };
    void setWorldPosition(const glm::vec2& position);

    CollisionDetector* collisionDetector() const { return m_collisionDetector; }
    void setCollisionDetector(CollisionDetector* collisionDetector)
    {
        m_collisionDetector = collisionDetector;
    }

protected:
    glm::vec2 m_worldPosition{ glm::vec2{ 0.0f } }; // 世界上的位置
    CollisionDetector* m_collisionDetector{ nullptr };
};
