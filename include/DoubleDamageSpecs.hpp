#ifndef DOUBLE_DAMAGE_SPECS_HPP
#define DOUBLE_DAMAGE_SPECS_HPP


#include "IAbilitySpecs.hpp"
class IAbilitySpecsVisitor;


struct DoubleDamageSpecs : public IAbilitySpecs
{
    DoubleDamageSpecs(int& miltiplier);
    AbilityType getType() const override;
    void acceptVisitor(IAbilitySpecsVisitor& visitor) override;

    int& multiplier;
};


#endif // DOUBLE_DAMAGE_SPECS_HPP