#include "ShipSetupState.hpp"
#include "ShipPlacementState.hpp"
#include "Game.hpp"
#include "GameException.hpp"


ShipSetupState::ShipSetupState(Game& game)
    : GameState(game)
{
    points = (getPlayer().field.getWidth() - 1) * (getPlayer().field.getHeight() - 1);
    ship_cnt = 0;
}


int ShipSetupState::shipSizeToPoints(int size)
{
    return 2 * (size + 1);
}


void ShipSetupState::doIt()
{
    game.output.clear();

    bool stop = false;
    while (points >= shipSizeToPoints(1) and !stop)
    {
        game.output.logMsg("Enter size of one of your ships. If you think you have enough ships, press any other key to continue");

        auto [curr_ship_size, stop] = game.input.inputShipSize();
        if (stop) break;


        try 
        {
            getPlayer().ship_manager.addShip(curr_ship_size);
            getBot().ship_manager.addShip(curr_ship_size);
        }
        catch (const std::exception& e)
        {
            game.output.logMsg("Invalid ship size! Try again");
            continue;
        }

        points -= shipSizeToPoints(curr_ship_size);
        ship_cnt++;
        ship_sizes.push_back(curr_ship_size);

        game.output.clear();
        game.output.logMsg("Your fleet:");
        game.output.displayNums(ship_sizes);
    }

    if (ship_cnt == 0)
    {
        throw GameException("Either the fleet or the field is to small!\n");
    }

    game.output.logMsg("Ship setup finished!");

    // try
    // {
    //     getPlayer().ship_manager = ShipManager{ship_sizes};
    //     getBot().ship_manager = ShipManager{ship_sizes};
        game.changeState(new ShipPlacementState(game));
    // }
    // catch (const GameException& e)
    // {
    //     game.output.logMsg(e.what());
    // }
}