#include "Game.hpp"
#include "GameRenderer.hpp"
#include "GameController.hpp"


int main()
{
    try 
    {
        Game game;
        GameController<CLGameInput, GameRenderer<CLGameOutput>> controller(game);
        controller.run();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}


