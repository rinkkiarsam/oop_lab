#ifndef FIELD_HPP
#define FIELD_HPP


#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

#include "Ship.hpp"
#include "ShipManager.hpp"

using json = nlohmann::json;


class Field
{
public:
    enum class CellState
    {
        unknown,
        empty,
        ship
    };

    explicit Field(int size_x = 8, int size_y = 8);
    Field (const Field& other);
    Field (Field&& other);
    Field& operator=(const Field& other);
    Field& operator=(Field&& other);
    ~Field();
    void placeShip(Ship& ship, int x, int y, Ship::Orientation orientation);
    bool attackCell(int x, int y, int damage = 1);
    int getWidth() const noexcept;
    int getHeight() const noexcept;
    CellState getCellState(int x, int y) const;
    void displaySegments() const noexcept;
    bool isCollision(int x, int x_offset, int y, int y_offset, Ship::Orientation orientation) const;
    bool hasShip(int x, int y) const;
    Ship getShip(int x, int y) const;
    void setCell(int x, int y, Ship* p_ship, CellState state, int index);
    void display() const noexcept;
    bool isShip(int x, int y) const;
    Ship::SegmentState getShipSegmentState(int x, int y) const;

    friend std::ostream& operator<<(std::ostream& os, Field& field);
    json toJson() const;

private:
    class Cell
    {
    public:
        Cell();
        ~Cell();
        CellState getState() const noexcept;
        void setState(CellState state) noexcept;
        void setShipSegment(Ship& ship, int index);
        Ship::SegmentState getShipSegmentState() const;
        bool attack(int damage);
        bool isEmpty() const noexcept;
        Ship getShip() const;
        void setShip(Ship* p_ship);
        void setIndex(int index);
        bool isShip() const;

        json toJson() const;

    private:
        CellState state_{CellState::unknown};
        Ship* p_ship_ = nullptr;
        int segment_index_{-1};
    };

    int width_;
    int height_;
    std::vector<std::vector<Cell>> cells_;
};



#endif //FIELD_HPP