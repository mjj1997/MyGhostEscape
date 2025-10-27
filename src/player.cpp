#include "player.h"
#include "core/scene.h"

void Player::init()
{
    setMaxSpeed(500.0f);
}

void Player::handleEvents(SDL_Event& event) {}

void Player::update(float deltaTime)
{
}

void Player::render()
{
    m_game.drawBoundary(m_screenPosition,
                        m_screenPosition + glm::vec2{ 20.0f },
                        5.0f,
                        SDL_FColor{ 1.0f, 0.0f, 0.0f, 1.0f });
}

void Player::clean() {}
