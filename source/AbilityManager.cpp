#include <random>
#include <array>
#include <stdexcept>
#include <algorithm>

#include "AbilityManager.hpp"
#include "GameException.hpp"

#include "IAbilitySpecs.hpp"


AbilityManager::AbilityManager()
    : visitor_(factory_)
{
    std::array<AbilityType, 3> tmp_abilities = {AbilityType::DoubleDamage,
                                   AbilityType::Shelling,
                                   AbilityType::Scanner};
    
    auto rng = std::default_random_engine {};
    std::shuffle(tmp_abilities.begin(), tmp_abilities.end(), rng);

    for (auto& ability : tmp_abilities)
    {
        abilities_.push_back(ability);
    }
}

AbilityManager::AbilityManager(const AbilityManager& other)
    : abilities_(other.abilities_), factory_(other.factory_), visitor_(factory_) {};

AbilityManager& AbilityManager::operator=(const AbilityManager& other)
{
    if (this != &other)
    {
        abilities_ = other.abilities_;
        factory_ = other.factory_;
    }

    return *this;
}

void AbilityManager::addAbility(AbilityType id)
{
    abilities_.push_back(id);
}

AbilityType AbilityManager::addRandomAbility()
{
    int rand_id = rand() % ability_type_count;

    switch (rand_id)
    {
    case 0:
    {
        abilities_.push_back(AbilityType::DoubleDamage);
        return AbilityType::DoubleDamage;
        break;
    }
    case 1:
    {
        abilities_.push_back(AbilityType::Scanner);
        return AbilityType::Scanner;
        break;
    }
    case 2:
    {
        abilities_.push_back(AbilityType::Shelling);
        return AbilityType::Shelling;
        break;
    }
    default: return AbilityType::DoubleDamage;
    }
}

IAbility* AbilityManager::buildAbility(IAbilitySpecs* specs)
{
    specs->acceptVisitor(visitor_);
    return factory_.getAbility();
}

void AbilityManager::castAbility(IAbilitySpecs& specs)
{
    if (abilities_.empty())
    {
        throw NoAbilityError("No ability");
    }
    if (specs.getType() != abilities_.front())
    {
        throw std::logic_error("Invalid ability specs type");
    }

    IAbility* current_ability = this->buildAbility(&specs);
    current_ability->cast();

    abilities_.pop_front();
}

AbilityType AbilityManager::getFirstAbility() const
{
    if (abilities_.empty())
    {
        throw NoAbilityError("No ability");
    }

    return abilities_.front();
}

bool AbilityManager::isEmpty() const noexcept
{
    return abilities_.empty();
}

std::ostream& operator<<(std::ostream& os, const AbilityManager& am)
{
    os << "First ability in queue: ";
    switch (am.getFirstAbility())
    {
        case (AbilityType::DoubleDamage):
        {
            os << "DoubleDamage";
            break;
        }
        case (AbilityType::Scanner):
        {
            os << "Scanner";
            break;
        }
        case (AbilityType::Shelling):
        {
            os << "Shelling";
            break;
        }
        default:
            break;
    }

    return os;
}

void AbilityManager::clean()
{
    while(!abilities_.empty())
    {
        abilities_.pop_back();
    }
}

json AbilityManager::toJson() const
{
    json save_file = json::array();
    for (const auto& ability : abilities_)
    {
        save_file.push_back(ability);
    }

    return save_file;
}