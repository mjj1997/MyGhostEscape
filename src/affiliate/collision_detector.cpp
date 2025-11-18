#include "collision_detector.h"

CollisionDetector* CollisionDetector::addCollisionDetectorChild(ObjectInScreen* parent,
                                                                glm::vec2 size,
                                                                Shape shape,
                                                                Anchor anchor)
{
    auto detector{ new CollisionDetector };
    detector->init();
    detector->setParent(parent);
    detector->setSize(size);
    detector->setShape(shape);
    detector->setAnchor(anchor);

    parent->addChild(detector);

    return detector;
}

void CollisionDetector::render()
{
#ifdef DEBUG_MODE
    ObjectAffiliated::render();

    auto pos{ m_parent->screenPosition() + m_offset };
    m_game.renderFillCircle(pos, m_size, 0.3f);
#endif // DEBUG_MODE
}

bool CollisionDetector::isColliding(CollisionDetector* other) const
{
    if (m_shape == Shape::Circle && other->shape() == Shape::Circle) {
        // 圆与圆碰撞检测
        auto center1{ m_parent->screenPosition() + m_offset + m_size / 2.0f };
        auto center2{ other->parent()->screenPosition() + other->offset() + other->size() / 2.0f };
        return glm::length(center1 - center2) < (m_size.x + other->size().x) / 2.0f;
    }

    // TODO: 其它形状的碰撞检测

    return false;
}
