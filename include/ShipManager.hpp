#ifndef SHIP_MANAGER_HPP
#define SHIP_MANAGER_HPP


#include <vector>
#include <initializer_list>
#include <utility>
#include <iostream>
#include <nlohmann/json.hpp>

#include "Ship.hpp"
class Fiedld;

using json = nlohmann::json;


class ShipManager
{
public:
    ShipManager() {};
    explicit ShipManager(const std::vector<int> ship_sizes);
    ~ShipManager();
    ShipManager(const ShipManager& other); 
    const std::vector<Ship> getShips() const noexcept;
    ShipManager& operator=(const ShipManager& other);
    ShipManager(ShipManager&& other);
    ShipManager& operator=(ShipManager&& other);
    void addShip(int ship_size);
    void addShip(std::vector<Ship::SegmentState> segment_states, int x, int y, Ship::Orientation r, bool is_active);
    bool allShipsArePlaced() const noexcept;
    bool allShipsAreSunk() const noexcept;
    int getActiveShipsCount() const noexcept;
    int getPassiveShipsCount() const noexcept;
    int getShipsCount() const noexcept;
    Ship& deployShip(int index);
    Ship& getActiveShip(int index);
    std::vector<int> getShipSizes() const noexcept;
    Ship& getPassiveShip(int index) const;

    friend std::ostream& operator<<(std::ostream& os, const ShipManager& sm);

    json toJson() const;

private:
    std::vector<Ship*> active_ships_;
    std::vector<Ship*> passive_ships_; 
};



#endif //SHIP_MANAGER_HPP