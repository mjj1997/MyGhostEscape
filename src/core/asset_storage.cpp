#include "asset_storage.h"

AssetStorage::AssetStorage(SDL_Renderer* renderer)
    : m_renderer{ renderer }
{}

void AssetStorage::clean()
{
    for (const auto& image : m_images) {
        SDL_DestroyTexture(image.second);
    }
    m_images.clear();

    for (const auto& sound : m_sounds) {
        Mix_FreeChunk(sound.second);
    }
    m_sounds.clear();

    for (const auto& music : m_musics) {
        Mix_FreeMusic(music.second);
    }
    m_musics.clear();

    for (const auto& font : m_fonts) {
        TTF_CloseFont(font.second);
    }
    m_fonts.clear();
}

void AssetStorage::loadImage(std::string_view filePath)
{
    SDL_Texture* texture = IMG_LoadTexture(m_renderer, filePath.data());
    if (texture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load image %s", filePath.data());
        return;
    }
    m_images.emplace(std::string{ filePath }, texture);
}

void AssetStorage::loadSound(std::string_view filePath)
{
    Mix_Chunk* sound = Mix_LoadWAV(filePath.data());
    if (sound == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load sound %s", filePath.data());
        return;
    }
    m_sounds.emplace(std::string{ filePath }, sound);
}

void AssetStorage::loadMusic(std::string_view filePath)
{
    Mix_Music* music = Mix_LoadMUS(filePath.data());
    if (music == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load music %s", filePath.data());
        return;
    }
    m_musics.emplace(std::string{ filePath }, music);
}

void AssetStorage::loadFont(std::string_view filePath, int fontSize)
{
    TTF_Font* font = TTF_OpenFont(filePath.data(), fontSize);
    if (font == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font %s", filePath.data());
        return;
    }
    m_fonts.emplace(std::string{ filePath } + std::to_string(fontSize), font);
}

SDL_Texture* AssetStorage::getImage(std::string_view filePath)
{
    auto it{ m_images.find(std::string{ filePath }) };

    if (it == m_images.end()) {
        loadImage(filePath);
        it = m_images.find(std::string{ filePath });
    }

    if (it == m_images.end()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get image %s", filePath.data());
        return nullptr;
    }

    return it->second;
}

Mix_Chunk* AssetStorage::getSound(std::string_view filePath)
{
    auto it{ m_sounds.find(std::string{ filePath }) };

    if (it == m_sounds.end()) {
        loadSound(filePath);
        it = m_sounds.find(std::string{ filePath });
    }

    if (it == m_sounds.end()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get sound %s", filePath.data());
        return nullptr;
    }

    return it->second;
}

Mix_Music* AssetStorage::getMusic(std::string_view filePath)
{
    auto it{ m_musics.find(std::string{ filePath }) };

    if (it == m_musics.end()) {
        loadMusic(filePath);
        it = m_musics.find(std::string{ filePath });
    }

    if (it == m_musics.end()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get music %s", filePath.data());
        return nullptr;
    }

    return it->second;
}

TTF_Font* AssetStorage::getFont(std::string_view filePath, int fontSize)
{
    auto it{ m_fonts.find(std::string{ filePath } + std::to_string(fontSize)) };

    if (it == m_fonts.end()) {
        loadFont(filePath, fontSize);
        it = m_fonts.find(std::string{ filePath } + std::to_string(fontSize));
    }

    if (it == m_fonts.end()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to get font %s", filePath.data());
        return nullptr;
    }

    return it->second;
}
