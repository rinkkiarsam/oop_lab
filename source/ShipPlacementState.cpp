#include <random>


#include "ShipPlacementState.hpp"
#include "BattleState.hpp"
#include "Game.hpp"
#include "GameException.hpp"


ShipPlacementState::ShipPlacementState(Game& game) noexcept
    : GameState(game) 
{
    game.output.clear();
    game.output.logMsg("Now place your ships!");
}


void ShipPlacementState::doIt()
{
    while (getPlayer().ship_manager.getPassiveShipsCount() > 0)
    {
        game.output.clear();
        game.output.displayFieldNoFog(getPlayer().field);
        game.output.logMsg("Your fleet:");
        game.output.displayShipManager(getPlayer().ship_manager);

        game.output.logMsg("Enter index of the ship you want to choose:");

        int index = game.input.inputShipIndex();
        if (index < 0 or index >= getPlayer().ship_manager.getPassiveShipsCount())
        {
            game.output.logMsg("Incorrect ship index! Choose index of one of your ships.");
            game.output.displayShipManager(getPlayer().ship_manager);
            index = game.input.inputShipIndex();
        }

        game.output.logMsg("Place your ship!");
        // game.output.displayFieldNoFog(getPlayer().field);
        auto [x, y, r] = game.input.inputShipPlacement();

        try
        {
            auto& ship = getPlayer().ship_manager.getPassiveShip(index);
            getPlayer().field.placeShip(ship, x, y, r);
            getPlayer().ship_manager.deployShip(index);
        }
        catch (const ShipCollisionError& e)
        {
            game.output.logMsg("Cannot place ship here, try again");
            continue;
        }
        catch (const FieldCoordinatesError& e)
        {
            game.output.logMsg("Cannot place ship here, try again");
            continue;
        }
    }

    botShipPlacement();

    game.output.displayFields(getPlayer().field, getBot().field);

    game.changeState(new BattleState(game));
}


void ShipPlacementState::botShipPlacement()
{
    // std::cout << getBot().ship_manager << '\n';

    while (getBot().ship_manager.getPassiveShipsCount() > 0)
    {
        int x = rand() % getBot().field.getWidth();
        int y = rand() % getBot().field.getHeight();
        Ship::Orientation r = Ship::Orientation(rand() % 2);

        try
        {
            auto& ship = getBot().ship_manager.getPassiveShip(0);
            getBot().field.placeShip(ship, x, y, r);
            getBot().ship_manager.deployShip(0);
        }
        catch (const ShipCollisionError& e)
        {
            continue;
        }
        catch (const FieldCoordinatesError& e)
        {
            continue;
        }
    }
}