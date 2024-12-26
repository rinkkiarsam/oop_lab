#include "Game.hpp"
#include "FieldSetupState.hpp"
#include "ShipSetupState.hpp"
// #include "ShipPlacementState.hpp"
#include "BattleState.hpp"


Game::Game() 
{
    curr_state = new FieldSetupState(*this);
}

void Game::startNewGame()
{
    changeState(new FieldSetupState(*this));
    is_running = true;

    curr_state->doIt(); // Field Setup State
    curr_state->doIt(); // Ship Setup State
    curr_state->doIt(); // Ship Placement State
}

void Game::play()
{
    is_running = true;

    output.logMsg("Press [l] to load a save file. Press any other key to continue");

    if (input.inputAction() == action::load)
    {
        load();
    }
    else
    {
        startNewGame();
    }
}

void Game::load()
{
    output.clear();
    output.logMsg("Enter the name of your save file");
    curr_state->load(input.inputString());
    this->changeState(new BattleState(*this));
}

void Game::save()
{
    output.clear();
    output.logMsg("Enter the name of your save file");
    curr_state->save(input.inputString());
}

void Game::changeState(GameState* new_state)
{
    delete curr_state;
    curr_state = new_state;
}

Game::~Game()
{
    delete curr_state;
}

bool Game::isRunning()
{
    return is_running;
}

void Game::quit()
{
    is_running = false;
}

void Game::humanAttack()
{
    auto res = dynamic_cast<BattleState*>(curr_state);
    if (res)
    {
        res->humanTurn();
    }
}

void Game::botAttack()
{
    auto res = dynamic_cast<BattleState*>(curr_state);
    if (res)
    {
        res->botTurn();
    }
}

void Game::castAbility()
{
    auto res = dynamic_cast<BattleState*>(curr_state);
    if (res)
    {
        res->castAbility();
    }
}

bool Game::isBotsTurn()
{
    auto res = dynamic_cast<BattleState*>(curr_state);
    return (res->getTurn() == Turn::bot);
}

void Game::checkGameState()
{
    if (is_running and bot.ship_manager.allShipsAreSunk())
    {
        output.clear();
        output.logMsg("You have won!");
        output.logMsg("Press [a] to start next round or any other key to exit");

        if (input.inputAction() == action::primary_action)
        {
            auto res = dynamic_cast<BattleState*>(curr_state);
            res->nextRound();
        }
        else
        {
            quit();
        }
    }
    else if (is_running and human.ship_manager.allShipsAreSunk())
    {
        output.clear();
        output.logMsg("You have lost!");
        output.logMsg("Press [a] to start a new game or anu other key to exit");

        if (input.inputAction() == action::primary_action)
        {
            startNewGame();
        }
        else
        {
            quit();
        }
    }
}