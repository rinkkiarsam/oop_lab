#ifndef CL_GAME_INPUT_HPP
#define CL_GAME_INPUT_HPP


class Game;

#include <string_view>
#include <utility>

#include "CLGameOutput.hpp"
#include "Ship.hpp"


enum class action
{
    primary_action,
    secondary_action,
    save,
    load,
    restart, 
    quit,
    err,
};

class CLGameInput
{
private:
    CLGameInput();
    CLGameOutput output = CLGameOutput::instance();
protected:
    const std::string default_keybinds = "./utils/default_keybinds.json";
    const std::string custom_keybinds = "./utils/custom_keybinds.json";

    friend class BattleState;
    friend class Game;

    std::unordered_map<char, action> keybinds;
    std::unordered_map<std::string, action> compulsory_keybinds = {
        {"primary_action", action::primary_action},
        {"secondary_action", action::secondary_action},
        {"save", action::save},
        {"load", action::load},
        {"start_new_game", action::restart},
        {"quit", action::quit}
    };
    bool inputX(int& x);
    bool inputXY(int& x, int& y);
    bool inputXYR(int& x, int& y, Ship::Orientation& r);
    const std::string inputString() const;
    void checkKeybinds() const;

public:
    static CLGameInput& instance();
    action inputAction();

    std::pair<int, int> inputFieldSize();
    std::pair<int, bool> inputShipSize();
    std::pair<int, int> inputCoordinates();
    int inputShipIndex();
    std::tuple<int, int, Ship::Orientation> inputShipPlacement();

    
    friend std::istream& operator>>(std::istream& is, CLGameInput& game_input);
};

std::istream& operator>>(std::istream& is, CLGameInput& game_input);


#endif // CL_GAME_INPUT_HPP