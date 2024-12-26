#ifndef I_ABILITY_SPECS_VISITOR_HPP
#define I_ABILITY_SPECS_VISITOR_HPP


class IAbilitySpecsVisitor
{
public:
    virtual void visit(class DoubleDamageSpecs* dd_specs) = 0;
    virtual void visit(class ScannerSpecs* sc_specs) = 0;
    virtual void visit(class ShellingSpecs* sh_specs) = 0;
};


#endif // I_ABILITY_SPECS_VISITOR_HPP