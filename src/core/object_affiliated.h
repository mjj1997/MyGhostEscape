#pragma once

#include "object_in_screen.h"

class ObjectAffiliated : public Object
{
public:
    void setOffsetByAnchor(Anchor anchor);
    void scaleSize(float scale);

    ObjectInScreen* parent() const { return m_parent; }
    void setParent(ObjectInScreen* parent) { m_parent = parent; }

    glm::vec2 offset() const { return m_offset; }
    void setOffset(const glm::vec2& offset) { m_offset = offset; }

    glm::vec2 size() const { return m_size; }
    void setSize(const glm::vec2& size);

    Anchor anchor() const { return m_anchor; }
    void setAnchor(Anchor anchor) { m_anchor = anchor; }

protected:
    ObjectInScreen* m_parent{ nullptr };     // 父节点
    glm::vec2 m_offset{ glm::vec2{ 0.0f } }; // 相对父节点的偏移量
    glm::vec2 m_size{ glm::vec2{ 0.0f } };   // 大小
    Anchor m_anchor{ Anchor::Center };       // 锚点, 默认为中心
};
