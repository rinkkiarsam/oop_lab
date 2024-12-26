#ifndef GAME_HPP
#define GAME_HPP


#include "GameState.hpp"
#include "CLGameInput.hpp"
#include "HumanPlayer.hpp"


class Game
{
private:
    bool is_running;
    
protected:
    friend class GameState;
    friend class FieldSetupState;
    friend class ShipSetupState;
    friend class ShipPlacementState;
    friend class BattleState;

    template <typename T1, typename T2>
    friend class GameController;

    template <typename T>
    friend class GameRenderer;

    CLGameInput input = CLGameInput::instance();
    CLGameOutput output = CLGameOutput::instance();

    Player bot;
    HumanPlayer human;
    GameState* curr_state;

public:
    explicit Game();
    ~Game();

    void startNewGame();
    void play();
    void load();
    void save();
    void humanAttack();
    void botAttack();
    void castAbility();
    bool isBotsTurn();
    void checkGameState();
    void changeState(GameState* new_state);
    bool isRunning();
    void quit();
};


#endif // GAME_HPP