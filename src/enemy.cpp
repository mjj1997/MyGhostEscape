#include "enemy.h"
#include "affiliate/sprite_anime.h"
#include "player.h"

void Enemy::init()
{
    Actor::init();

    m_spriteNormal = SpriteAnime::addSpriteAnimeChild(this, "assets/sprite/ghost-Sheet.png", 2.0f);
    m_spriteHurt = SpriteAnime::addSpriteAnimeChild(this, "assets/sprite/ghostHurt-Sheet.png", 2.0f);
    m_spriteDie = SpriteAnime::addSpriteAnimeChild(this, "assets/sprite/ghostDead-Sheet.png", 2.0f);
    m_spriteHurt->setActive(false);
    m_spriteDie->setActive(false);

    m_currentAnime = m_spriteNormal;
}

void Enemy::handleEvents(SDL_Event& event)
{
    Actor::handleEvents(event);
}

void Enemy::update(float deltaTime)
{
    Actor::update(deltaTime);
    aimTarget(m_target);
    move(deltaTime);

    m_timer += deltaTime;
    if (m_timer > 2.0f && m_timer < 4.0f) {
        changeState(State::Hurt);
    } else if (m_timer > 4.0f) {
        changeState(State::Die);
    }
}

void Enemy::render()
{
    Actor::render();
}

void Enemy::clean()
{
    Actor::clean();
}

void Enemy::aimTarget(Player* target)
{
    if (target == nullptr)
        return;

    auto direction{ target->worldPosition() - this->worldPosition() };
    direction = glm::normalize(direction);
    m_velocity = direction * m_maxSpeed;
}

void Enemy::checkState() {}

void Enemy::changeState(State state)
{
    if (m_currentState == state)
        return;

    m_currentAnime->setActive(false);
    switch (state) {
    case State::Normal:
        m_currentAnime = m_spriteNormal;
        m_currentAnime->setActive(true);
        break;
    case State::Hurt:
        m_currentAnime = m_spriteHurt;
        m_currentAnime->setActive(true);
        break;
    case State::Die:
        m_currentAnime = m_spriteDie;
        m_currentAnime->setActive(true);
        break;
    default:
        break;
    }
    m_currentState = state;
}
