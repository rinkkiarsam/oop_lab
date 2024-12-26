#include "DoubleDamageSpecs.hpp"
#include "IAbilitySpecsVisitor.hpp"


DoubleDamageSpecs::DoubleDamageSpecs(int& multiplier)
    : multiplier(multiplier) {};

AbilityType DoubleDamageSpecs::getType() const
{
    return AbilityType::DoubleDamage;
}

void DoubleDamageSpecs::acceptVisitor(IAbilitySpecsVisitor& visitor)
{
    visitor.visit(this);
}