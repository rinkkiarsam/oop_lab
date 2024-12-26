#ifndef BATTLE_STATE_HPP
#define BATTLE_STATE_HPP


#include "GameState.hpp"


class Game;


enum class Turn {
    bot, 
    human
};


class BattleState final: public GameState
{
private:
    Turn curr_turn;

public:
    explicit BattleState(Game& game) noexcept;
    void takeTurn();
    Turn getTurn();
    void nextRound();
    void humanTurn();
    void castAbility();
    void botTurn();
    void doIt() override;
};


#endif // BATTLE_STATE_HPP