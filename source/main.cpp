#include "Game.hpp"
#include "GameRenderer.hpp"
#include "GameController.hpp"


// Починить вывод сканера и других абилок бебебеб
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


