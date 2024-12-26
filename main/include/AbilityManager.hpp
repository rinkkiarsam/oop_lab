#ifndef ABILITY_MANAGER_HPP
#define ABILITY_MANAGER_HPP


#include <deque>
#include <iostream>
#include <nlohmann/json.hpp>

#include "AbilitySpecsVisitor.hpp"
#include "AbilityFactory.hpp"
class IAbilitySpecs;

using json = nlohmann::json;


class AbilityManager
{
public:
    AbilityManager();
    AbilityManager(const AbilityManager& other);
    AbilityManager& operator=(const AbilityManager& other);
    void addAbility(AbilityType id);
    AbilityType addRandomAbility();
    void castAbility(IAbilitySpecs& args);
    AbilityType getFirstAbility() const;
    bool isEmpty() const noexcept;
    void clean();

    friend std::ostream& operator<<(std::ostream& os, const AbilityManager& am);

    json toJson() const;

private:
    IAbility* buildAbility(IAbilitySpecs* args);

    std::deque<AbilityType> abilities_;
    AbilityFactory factory_;
    AbilitySpecsVisitor visitor_;
};


#endif // ABILITY_MANAGER