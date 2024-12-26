#ifndef GAME_RENDERER_HPP
#define GAME_RENDERER_HPP


#include <string_view>

#include "Game.hpp"


template <class Output>
class GameRenderer
{
public:
    static GameRenderer& instance(Game& game)
    {
        static GameRenderer self(game);
        return self;
    }
    void render();
    void renderAttack();
    void renderMsg(std::string_view msg);
    void renderAbilityMsg(std::string_view msg);
    void renderAbilityResMsg(std::string_view msg, bool res);
private:
    Output output = Output::instance();
    Game& game;
    
    GameRenderer(Game& game): game(game) {};

    template <typename T1, typename T2>
    friend class GameController;
};

template <class Output>
void GameRenderer<Output>::render()
{
    output.clear();
    output.displayFields(game.human.field, game.bot.field);
}

template <class Output>
void GameRenderer<Output>::renderAttack()
{
    output.clear();
    output.displayField(game.human.field);
    output.displayBuff(game.human.damage_multiplier);
}

template <class Output>
void GameRenderer<Output>::renderMsg(std::string_view msg)
{
    output.logMsg(msg);
}

template <class Output>
void GameRenderer<Output>::renderAbilityMsg(std::string_view msg)
{
    output.abilityMsg(msg);
}

template <class Output>
void GameRenderer<Output>::renderAbilityResMsg(std::string_view msg, bool res)
{
    output.abilityMsg(msg, res);
}


#endif // GAME_RENDERER_HPP