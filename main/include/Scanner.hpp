#ifndef SCANNER_HPP
#define SCANNER_HPP


#include "IAbility.hpp"
class Field;


constexpr int scan_range = 2;


class Scanner : public IAbility
{
public:
    Scanner(Field& field, int x, int y, int& scan);
    void cast() override;

private:
    Field& field_;
    int x_, y_;
    int &scan_;
};


#endif // SCANNER_HPP