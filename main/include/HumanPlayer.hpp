#ifndef HUMAN_PLAYER_HPP
#define HUMAN_PLAYER_HPP


#include "Player.hpp"
#include "CLGameInput.hpp"
#include "CLGameOutput.hpp"
#include "AbilityManager.hpp"

struct HumanPlayer: public Player
{
    AbilityManager ability_manager;
    CLGameInput input = CLGameInput::instance();
    CLGameOutput output = CLGameOutput::instance();

    void attack(Player& target, int x, int y);
    void castAbility(Player& target);
    json toJson() const;
};


#endif // HUMAN_PLAYER_HPP