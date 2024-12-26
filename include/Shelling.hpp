#ifndef SHELLING_HPP
#define SHELLING_HPP


#include "IAbility.hpp"
class ShipManager;


class Shelling: public IAbility
{
public:
    Shelling(ShipManager& ship_manager);
    void cast() override;

private:
    ShipManager& ship_manager_;
};


#endif // SHELLING_HPP