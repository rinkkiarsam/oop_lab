#ifndef CL_GAME_OUTPUT_HPP
#define CL_GAME_OUTPUT_HPP


#include <string_view>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "IAbilitySpecs.hpp"

// q 8 8 4 4 q 0 0 0 h 0 3 3 v

class GameState;
class Field;
class ShipManager;


class CLGameOutput
{
public:
    static CLGameOutput& instance();

    void abilityMsg(AbilityType ability_type);
    void abilityMsg(AbilityType ability_type, bool flag);
    void logMsg(std::string_view msg);
    void displayFieldNoFog(Field& field);
    void displayField(Field& field);
    void displayFields(Field& friend_field, Field& foe_field);
    void displayNums(const std::vector<int>& nums);
    void displayBuff(bool flag) const;
    void displayShipManager(ShipManager& ship_manager);
    void clear();

private:
    CLGameOutput() = default;
};


#endif // CL_GAME_OUTPUT_HPP