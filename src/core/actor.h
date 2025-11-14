#pragma once

#include "object_in_world.h"

class Actor : public ObjectInWorld
{
public:
    void move(float deltaTime);

    glm::vec2 velocity() const { return m_velocity; };
    void setVelocity(const glm::vec2& velocity) { m_velocity = velocity; };

    float maxSpeed() const { return m_maxSpeed; };
    void setMaxSpeed(float maxSpeed) { m_maxSpeed = maxSpeed; };

protected:
    glm::vec2 m_velocity{ glm::vec2{ 0.0f } }; // 速度
    float m_maxSpeed{ 100.0f };                // 最大速度
};
