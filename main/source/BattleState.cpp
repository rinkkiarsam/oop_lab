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

void BattleState::doIt() {
    while (game.is_running 
           and !getPlayer().ship_manager.allShipsAreSunk()
           and !getBot().ship_manager.allShipsAreSunk())
    {
        if (curr_turn == Turn::human)
        {
            auto act = game.input.inputAction();
            switch (act)
            {
                case action::primary_action:
                {
                    humanTurn();
                    break;
                }
                case action::secondary_action:
                {
                    castAbility();
                    break;
                }
                case action::save:
                {   
                    save(game.input.inputString());
                    break;
                }
                case action::load:
                {
                    load(game.input.inputString());
                    break;
                }
                case action::quit:
                {
                    game.quit();
                    break;
                }
                case action::restart:
                {
                    game.startNewGame();
                    break;
                }
                default: game.output.logMsg("Invalid input. Try again!");
            }

            game.checkGameState();
        }
        else
        {
            botTurn();
            game.checkGameState();
        }

        game.output.clear();
        game.output.displayFields(game.human.field, game.bot.field);

        // std::cout << "\n--Debug--\n";
        // game.output.displayFieldNoFog(game.bot.field);
        // std::cout << '\n';
        // game.output.displayShipManager(game.bot.ship_manager);
        // std::cout << "\n--Debug--\n";

        game.output.displayBuff(game.human.damage_multiplier == 2 ? true : false);
    }
    std::cout << "\n\nrework\n\n";
}

Turn BattleState::getTurn()
{
    return curr_turn;
}
