#ifndef I_ABILITY_SPECS_HPP
#define I_ABILITY_SPECS_HPP


#include "IAbilitySpecsVisitor.hpp"

enum class AbilityType
{
    DoubleDamage,
    Scanner,
    Shelling,
};

constexpr int ability_type_count = 3;

struct IAbilitySpecs
{
    virtual void acceptVisitor(IAbilitySpecsVisitor& visitor) = 0;
    virtual AbilityType getType() const = 0;
};


#endif // I_ABILITY_SPECS_HPP