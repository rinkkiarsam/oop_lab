#include <iostream>
#include <vector>
#include <stdexcept>

#include "Ship.hpp"
#include "GameException.hpp"


Ship::Segment::Segment(Ship::SegmentState state = Ship::SegmentState::intact)
    : state_(state) {};

Ship::SegmentState Ship::Segment::getState() const noexcept
{
    return state_;
}

void Ship::Segment::takeDamage(const int damage)
{
    if (damage < 0)
    {
        throw DamageError("Damage error");
    }
    
    else if (damage >= 2)
    {
        state_ = Ship::SegmentState::destroyed;
    }

    else if (damage == 1 and state_ == Ship::SegmentState::intact)
    {
        state_ = Ship::SegmentState::damaged;
    }

    else if (damage == 1 and state_ == Ship::SegmentState::damaged)
    {
        state_ = Ship::SegmentState::destroyed;
    }
}

Ship::Ship(int length)
{
    if (length < min_length or length > max_length)
    {
        throw std::length_error("Invalid ship size");
    }

    for (int i = 0; i < length; ++i)
    {
        segments_.emplace_back();
    }
}

Ship::Ship(std::vector<SegmentState> segment_states, int x, int y, Orientation r)
{
    std::vector<Segment> segments;
    for (const auto& state : segment_states)
    {
        segments.push_back(Segment(state));
    }
    segments_ = segments;
    this->x = x;
    this->y = y;
    this->r = r;
}


int Ship::getLength() const noexcept
{
    return static_cast<int>(segments_.size());
}

Ship::SegmentState Ship::getSegmentState(int index) const
{
    if (index < 0 or index >= getLength())
    {
        throw std::length_error("Invalid ship segment index");
    }

    return segments_[index].getState();
}

bool Ship::isAlive() const noexcept
{
    for (const auto& segment : segments_)
    {
        if (segment.getState() != Ship::SegmentState::destroyed)
        {
            return true;
        }
    }

    return false;
}

void Ship::takeDamage(int index, int damage)
{
    if (index < 0 or index >= getLength())
    {
        throw std::length_error("Invalid ship segment index");
    }

    segments_[index].takeDamage(damage);
}

std::ostream& operator<<(std::ostream& os, const Ship& ship)
{
    os << "ship: ";

    for (int i = 0; i < ship.getLength(); ++i)
    {
        os << ' ' << static_cast<int>(ship.getSegmentState(i));
    }

    return os;
}


// Might blow errythang up
json Ship::toJson() const
{
    std::vector<Ship::SegmentState> states;
    for (const auto& segment : segments_)
    {
        states.push_back(segment.getState());
    }
    return json{
        {"segment states", states},
        {"r", static_cast<int>(r)},
        {"x", x},
        {"y", y}
        };
}