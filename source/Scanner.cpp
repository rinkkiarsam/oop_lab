#include "Scanner.hpp"
#include "Field.hpp"


Scanner::Scanner(Field& field, int x, int y, int& scan)
    : field_(field), x_(x), y_(y), scan_(scan) {};

void Scanner::cast()
{
    for (int y = y_; y < y_ + scan_range; ++y)
    {
        for (int x = x_; x < x_ + scan_range; ++x)
        {
            if (field_.hasShip(x, y))
            {
                scan_++;
            }
        }
    }
}
