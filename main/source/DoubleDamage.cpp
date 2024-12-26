#include "DoubleDamage.hpp"


DoubleDamage::DoubleDamage(int& multiplier)
    : multiplier_(multiplier) {};

void DoubleDamage::cast()
{
    multiplier_ = 2;
}