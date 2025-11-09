#include "game.h"
#include "../affiliate/sprite.h"
#include "../scene_main.h"

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

    // 计算每帧时间
    m_frameTime = 1'000'000'000 / m_FPS;

    // 创建资产存储
    m_assetStorage = new AssetStorage{ m_renderer };

    // 创建场景
    m_currentScene = new SceneMain;
    m_currentScene->init();
}

void Game::run()
{
    while (m_isRunning) {
        auto frameStart{ SDL_GetTicksNS() };
        handleEvents();
        update(m_deltaTime);
        render();
        auto frameEnd{ SDL_GetTicksNS() };
        auto frameElapsed{ frameEnd - frameStart };

        if (frameElapsed < m_frameTime) {
            SDL_DelayNS(m_frameTime - frameElapsed);
            m_deltaTime = m_frameTime / 1.0e9f; // 转换为秒
        } else {
            m_deltaTime = frameElapsed / 1.0e9f; // 转换为秒
        }
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
            m_currentScene->handleEvents(event);
            break;
        }
    }
}

void Game::update(float deltaTime)
{
    m_currentScene->update(deltaTime);
}

void Game::render()
{
    // 清除渲染器
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    m_currentScene->render();

    // 显示渲染结果
    SDL_RenderPresent(m_renderer);
}

void Game::clean()
{
    // 清理场景
    if (m_currentScene) {
        m_currentScene->clean();
        delete m_currentScene;
        m_currentScene = nullptr;
    }
    // 清理资产存储
    if (m_assetStorage) {
        m_assetStorage->clean();
        delete m_assetStorage;
        m_assetStorage = nullptr;
    }
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

void Game::renderTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size)
{
    SDL_FRect dstRect{ position.x, position.y, size.x, size.y };
    SDL_RenderTextureRotated(m_renderer,
                             texture.texture,
                             &texture.srcRect,
                             &dstRect,
                             texture.angle,
                             nullptr,
                             texture.isFlipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Game::drawGrid(const glm::vec2& topLeft,
                    const glm::vec2& bottomRight,
                    float gridWidth,
                    SDL_FColor fColor)
{
    // 设置渲染颜色
    SDL_SetRenderDrawColorFloat(m_renderer, fColor.r, fColor.g, fColor.b, fColor.a);
    // 绘制垂直网格线
    for (float x{ topLeft.x }; x <= bottomRight.x; x += gridWidth)
        SDL_RenderLine(m_renderer, x, topLeft.y, x, bottomRight.y);
    // 绘制水平网格线
    for (float y{ topLeft.y }; y <= bottomRight.y; y += gridWidth)
        SDL_RenderLine(m_renderer, topLeft.x, y, bottomRight.x, y);
    // 恢复默认渲染颜色
    SDL_SetRenderDrawColorFloat(m_renderer, 0.0f, 0.0f, 0.0f, 1.0f);
}

void Game::drawBoundary(const glm::vec2& topLeft,
                        const glm::vec2& bottomRight,
                        float boundaryWidth,
                        SDL_FColor fColor)
{
    // 设置渲染颜色
    SDL_SetRenderDrawColorFloat(m_renderer, fColor.r, fColor.g, fColor.b, fColor.a);
    // 绘制边界
    for (float i{ 0 }; i < boundaryWidth; ++i) {
        SDL_FRect rect{ topLeft.x - i,
                        topLeft.y - i,
                        bottomRight.x - topLeft.x + 2 * i,
                        bottomRight.y - topLeft.y + 2 * i };
        SDL_RenderRect(m_renderer, &rect);
    }
    // 恢复默认渲染颜色
    SDL_SetRenderDrawColorFloat(m_renderer, 0.0f, 0.0f, 0.0f, 1.0f);
}
