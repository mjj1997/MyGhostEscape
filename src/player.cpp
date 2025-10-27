#include "player.h"
#include "core/scene.h"

void Player::init()
{
    setMaxSpeed(500.0f);
}

void Player::handleEvents(SDL_Event& event) {}

void Player::update(float deltaTime)
{
    keyboardControl();
    move(deltaTime);
}

void Player::render()
{
    m_game.drawBoundary(m_screenPosition,
                        m_screenPosition + glm::vec2{ 20.0f },
                        5.0f,
                        SDL_FColor{ 1.0f, 0.0f, 0.0f, 1.0f });
}

void Player::clean() {}

void Player::keyboardControl()
{
    m_velocity *= 0.9f; // 惯性

    auto currentKeyStates{ SDL_GetKeyboardState(nullptr) };
    if (currentKeyStates[SDL_SCANCODE_W])
        m_velocity.y = -m_maxSpeed;
    if (currentKeyStates[SDL_SCANCODE_S])
        m_velocity.y = m_maxSpeed;
    if (currentKeyStates[SDL_SCANCODE_A])
        m_velocity.x = -m_maxSpeed;
    if (currentKeyStates[SDL_SCANCODE_D])
        m_velocity.x = m_maxSpeed;
}

void Player::move(float deltaTime)
{
    setWorldPosition(m_worldPosition + m_velocity * deltaTime);
    SDL_Log("deltaTime: %f, position: (%f, %f), velocity: (%f, %f)",
            deltaTime,
            m_worldPosition.x,
            m_worldPosition.y,
            m_velocity.x,
            m_velocity.y);
}

