#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
#include <string_view>
#include <unordered_map>

class AssetStorage
{
public:
    explicit AssetStorage(SDL_Renderer* renderer);
    ~AssetStorage() = default;

    void clean();

    void loadImage(std::string_view filePath);
    void loadSound(std::string_view filePath);
    void loadMusic(std::string_view filePath);
    void loadFont(std::string_view filePath, int fontSize);

    SDL_Texture* getImage(std::string_view filePath);
    Mix_Chunk* getSound(std::string_view filePath);
    Mix_Music* getMusic(std::string_view filePath);
    TTF_Font* getFont(std::string_view filePath, int fontSize);

private:
    SDL_Renderer* m_renderer{ nullptr };

    std::unordered_map<std::string, SDL_Texture*> m_images;
    std::unordered_map<std::string, Mix_Chunk*> m_sounds;
    std::unordered_map<std::string, Mix_Music*> m_musics;
    std::unordered_map<std::string, TTF_Font*> m_fonts;
};
