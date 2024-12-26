#include "ScannerSpecs.hpp"


ScannerSpecs::ScannerSpecs(Field& field, int x, int y, int &scan_)
    : field_(field), x_(x), y_(y), scan_(scan_) {};

AbilityType ScannerSpecs::getType() const 
{
    return AbilityType::Scanner;
}

void ScannerSpecs::acceptVisitor(IAbilitySpecsVisitor& visitor)
{
    return visitor.visit(this);
}