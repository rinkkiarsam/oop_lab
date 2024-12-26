#include "AbilityFactory.hpp"


IAbility* AbilityFactory::getAbility()
{
    return built_ability_;
}

void AbilityFactory::buildDoubleDamage(DoubleDamageSpecs* dd_specs)
{
    built_ability_ = new DoubleDamage(dd_specs->multiplier);
}

void AbilityFactory::buildShelling(ShellingSpecs* sh_specs)
{
    built_ability_ = new Shelling(sh_specs->ship_manager_);
}

void AbilityFactory::buildScanner(ScannerSpecs* sc_specs)
{
    built_ability_ = new Scanner(sc_specs->field_, sc_specs->x_, sc_specs->y_, sc_specs->scan_);
}