#include "game.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

void Game::init(std::string_view title, int width, int height)
{
    m_screenSize = glm::vec2{ width, height };

    // SDL3初始化
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL初始化失败: %s\n", SDL_GetError());
        m_isRunning = false;
    }

    // 不需要进行SDL_image初始化

    // SDL3_Mixer初始化
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Mixer初始化失败: %s\n", SDL_GetError());
        m_isRunning = false;
    }
    if (!Mix_OpenAudio(0, NULL)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Mixer打开音频失败: %s\n", SDL_GetError());
        m_isRunning = false;
    }
    Mix_AllocateChannels(16); // 分配16个音频通道

    // SDL3_TTF初始化
    if (!TTF_Init()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_TTF初始化失败: %s\n", SDL_GetError());
        m_isRunning = false;
    }

    // 创建窗口与渲染器
    SDL_CreateWindowAndRenderer(title.data(),
                                width,
                                height,
                                SDL_WINDOW_RESIZABLE,
                                &m_window,
                                &m_renderer);
    if (!m_window || !m_renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "创建窗口或渲染器失败: %s\n", SDL_GetError());
        m_isRunning = false;
    }
    // 设置窗口逻辑分辨率
    SDL_SetRenderLogicalPresentation(m_renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
}

void Game::run()
{
    while (m_isRunning) {
        handleEvents();
        update(0.0f);
        render();
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
            m_isRunning = false;
            break;
        default:
            break;
        }
    }
}

void Game::update(float deltaTime) {}

void Game::render() {}

void Game::clean()
{
    // 关闭SDL3_TTF
    TTF_Quit();
    // 关闭SDL3_Mixer
    Mix_CloseAudio();
    Mix_Quit();
    // 销毁窗口与渲染器
    if (m_renderer)
        SDL_DestroyRenderer(m_renderer);
    if (m_window)
        SDL_DestroyWindow(m_window);
    // 退出SDL3
    SDL_Quit();
}
