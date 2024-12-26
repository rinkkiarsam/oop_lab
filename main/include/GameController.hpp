#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP


#include "Game.hpp"


template <class Input, class Renderer>
class GameController
{
public:
    GameController(Game& game);
    void run();
private:
    Game& curr_session;
    Input input = Input::instance();
    Renderer output = Renderer::instance();
    std::map<action, std::function<void()>> actions; 
};

template <class Input, class Renderer>
GameController<Input, Renderer>::GameController(Game& game)
    : curr_session(game), output(game)
{
    actions[action::primary_action] = [&](){curr_session.humanAttack();};
    actions[action::secondary_action] = [&](){curr_session.castAbility();};
    actions[action::load] = [&](){curr_session.load();};
    actions[action::save] = [&](){curr_session.save();};
    actions[action::quit] = [&](){curr_session.quit();};
}

template<class Input, class Renderer>
void GameController<Input, Renderer>::run()
{
    curr_session.play();

    while (curr_session.isRunning())
    {
        auto act = input.inputAction();
        if (actions.find(act) != actions.end())
        {
            actions[act]();
        }
        else
        {
            output.renderMsg("Unknown action");
        }

        if (!curr_session.isBotsTurn()) 
        {
            continue;
        }

        curr_session.botAttack();
        curr_session.checkGameState();
        output.render();
    }
}


#endif // GAME_CONTROLLER_HPP