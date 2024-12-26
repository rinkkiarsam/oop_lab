#include <vector>
#include <utility>
#include <iostream>
#include <stdexcept>

#include "ShipManager.hpp"
#include "Ship.hpp"


ShipManager::ShipManager(const std::vector<int> ship_sizes)
{
    for (auto& ship_size : ship_sizes)
    {
        auto ship_ptr = new Ship(ship_size);
        passive_ships_.push_back(ship_ptr);
    }
}

ShipManager::~ShipManager()
{
    for (auto& ship_ptr : active_ships_)
    {
        delete ship_ptr;
    }

    for (auto& ship_ptr : passive_ships_)
    {
        delete ship_ptr;
    }
}

ShipManager::ShipManager(const ShipManager& other)
    : active_ships_(other.active_ships_), passive_ships_(other.passive_ships_) {}

ShipManager& ShipManager::operator=(const ShipManager& other)
{
    if (this != &other)
    {
        active_ships_ = other.active_ships_;
        passive_ships_ = other.passive_ships_;
    }
    return *this;
}

ShipManager::ShipManager(ShipManager&& other)
{
    std::swap(active_ships_, other.active_ships_);
    std::swap(passive_ships_, other.passive_ships_);
}

ShipManager& ShipManager::operator=(ShipManager&& other)
{
    if (this != &other)
    {
        std::swap(active_ships_, other.active_ships_);
        std::swap(passive_ships_, other.passive_ships_);
    }

    return *this;
}

const std::vector<Ship> ShipManager::getShips() const noexcept
{
    std::vector<Ship> ships;

    for (const auto& ship_ptr : active_ships_)
    {
        ships.push_back(*ship_ptr);
    }

    for (const auto& ship_ptr : passive_ships_)
    {
        ships.push_back(*ship_ptr);
    }

    return ships;
}

void ShipManager::addShip(int ship_size)
{
    if (ship_size < Ship::min_length or ship_size > Ship::max_length)
    {
        throw std::length_error("Invalid ship size");
    }

    passive_ships_.push_back(new Ship(ship_size));
}

void ShipManager::addShip(std::vector<Ship::SegmentState> segment_states, int x, int y, Ship::Orientation r, bool is_active = true)
{
    Ship *ship = new Ship(segment_states, x, y, r);
    is_active ? active_ships_.push_back(ship) : passive_ships_.push_back(ship);
}

bool ShipManager::allShipsArePlaced() const noexcept
{
    return passive_ships_.size() == 0;
}

bool ShipManager::allShipsAreSunk() const noexcept
{
    for (const auto& ship_ptr : active_ships_)
    {
        if (ship_ptr->isAlive())
        {
            return false;
        }
    }

    return true;
}

int ShipManager::getActiveShipsCount() const noexcept
{
    return active_ships_.size();
}

int ShipManager::getPassiveShipsCount() const noexcept
{
    return passive_ships_.size();
}

int ShipManager::getShipsCount() const noexcept
{
    return active_ships_.size() + passive_ships_.size();
}

Ship& ShipManager::deployShip(int index)
{
    if (index < 0 or index >= getPassiveShipsCount())
    {
        throw std::length_error("Invalid ship index");
    }

    auto ship = passive_ships_[index];
    active_ships_.push_back(ship);
    passive_ships_.erase(passive_ships_.begin() + index);

    return *ship;
}

Ship& ShipManager::getActiveShip(int index)
{
    if (index < 0 or index >= getActiveShipsCount())
    {
        throw std::length_error("Invalid ship index");
    }

    return *active_ships_[index];
}

Ship& ShipManager::getPassiveShip(int index) const
{
    if (index < 0 or index >= getPassiveShipsCount())
    {
        throw std::length_error("Invalid ship index");
    }

    return *passive_ships_[index];
}

std::vector<int> ShipManager::getShipSizes() const noexcept
{
    std::vector<int> sizes;
    for (const auto& ship : active_ships_)
    {
        sizes.push_back(ship->getLength());
    }
    for (const auto& ship : passive_ships_)
    {
        sizes.push_back(ship->getLength());
    }
    return sizes;
}

std::ostream& operator<<(std::ostream& os, const ShipManager& sm)
{
    int ship_counter = 0;

    for (const auto& ship : sm.passive_ships_)
    {
        if (ship_counter != 0)
        {
            os << '\n';
        }

        os << "№" << ship_counter++ << " (passive) " << *ship;
    }

    for (const auto& ship : sm.active_ships_)
    {
        if (ship_counter != 0)
        {
            os << '\n';
        }

        os << "№" << ship_counter++ << " (active) " << *ship;
    }

    return os;
}

json ShipManager::toJson() const
{
    json save_file;
    json passive_ships_array = json::array();
    json active_ships_array = json::array();

    for (const auto& ship: passive_ships_)
    {
        passive_ships_array.push_back(ship->toJson()); // !!!!!!!!!!!!
    }

    for (const auto& ship: active_ships_)
    {
        active_ships_array.push_back(ship->toJson());
    }

    save_file["passive ships"] = passive_ships_array;
    save_file["active ships"] = active_ships_array;
    return save_file;
}