#pragma once

#include "core/actor.h"

class Player;
class SpriteAnime;

class Enemy : public Actor
{
public:
    enum class State { Normal, Hurt, Die };

    void init() override;
    void handleEvents(SDL_Event& event) override;
    void update(float deltaTime) override;
    void render() override;
    void clean() override;

    void aimTarget(Player* target);
    void checkState();
    void changeState(State state);

    Player* target() { return m_target; }
    void setTarget(Player* target) { m_target = target; }

private:
    Player* m_target{ nullptr };

    State m_currentState{ State::Normal };
    SpriteAnime* m_currentAnime{ nullptr };

    SpriteAnime* m_spriteNormal{ nullptr };
    SpriteAnime* m_spriteHurt{ nullptr };
    SpriteAnime* m_spriteDie{ nullptr };
};
