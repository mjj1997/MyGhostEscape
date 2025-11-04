#include "sprite.h"

Texture::Texture(std::string_view filePath)
{
    texture = Game::instance().assetStorage()->getImage(filePath);
    SDL_GetTextureSize(texture, &srcRect.w, &srcRect.h);
}

