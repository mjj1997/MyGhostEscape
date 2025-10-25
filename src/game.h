#pragma once

class Game
{
public:
    static Game& instance()
    {
        static Game instance;
        return instance;
    }

private:
    Game() = default;
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
};
