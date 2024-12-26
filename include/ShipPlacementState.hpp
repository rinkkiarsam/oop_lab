#ifndef SHIP_PLACEMENT_STATE
#define SHIP_PLACEMENT_STATE


#include "GameState.hpp"


class Game;


class ShipPlacementState final: public GameState
{
public:
    explicit ShipPlacementState(Game& game) noexcept;
    void doIt() override;
    void botShipPlacement();
};


#endif // SHIP_PLACEMENT_STATE