#include <random>


#include "BattleState.hpp"
#include "ShipPlacementState.hpp"
#include "Game.hpp"
#include "GameException.hpp"


BattleState::BattleState(Game& game) noexcept
    : GameState(game), curr_turn(Turn::human) 
{
    game.output.clear();
    game.output.logMsg("The battle begins!");
    game.output.displayFields(getPlayer().field, getBot().field);
    doIt();
}

void BattleState::takeTurn()
{
    curr_turn = (curr_turn == Turn::bot) ? Turn::human : Turn::bot;
}

void BattleState::nextRound()
{
    getBot().field = std::move(Field(getBot().field.getWidth(),
                                     getBot().field.getHeight()));
    getBot().ship_manager = std::move(ShipManager(getBot().ship_manager.getShipSizes()));
    ShipPlacementState sps(game);
    sps.botShipPlacement();
}

void BattleState::humanTurn()
{
    game.output.logMsg("Choose a cell to attack!");
    auto [x, y] = game.input.inputCoordinates();

    try
    {
        getPlayer().attack(getBot(), x, y);
        takeTurn();
    }
    catch (const FieldCoordinatesError& e)
    {
        game.output.logMsg(e.what());
    }
}

void BattleState::botTurn()
{
    int x = rand() % getBot().field.getWidth();
    int y = rand() % getBot().field.getHeight();
    getPlayer().field.attackCell(x, y);
    takeTurn();
}

void BattleState::castAbility()
{
    try 
    {
        getPlayer().castAbility(getBot());
    }
    catch(const NoAbilityError& e)
    {
        game.output.logMsg(e.what());
    }
}

void BattleState::doIt() {}

Turn BattleState::getTurn()
{
    return curr_turn;
}
