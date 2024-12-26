#include "FieldSetupState.hpp"
#include "ShipSetupState.hpp"
#include "CLGameInput.hpp"
#include "Game.hpp"
#include "GameException.hpp"


FieldSetupState::FieldSetupState(Game& game) noexcept
    : GameState(game), x(0), y(0)
{
    game.output.clear();
    game.output.logMsg("Welcome to Battleships!");
}

void FieldSetupState::doIt()
{
    game.output.clear();
    game.output.logMsg("Enter the size of your field:");

    auto coords = game.input.inputFieldSize();
    if (x < 0 or x >= getPlayer().field.getWidth()
        or y < 0 or y >= getPlayer().field.getHeight())
    {
        game.output.logMsg("Incorrect coordinates! Coordinates should be in range [1, Field Width), [1, Field Height)");
        coords = game.input.inputFieldSize();
    }

    try
    {
        auto[x, y] = coords;
        getPlayer().field = Field(x, y);
        getBot().field = Field(x, y);
        game.changeState(new ShipSetupState(game));
    }
    catch (const GameException& e)
    {
        game.output.logMsg(e.what());
        return;
    }
}