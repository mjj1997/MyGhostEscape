#pragma once

#include "../core/object_affiliated.h"

class CollisionDetector : public ObjectAffiliated
{
public:
    enum class Shape {
        Circle, // 默认 m_size.x == m_size.y 为直径, 半径为 m_size.x / 2.0f
        Rectangle
    };

    static CollisionDetector* addCollisionDetectorChild(ObjectInScreen* parent,
                                                        glm::vec2 size,
                                                        Shape shape = Shape::Circle);

    void init() override {};

    bool isColliding(CollisionDetector* other) const;

    Shape shape() const { return m_shape; }
    void setShape(Shape shape) { m_shape = shape; }

protected:
    Shape m_shape{ Shape::Circle };
};
