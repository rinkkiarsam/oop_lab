#ifndef ABILITY_SPECS_VISITOR_H
#define ABILITY_SPECS_VISITOR_H


#include "IAbilitySpecsVisitor.hpp"
class AbilityFactory;


class AbilitySpecsVisitor : public IAbilitySpecsVisitor
{
public:
    AbilitySpecsVisitor(AbilityFactory& factory);
    void visit(class DoubleDamageSpecs* dd_specs) override;
    void visit(class ScannerSpecs* sc_specs) override;
    void visit(class ShellingSpecs* sh_specs) override;

private:
    AbilityFactory& factory_;
};


#endif // ABILITY_SPECS_VISITOR_H