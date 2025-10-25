#pragma once

#include <SDL3/SDL.h>
#include <glm/glm.hpp>

#include <string_view>

class Scene;

class Game
{
public:
    ~Game() = default;

    static Game& instance()
    {
        static Game instance;
        return instance;
    }

    void init(std::string_view title, int width, int height);
    void run();
    void handleEvents();
    void update(float deltaTime);
    void render();
    void clean();

private:
    Game() = default;
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    glm::vec2 m_screenSize{ glm::vec2{ 0.0f } }; // 屏幕尺寸
    bool m_isRunning{ true };
    Scene* m_currentScene{ nullptr };

    Uint64 m_FPS{ 60 };
    Uint64 m_frameTime{ 0 }; // 每帧时间，单位：纳秒
    float m_deltaTime{ 0.0f };

    SDL_Window* m_window{ nullptr };
    SDL_Renderer* m_renderer{ nullptr };
};
