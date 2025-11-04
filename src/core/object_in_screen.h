#pragma once

#include "object.h"

class ObjectInScreen : public Object
{
public:
    virtual void init() override { m_type = ObjectType::Screen; }

    glm::vec2 screenPosition() const { return m_screenPosition; };
    virtual void setScreenPosition(const glm::vec2& position) { m_screenPosition = position; };

protected:
    glm::vec2 m_screenPosition{ glm::vec2{ 0.0f } }; // 屏幕上的位置
};
