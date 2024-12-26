#ifndef SCANNER_SPECS_HPP
#define SCANNER_SPECS_HPP


#include "IAbilitySpecs.hpp"
class Field;


struct ScannerSpecs : public IAbilitySpecs
{
    ScannerSpecs(Field& field, int x, int y, int &scan_);
    AbilityType getType() const override;
    void acceptVisitor(IAbilitySpecsVisitor& visitor) override;

    Field& field_;
    int x_, y_;
    int &scan_;
};


#endif // SCANNER_SPECS_HPP