#pragma once

#include "object_in_screen.h"

class ObjectInWorld : public ObjectInScreen
{
public:
    void setScreenPosition(const glm::vec2& position) override;

    glm::vec2 worldPosition() const { return m_worldPosition; };
    void setWorldPosition(const glm::vec2& position);

protected:
    glm::vec2 m_worldPosition{ glm::vec2{ 0.0f } }; // 世界上的位置
};
