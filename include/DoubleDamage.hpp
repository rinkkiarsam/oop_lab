#ifndef DOUBLE_DAMAGE_HPP
#define DOUBLE_DAMAGE_HPP


#include "IAbility.hpp"


class DoubleDamage : public IAbility
{
public:
    DoubleDamage(int& multiplier);
    void cast() override;

private:
    int& multiplier_;
};


#endif // DOUBLE_DAMAGE_HPP