#include "player.h"
#include "affiliate/sprite_anime.h"
#include "core/scene.h"

void Player::init()
{
    Actor::init();

    setMaxSpeed(500.0f);

    auto spriteAnime{ new SpriteAnime };
    spriteAnime->setTexture(Texture{ "assets/sprite/ghost-idle.png" });
    spriteAnime->setParent(this);
    addChild(spriteAnime);
}

void Player::handleEvents(SDL_Event& event)
{
    Actor::handleEvents(event);
}

void Player::update(float deltaTime)
{
    Actor::update(deltaTime);
    keyboardControl();
    move(deltaTime);
    syncCamera();
}

void Player::render()
{
    Actor::render();
    m_game.drawBoundary(m_screenPosition,
                        m_screenPosition + glm::vec2{ 20.0f },
                        5.0f,
                        SDL_FColor{ 1.0f, 0.0f, 0.0f, 1.0f });
}

void Player::clean()
{
    Actor::clean();
}

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
    m_worldPosition = glm::clamp(m_worldPosition,
                                 glm::vec2{ 0.0f },
                                 m_game.currentScene()->worldSize());
}

void Player::syncCamera()
{
    m_game.currentScene()->setCameraPosition(m_worldPosition - m_game.screenSize() / 2.0f);
}
