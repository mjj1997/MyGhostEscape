#include "enemy.h"
#include "affiliate/sprite_anime.h"
#include "player.h"

void Enemy::init()
{
    Actor::init();
    SpriteAnime::addSpriteAnimeChild(this, "assets/sprite/ghost-Sheet.png", 2.0f);
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
