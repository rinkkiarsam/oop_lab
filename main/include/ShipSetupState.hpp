#ifndef SHIP_SETUP_STATE
#define SHIP_SETUP_STATE


#include <map>
#include <vector>


#include "GameState.hpp"


class Game;


class ShipSetupState final: public GameState
{
private:
    std::vector<int> ship_sizes;
    int points;
    int ship_cnt;

public:
    explicit ShipSetupState(Game& game);
    void doIt() override;
    int shipSizeToPoints(int size) ;
};

#endif // SHIP_SETUP_STATE