#include "player.h"
#include "affiliate/sprite_anime.h"
#include "core/scene.h"

void Player::init()
{
    Actor::init();

    setMaxSpeed(500.0f);
    m_spriteIdle = SpriteAnime::addSpriteAnimeChild(this, "assets/sprite/ghost-idle.png", 2.0f);
    m_spriteMove = SpriteAnime::addSpriteAnimeChild(this, "assets/sprite/ghost-move.png", 2.0f);
    m_spriteMove->setActive(false);
}

void Player::handleEvents(SDL_Event& event)
{
    Actor::handleEvents(event);
}

void Player::update(float deltaTime)
{
    Actor::update(deltaTime);
    keyboardControl();
    checkState();
    move(deltaTime);
    syncCamera();
}

void Player::render()
{
    Actor::render();
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

void Player::checkState()
{
    if (m_velocity.x < 0) {
        m_spriteMove->setFlipped(true);
        m_spriteIdle->setFlipped(true);
    } else {
        m_spriteMove->setFlipped(false);
        m_spriteIdle->setFlipped(false);
    }

    State state{ glm::length(m_velocity) > 0.1f ? State::Moving : State::Idle };
    if (state != m_curentState) {
        m_curentState = state;
        changeState(m_curentState);
    }
}

void Player::changeState(State state)
{
    switch (state) {
    case State::Idle:
        m_spriteIdle->setActive(true);
        m_spriteMove->setActive(false);
        m_spriteIdle->setCurrentFrame(m_spriteMove->currentFrame());
        m_spriteIdle->setFrameTimer(m_spriteMove->frameTimer());
        break;
    case State::Moving:
        m_spriteIdle->setActive(false);
        m_spriteMove->setActive(true);
        m_spriteMove->setCurrentFrame(m_spriteIdle->currentFrame());
        m_spriteMove->setFrameTimer(m_spriteIdle->frameTimer());
        break;
    default:
        break;
    }
}
