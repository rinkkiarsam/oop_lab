#ifndef ABILITY_FACTORY_HPP
#define ABILITY_FACTORY_HPP


#include "IAbility.hpp"
#include "DoubleDamage.hpp"
#include "DoubleDamageSpecs.hpp"
#include "Scanner.hpp"
#include "ScannerSpecs.hpp"
#include "Shelling.hpp"
#include "ShellingSpecs.hpp"


class AbilityFactory
{
public:
    AbilityFactory() = default;
    ~AbilityFactory() = default;
    IAbility* getAbility();
    void buildDoubleDamage(DoubleDamageSpecs* dd_specs);
    void buildShelling(ShellingSpecs* sh_specs);
    void buildScanner(ScannerSpecs* sc_specs);

private:
    IAbility* built_ability_ = nullptr;
};


#endif // ABILITY_FACTORY_HPP