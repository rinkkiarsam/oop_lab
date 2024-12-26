#include "Player.hpp"

json Player::toJson() const
{
    json save_file;
    save_file["field"] = field.toJson();
    save_file["ship manager"] = ship_manager.toJson();
    save_file["damage multiplier"] = damage_multiplier;
    return save_file;
}