#include "CLGameInput.hpp"
#include "FileHandler.hpp"
#include "GameException.hpp"
#include "Ship.hpp"


CLGameInput::CLGameInput()
{
    try 
    {
        FileHandler fh(custom_keybinds);
        fh.openForReading();
        fh.read(*this);
    }
    catch (const std::exception& e)
    {
        output.logMsg(e.what());
        output.logMsg("Could not acces custom keybinds. Default keybinds applied");
        FileHandler fh(default_keybinds);
        fh.openForReading();
        fh.read(*this);
    }
}

CLGameInput& CLGameInput::instance()
{
    static CLGameInput self;
    return self;
}

action CLGameInput::inputAction()
{
    char inp;
    std::cin >> inp;

    auto it = keybinds.find(inp);
    if (it != keybinds.end())
    {
        return it->second;
    }
    else
    {
        return action::err;
    }
}


bool CLGameInput::inputX(int& x)
{
    if (std::cin >> x)
    {
        return true;
    }

    return false;
}


bool CLGameInput::inputXY(int& x, int& y)
{
    if (std::cin >> x >> y)
    {
        return true;
    }
    return false;
}


bool CLGameInput::inputXYR(int& x, int& y, Ship::Orientation& r)
{
    std::string orientation = "";
    if (!(std::cin >> x >> y))
    {
        return false;
    }
    std::cin >> orientation;
    if (orientation == "h" or orientation == "hor" or orientation == "horizontal")
    {
        r = Ship::Orientation::horizontal;
        return true;
    }
    else if (orientation == "v" or orientation == "ver" or orientation == "vertical")
    {
        r = Ship::Orientation::vertical;
        return true;
    }

    return false;
}

const std::string CLGameInput::inputString() const 
{
    std::string inp;
    std::cin >> inp;
    return inp;
}

void CLGameInput::checkKeybinds() const 
{
    std::vector<action> actions;

    for (const auto& [key, action] : keybinds)
    {
        if (std::find(actions.begin(), actions.end(), action) != actions.end())
        {
            throw GameException("Same key for multiple actions\n");
        }

        actions.emplace_back(action);
    }
}

std::istream& operator>>(std::istream& is, CLGameInput& game_input)
{
    json j;
    is >> j;

    for (const auto& [key, val]: j.items())
    {
        auto it = game_input.compulsory_keybinds.find(val);
        if (it != game_input.compulsory_keybinds.end())
        {
            game_input.keybinds[key[0]] = it->second;
        }
        else
        {
            throw GameException("Unknown action keybind\n");
        }
    }

    if (game_input.keybinds.size() != game_input.compulsory_keybinds.size())
    {
        throw GameException("Unlawful key binds\n");
    }

    game_input.checkKeybinds();

    return is;
}

std::pair<int, int> CLGameInput::inputCoordinates()
{
    int x = -1, y = -1;
    bool success = inputXY(x, y);
    while (!success)
    {
        std::cin.clear();
        std::cin.ignore();

        output.logMsg("Invalid coordinates! Try again");
        success = inputXY(x, y);
    }

    return std::pair<int, int>(x, y);
}

std::pair<int, int> CLGameInput::inputFieldSize()
{
    int x = -1, y = -1;
    bool success = inputXY(x, y);
    while (!success)
    {
        std::cin.clear();
        std::cin.ignore();

        output.logMsg("Invalid input. Enter two integers.");
        success = inputXY(x, y);
    }

    return std::pair<int, int>(x, y);
}

int CLGameInput::inputShipIndex()
{
    int i = -1;
    bool success = inputX(i);
    while (!success or i < 0)
    {
        std::cin.clear();
        std::cin.ignore();

        output.logMsg("Incorrect ship index! Enter a positive number like: 1");
        success = inputX(i);
    }
    
    return i;
}

std::pair<int, bool> CLGameInput::inputShipSize()
{
    int size = 1;
    bool stop = !inputX(size);
    // while (size < 1)
    // {
    //     std::cout << "size : " << size << " stop: " << stop << '\n';
    //     output.logMsg("Incorrect ship size! Enter a positive number like: 1");
    //     stop = !inputX(size);
    // }

    if (stop)
    {
        std::cin.clear();
        std::cin.ignore();
    }

    return std::pair<int, bool>(size, stop);
}

std::tuple<int, int, Ship::Orientation> CLGameInput::inputShipPlacement()
{
    int x = -1, y = -1;
    Ship::Orientation r = Ship::Orientation::horizontal;
    bool success = inputXYR(x, y, r);
    while (!success)
    {
        std::cin.clear();
        std::cin.ignore();
        
        output.logMsg("You can't place a ship like that! Try something like: 1, 2, h");
        success = inputXYR(x, y, r);
    }

    return std::tuple<int, int, Ship::Orientation>(x, y, r);
}