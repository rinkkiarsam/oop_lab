#include "HumanPlayer.hpp"


void HumanPlayer::castAbility(Player& target)
{
    auto ability_type = ability_manager.getFirstAbility();

    output.abilityMsg(ability_type);

    int scan = -1;
    switch (ability_type)
    {
        case AbilityType::DoubleDamage:
        {
            DoubleDamageSpecs dds = DoubleDamageSpecs(damage_multiplier);
            ability_manager.castAbility(dds);
            break;
        }
        case AbilityType::Scanner:
        {
            output.clear();
            output.displayFields(this->field, target.field);
            output.abilityMsg(ability_type);

            auto coords = input.inputCoordinates();
            if (coords.first < 0 or coords.first >= field.getWidth() - scan_range
                or coords.second < 0 or coords.second >= field.getHeight() - scan_range)
            {
                output.logMsg("Invalid coordinates! Try again!");
                coords = input.inputCoordinates();
            }
            auto [x, y] = coords;

            ScannerSpecs scs = ScannerSpecs(target.field, x, y, scan);
            ability_manager.castAbility(scs);
            break;
        }
        case AbilityType::Shelling:
        {
            ShellingSpecs shs = ShellingSpecs(target.ship_manager);
            ability_manager.castAbility(shs);
            break;
        }
    }

    output.abilityMsg(ability_type, scan > 0 ? true : false);
}

void HumanPlayer::attack(Player& target, int x, int y)
{
    bool hit = target.field.attackCell(x, y, damage_multiplier);
    damage_multiplier = 1;

    if (hit and !target.field.getShip(x, y).isAlive())
    {
        auto ability = ability_manager.addRandomAbility();
        output.logMsg("Added ability:");
        switch (ability)
        {
            case AbilityType::DoubleDamage:
            {
                output.logMsg("double damage");
                break;
            }
            case AbilityType::Scanner:
            {
                output.logMsg("scanner");
                break;
            }
            case AbilityType::Shelling:
            {
                output.logMsg("shelling");
                break;
            }
        }
    }
}

json HumanPlayer::toJson() const
{
    json save_file = Player::toJson();
    save_file["ability manager"] = ability_manager.toJson();
    return save_file;
}