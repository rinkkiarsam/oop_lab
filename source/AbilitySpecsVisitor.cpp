#include "AbilitySpecsVisitor.hpp"
#include "AbilityFactory.hpp"


AbilitySpecsVisitor::AbilitySpecsVisitor(AbilityFactory& factory)
    : factory_(factory) {};

void AbilitySpecsVisitor::visit(class DoubleDamageSpecs* dd_specs)
{
    factory_.buildDoubleDamage(dd_specs);
}

void AbilitySpecsVisitor::visit(class ShellingSpecs* sh_specs)
{
    factory_.buildShelling(sh_specs);
}

void AbilitySpecsVisitor::visit(class ScannerSpecs* sc_specs)
{
    factory_.buildScanner(sc_specs);
}