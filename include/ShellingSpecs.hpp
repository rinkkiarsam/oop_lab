#ifndef SHELLING_SPECS_HPP
#define SHELLING_SPECS_HPP


#include "IAbilitySpecs.hpp"
class ShipManager;


struct ShellingSpecs : public IAbilitySpecs
{
    ShellingSpecs(ShipManager& ship_manager);
    AbilityType getType() const override;
    void acceptVisitor(IAbilitySpecsVisitor& visitor) override;

    ShipManager& ship_manager_;
};


#endif // SHELLING_SPECS_HPP