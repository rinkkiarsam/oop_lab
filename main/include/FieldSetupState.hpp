#ifndef FIELD_SETUP_STATE
#define FIELD_SETUP_STATE


#include "GameState.hpp"


class Game;


class FieldSetupState final: public GameState
{
private:
    int x, y;
public:
    explicit FieldSetupState(Game& game) noexcept;
    void doIt() override;
};


#endif // FIELD_SETUP_STATE