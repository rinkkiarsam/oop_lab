#ifndef PLAYER_HPP
#define PLAYER_HPP


#include <nlohmann/json.hpp>

#include "Field.hpp"
#include "ShipManager.hpp"

using json = nlohmann::json;


struct Player
{
    Field field;
    ShipManager ship_manager; 
    int damage_multiplier{1};

    json toJson() const;
};


#endif // PLAYER_HPP