#include <iostream>
#include <vector>
#include <utility>

#include "Ship.hpp"
#include "ShipManager.hpp"
#include "Field.hpp"
#include "GameException.hpp"


Field::Cell::Cell() = default;

Field::Cell::~Cell() = default;

Field::CellState Field::Cell::getState() const noexcept
{
    return state_;
}

void Field::Cell::setShipSegment(Ship& ship, int index)
{
    if (index < 0 or index >= ship.getLength())
    {
        throw std::length_error("Incorrect index");
    }
    p_ship_ = &ship;
    segment_index_ = index;
}

bool Field::Cell::attack(int damage)
{
    if (damage < 0)
    {
        throw DamageError("Damage error");
        return false; 
    }

    if (isEmpty())
    {
        state_ = Field::CellState::empty;
        return false; 
    }
    
    state_ = Field::CellState::ship;
    p_ship_->takeDamage(segment_index_, damage);

    if (p_ship_->isAlive())
    {
        return false;
    }
    return true;
}

Ship::SegmentState Field::Cell::getShipSegmentState() const
{
    if (isEmpty())
    {
        throw std::logic_error("Cell is empty");
    }

    return p_ship_->getSegmentState(segment_index_);
}

bool Field::Cell::isEmpty() const noexcept
{
    return p_ship_ == nullptr;
}

void Field::Cell::setState(Field::CellState state) noexcept
{
    state_ = state;
}

Field::Field(int size_x, int size_y)
    : width_(size_x), height_(size_y)
{
    if (width_ < Ship::min_length or height_ < Ship::min_length)
    {
        throw std::logic_error("Invalid field size");
    }

    cells_.resize(width_);
    for (int x = 0; x < width_; ++x)
    {
        cells_[x].resize(height_);

        for (int y = 0; y < height_; ++y)
        {
            cells_[x][y] = Cell();
        }
    }
}
 
Field::Field (const Field& other)
    : width_(other.getWidth()), 
    height_(other.getHeight()),
    cells_(other.cells_) 
{}

Field::Field (Field&& other)
    : width_(std::move(other.width_)),
    height_(std::move(other.height_)),
    cells_(std::move(other.cells_))
{}

Field& Field::operator=(const Field& other)
{
    if (this == &other)
    {
        return *this;
    }

    width_ = other.width_;
    height_ = other.height_;
    cells_ = other.cells_;

    return *this;
}

Field& Field::operator=(Field&& other)
{
    if (this == &other)
    {
        return *this;
    }

    width_ = other.width_;
    height_ = other.height_;
    cells_ = std::move(other.cells_);

    return *this;
}

Field::~Field() = default;

bool Field::attackCell(int x, int y, int damage)
{
    if (x < 0 or x >= width_ or y < 0 or y >= height_)
    {
        throw FieldCoordinatesError("Field coordinates error attack");
    }
    return cells_[x][y].attack(damage);
}

bool Field::isCollision(int x, int x_offset, 
                        int y, int y_offset, 
                        Ship::Orientation orientation) const
{
    for (int i = std::max(x - 1, 0); i < std::min(x + x_offset + 2, width_); ++i)
    {
        for (int j = std::max(y - 1, 0); j < std::min(y + y_offset + 2, height_); ++j)
        {
            if (not cells_[i][j].isEmpty())
            {
                return true;                
            }
        }
    }

    return false;
}

void Field::placeShip(Ship& ship, int x, int y, Ship::Orientation orientation)
{
    auto [x_offset, y_offset] = orientation == Ship::Orientation::horizontal ? 
                                std::pair<int, int>{ship.getLength() - 1, 0} :
                                std::pair<int, int>{0, ship.getLength() - 1};
    
    if (x < 0 or x >= width_ - x_offset or y < 0 or y >= height_ - y_offset)
    {
        throw FieldCoordinatesError("Field coordinates error placing");
    }

    if (isCollision(x, x_offset, y, y_offset, orientation))
    {
        throw ShipCollisionError("Ship collision error");   
    }

    int ship_index = 0;
    for (int i = x; i <= x + x_offset; ++i)
    {
        for (int j = y; j <= y + y_offset; ++j)
        {
            cells_[i][j].setShipSegment(ship, ship_index);
            ship_index++;
        }
    }
    ship.x = x;
    ship.y = y;
    ship.r = orientation;
}

int Field::getWidth() const noexcept
{
    return width_;
}

