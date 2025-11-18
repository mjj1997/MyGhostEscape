#pragma once

#define DEBUG_MODE

enum class ObjectType {
    None,
    Screen,
    World,
};

enum class Anchor {
    None,
    TopLeft,
    TopCenter,
    TopRight,
    CenterLeft,
    Center,
    CenterRight,
    BottomLeft,
    BottomCenter,
    BottomRight,
};
