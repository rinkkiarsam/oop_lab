#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP


#include <nlohmann/json.hpp>

class ShipManager;
class Field;
class AbilityManager;
class HumanPlayer;
class Player;
class Game;


using json = nlohmann::json;


class GameState
{
protected:
    Game& game;

    HumanPlayer& getPlayer();
    Player& getBot();

public:
    GameState(Game& game);
    virtual void doIt() = 0;
    virtual ~GameState() {};

    ShipManager shipManagerFromJson(const json& save_file);
    Field fieldFromJson(const json& save_file, ShipManager& ship_manager);
    AbilityManager abilityManagerFromJson(const json& save_file);

    bool save(const std::string& file_name);
    bool load(const std::string& file_name);

    friend std::ostream& operator<<(std::ostream& os, GameState& gs);
    friend std::istream& operator>>(std::istream& os, GameState& gs);
};


std::ostream& operator<<(std::ostream& os, GameState& gs);
std::istream& operator>>(std::istream& os, GameState& gs);


#endif // GAME_STATE_HPP