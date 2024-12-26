#include "CLGameOutput.hpp"
#include "Field.hpp"


CLGameOutput& CLGameOutput::instance()
{
    static CLGameOutput self;
    return self;
}

void CLGameOutput::abilityMsg(AbilityType ability_type)
{
    switch (ability_type)
    {
        case AbilityType::DoubleDamage:
        {
            std::cout << "Double damage casted!\n";
            break;
        }
        case AbilityType::Scanner:
        {
            std::cout << "Scanner casted!\nChoose an area to be scanned\n";
            break;
        }
        case AbilityType::Shelling:
        {
            std::cout << "Shelling casted on enemy's fleet!\n";
        }
        default:
            std::cout << "Unknown Ability!\n";
    }
}

void CLGameOutput::abilityMsg(AbilityType ability_type, bool flag)
{
    if (ability_type != AbilityType::Scanner)
    {
        return;
    }

    if (flag)
    {
        std::cout << "Scanner found a ship!\n"; 
    }
    else
    {
        std::cout << "Scanner did not find any ships...\n";
    }
}

void CLGameOutput::logMsg(std::string_view msg)
{
    std::cout << msg << '\n';
}

void CLGameOutput::clear()
{
    system("clear");
}

void CLGameOutput::displayFieldNoFog(Field& field)
{
    std::cout << "  ";
    for (int x = 0; x < field.getWidth(); ++x)
    {
        std::cout << ' ' << x << ' ';
    }
    std::cout << '\n';

    for (int y = 0; y < field.getHeight(); ++y)
    {
        std::cout << y << ' ';
        for (int x = 0; x < field.getWidth(); ++x)
        {
            if (field.isShip(x, y))
            {
                std::cout << '[' << static_cast<int>(field.getShipSegmentState(x, y)) << ']';
            }
            else
            {
                switch (field.getCellState(x, y))
                {
                    case Field::CellState::unknown:
                    {
                        std::cout << "[ ]";
                        break;
                    }
                    case Field::CellState::empty:
                    {
                        std::cout << "[.]";
                        break;
                    }
                    default: break;
                }
            }
        }
        std::cout << '\n';
    }
}

void CLGameOutput::displayField(Field& field)
{
    std::cout << "  ";
    for (int x = 0; x < field.getWidth(); ++x)
    {
        std::cout << ' ' << x << ' ';
    }
    std::cout << '\n';

    for (int y = 0; y < field.getHeight(); ++y)
    {
        std::cout << y << ' ';
        for (int x = 0; x < field.getWidth(); ++x)
        {
            switch (field.getCellState(x, y))
            {
                case Field::CellState::unknown:
                {
                    std::cout << "[?]";
                    break;
                }
                case Field::CellState::empty:
                {
                    std::cout << "[.]";
                    break;
                }
                case Field::CellState::ship:
                {
                    std::cout << '[' << static_cast<int>(field.getShipSegmentState(x, y)) << ']';
                    break;
                }
            }
        }
        std::cout << '\n';
    }
}

void CLGameOutput::displayBuff(bool flag) const
{
    if (flag)
    {
        std::cout << "Active: double damage buff\n";
    }
}

void CLGameOutput::displayFields(Field& friend_field, Field& foe_field)
{
    std::cout << "Your field:\n";
    displayFieldNoFog(friend_field);
    std::cout << '\n';
    std::cout << "Foe's field:\n";
    displayField(foe_field);
}

void CLGameOutput::displayNums(const std::vector<int>& nums)
{
    for(auto num : nums)
    {
        std::cout << num << ' ';
    }
    std::cout << '\n';
}

void CLGameOutput::displayShipManager(ShipManager& ship_manager)
{
    std::cout << ship_manager << '\n';
}