int Field::getHeight() const noexcept
{
    return height_;
}

Field::CellState Field::getCellState(int x, int y) const
{
    return cells_[x][y].getState();
}

bool Field::hasShip(int x, int y) const
{
    if (x < 0 or x >= width_ or y < 0 or y >= height_)
    {
        throw FieldCoordinatesError("Invalid cell coordinates");
    }

    return !cells_[x][y].isEmpty();
}


void Field::displaySegments() const noexcept
{
    for (int y = 0; y < getHeight(); ++y)
    {
        for (int x = 0; x < getWidth(); ++x)
        {
            auto cell = cells_[x][y];

            if (not cell.isEmpty())
            {
                std::cout << '(' << x << ", " << y << ')' << ": "
                          << static_cast<int>(cells_[x][y].getShipSegmentState()) 
                          << '\n';
            }
        }
    }
}


Ship Field::Cell::getShip() const
{   
    if (p_ship_ == nullptr)
    {
        throw std::logic_error("No ship here");
    }
    return *p_ship_;
}



Ship Field::getShip(int x, int y) const
{
    return cells_[x][y].getShip();
} 

void Field::Cell::setShip(Ship* ship)
{
    p_ship_ = ship;
}

void Field::Cell::setIndex(int index)
{
    segment_index_ = index;
}

void Field::setCell(int x, int y, Ship* p_ship, Field::CellState state, int index)
{
    cells_[x][y].setShip(p_ship);
    cells_[x][y].setState(state);
    cells_[x][y].setIndex(index);
}



std::ostream& operator<<(std::ostream& os, Field& field)
{
    for (int y = 0; y < field.getHeight(); ++y)
    {
        if (y != 0)
        {
            os << '\n';
        }

        for (int x = 0; x < field.getWidth(); ++x)
        {
            char cell = ' ';
            switch(field.getCellState(x, y)) 
            {
            case (Field::CellState::unknown):
                cell = ' ';
                break;
            case (Field::CellState::empty):
                cell = '.';
                break;
            case (Field::CellState::ship):
                switch (field.cells_[x][y].getShipSegmentState())
                {
                case Ship::SegmentState::intact:
                    cell = 'O';
                    break;
                case Ship::SegmentState::damaged:
                    cell = '+';
                    break;
                case Ship::SegmentState::destroyed:
                    cell = 'X';
                    break;
                }
                break;       
            default:
                cell = '?';
            }

            os << '[' << cell << ']';
        }
    }

    return os;
}

bool Field::Cell::isShip() const 
{
    return p_ship_ != nullptr;
}

bool Field::isShip(int x, int y) const 
{
    return cells_[x][y].isShip();
}

Ship::SegmentState Field::getShipSegmentState(int x, int y) const
{
    return cells_[x][y].getShipSegmentState();
}

void Field::display() const noexcept
{
    for (int y = 0; y < getHeight(); ++y)
    {
        if (y != 0)
        {
            std::cout << '\n';
        }

        for (int x = 0; x < getWidth(); ++x)
        {
            char cell = ' ';
            switch(getCellState(x, y)) 
            {
            case (Field::CellState::empty):
                cell = '.';
                break;
            case (Field::CellState::unknown):
                if (cells_[x][y].isEmpty())
                {
                    cell = ' ';
                    break;
                }
            case (Field::CellState::ship):
                switch (cells_[x][y].getShipSegmentState())
                {
                case Ship::SegmentState::intact:
                    cell = 'O';
                    break;
                case Ship::SegmentState::damaged:
                    cell = '+';
                    break;
                case Ship::SegmentState::destroyed:
                    cell = 'X';
                    break;
                }
                break;       
            default:
                cell = '?';
            }

            std::cout << '[' << cell << ']';
        }
    }
    std::cout << '\n';
}

json Field::Cell::toJson() const
{
    return json{
        {"state", state_},
        {"ship", p_ship_ == nullptr ? nullptr : p_ship_->toJson()},
        {"segment index", segment_index_}
    };
}

json Field::toJson() const
{
    json save_file;
    save_file["height"] = height_;
    save_file["width"] = width_;

    json cells = json::array();
    for (int x = 0; x < width_; ++x)
    {
        json col = json::array();
        for (int y = 0; y < height_; ++y)
        {
            col.push_back(cells_[x][y].toJson());
        }
        cells.push_back(col);
    }

    save_file["cells"] = cells;
    return save_file;
}