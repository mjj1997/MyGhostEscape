#include "object_affiliated.h"

void ObjectAffiliated::setOffsetByAnchor(Anchor anchor)
{
    m_anchor = anchor;
    switch (anchor) {
    case Anchor::TopLeft:
        m_offset = glm::vec2{ 0.0f };
        break;
    case Anchor::TopCenter:
        m_offset = glm::vec2{ -m_size.x / 2.0f, 0.0f };
        break;
    case Anchor::TopRight:
        m_offset = glm::vec2{ -m_size.x, 0.0f };
        break;
    case Anchor::CenterLeft:
        m_offset = glm::vec2{ 0.0f, -m_size.y / 2.0f };
        break;
    case Anchor::Center:
        m_offset = glm::vec2{ -m_size.x / 2.0f, -m_size.y / 2.0f };
        break;
    case Anchor::CenterRight:
        m_offset = glm::vec2{ -m_size.x, -m_size.y / 2.0f };
        break;
    case Anchor::BottomLeft:
        m_offset = glm::vec2{ 0.0f, -m_size.y };
        break;
    case Anchor::BottomCenter:
        m_offset = glm::vec2{ -m_size.x / 2.0f, -m_size.y };
        break;
    case Anchor::BottomRight:
        m_offset = glm::vec2{ -m_size.x, -m_size.y };
        break;
    default:
        break;
    }
}

void ObjectAffiliated::setSize(const glm::vec2& size)
{
    m_size = size;
    setOffsetByAnchor(m_anchor);
}
