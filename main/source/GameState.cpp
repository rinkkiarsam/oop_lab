#include "GameState.hpp"
#include "ShipManager.hpp"
#include "Field.hpp"
#include "AbilityManager.hpp"
#include "Game.hpp"
#include "FileHandler.hpp"
#include "Player.hpp"
#include "HumanPlayer.hpp"


GameState::GameState(Game& game)
    : game(game) {};

HumanPlayer& GameState::getPlayer() 
{
    return game.human;
}

Player& GameState::getBot()
{
    return game.bot;
}

bool GameState::save(const std::string& file_name)
{
    FileHandler file_handler(file_name);
    
    file_handler.openForWriting();
    file_handler.write(*this);

    return true;
}

bool GameState::load(const std::string& file_name)
{
    FileHandler file_handler(file_name);

    file_handler.openForReading();
    file_handler.read(*this);

    return true;
}

ShipManager GameState::shipManagerFromJson(const json& save_file)
{
    ShipManager ship_manager{};

    const auto& active_ships = save_file["active ships"];
    const auto& passive_ships = save_file["passive ships"];

    for (auto& ship : passive_ships)
    {
        int x = int(ship["x"]);
        int y = int(ship["y"]);
        Ship::Orientation r = Ship::Orientation(ship["r"]);
        std::vector<Ship::SegmentState> states;
        for (auto& state : ship["segment states"])
        {
            states.push_back(Ship::SegmentState(state));
        }
        ship_manager.addShip(states, x, y, r, false);
    }

    for (auto& ship : active_ships)
    {
        int x = int(ship["x"]);
        int y = int(ship["y"]);
        Ship::Orientation r = Ship::Orientation(ship["r"]);
        std::vector<Ship::SegmentState> states;
        for (auto& state : ship["segment states"])
        {
            states.push_back(Ship::SegmentState(state));
        }
        Ship act(states, x, y, r);

        ship_manager.addShip(states, x, y, r, true);
    }
    
    return ship_manager;
}

Field GameState::fieldFromJson(const json& save_file, ShipManager& ship_manager)
{
    Field field(save_file["width"], save_file["height"]);

    const auto& cells = save_file["cells"];

    for (int x = 0; x < field.getWidth(); ++x)
    {
        for (int y = 0; y < field.getHeight(); ++y)
        {
            Ship *ship = nullptr;
            field.setCell(x, y, ship, Field::CellState(cells[x][y]["state"]), int(cells[x][y]["segment index"]));
        }
    }

    for (int i = 0; i < ship_manager.getActiveShipsCount(); ++i)
    {
        Ship& ship = ship_manager.getActiveShip(i);
        field.placeShip(ship, ship.x, ship.y, ship.r); 
    }

    return field;
}

AbilityManager GameState::abilityManagerFromJson(const json& save_file)
{
    AbilityManager ability_manager;
    ability_manager.clean();

    for (const auto& ability : save_file)
    {
        ability_manager.addAbility(ability);
    }
    return ability_manager;
}

std::ostream& operator<<(std::ostream& os, GameState& state)
{
    json save_file;
    save_file["human player"] = state.getPlayer().toJson();
    save_file["bot player"] = state.getBot().toJson();

    os << save_file.dump(4) << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, GameState& state)
{
    json save_file;
    is >> save_file;

    auto player_ship_manager_data = save_file["human player"]["ship manager"];
    auto player_field_data = save_file["human player"]["field"];
    auto player_ability_manager_data = save_file["human player"]["ability manager"];
    auto player_multiplier_data = save_file["human player"]["damage multiplier"];

    auto bot_ship_manager_data = save_file["bot player"]["ship manager"];
    auto bot_field_data = save_file["bot player"]["field"];
    auto bot_multiplier_data = save_file["bot player"]["damage multiplier"];

    state.getPlayer().ship_manager = std::move(state.shipManagerFromJson(player_ship_manager_data));
    state.getPlayer().field = std::move(state.fieldFromJson(player_field_data, state.getPlayer().ship_manager));
    state.getPlayer().ability_manager = state.abilityManagerFromJson(player_ability_manager_data);
    state.getPlayer().damage_multiplier = player_multiplier_data;

    state.getBot().ship_manager = std::move(state.shipManagerFromJson(bot_ship_manager_data));
    state.getBot().field = std::move(state.fieldFromJson(bot_field_data, state.getBot().ship_manager));
    state.getBot().damage_multiplier = bot_multiplier_data;

    return is;
}