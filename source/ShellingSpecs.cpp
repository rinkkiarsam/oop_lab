#include "ShellingSpecs.hpp"


ShellingSpecs::ShellingSpecs(ShipManager& ship_manager)
    : ship_manager_(ship_manager) {};

AbilityType ShellingSpecs::getType() const
{
    return AbilityType::Shelling;
}

void ShellingSpecs::acceptVisitor(IAbilitySpecsVisitor& visitor)
{
    return visitor.visit(this);
}