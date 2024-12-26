#include <random>

#include "Shelling.hpp"
#include "ShipManager.hpp"


Shelling::Shelling(ShipManager& ship_manager)
    : ship_manager_(ship_manager) {};

void Shelling::cast ()
{
    int number_of_ships = ship_manager_.getActiveShipsCount();
    if (number_of_ships == 0)
    {
        return;
    }

    int rand_ship_index = rand() % number_of_ships;
    Ship& rand_ship = ship_manager_.getActiveShip(rand_ship_index);

    int rand_segment_index = rand() % rand_ship.getLength();
    rand_ship.takeDamage(rand_segment_index, 1);
}