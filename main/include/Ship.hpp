#ifndef SHIP_HPP
#define SHIP_HPP


#include <vector> 
#include <iostream>
#include <nlohmann/json.hpp>


using json = nlohmann::json; 


constexpr int max_ship_len = 4;
constexpr int min_ship_len = 1;


class Ship
{
public:
    enum class SegmentState
    {
        destroyed,
        damaged,
        intact
    };

    enum class Orientation
    {
        horizontal,
        vertical
    };

    explicit Ship(int t_length);
    Ship(std::vector<SegmentState> segment_states, int x, int y, Orientation r);
    ~Ship() = default;
    SegmentState getSegmentState(int index) const;
    bool isAlive() const noexcept;
    int getLength() const noexcept;
    void takeDamage(int index, int damage);

    json toJson() const;

    static const int min_length{1};
    static const int max_length{4};

    int x{0};
    int y{0};
    Orientation r{Orientation::horizontal};

private:
    class Segment
    {
    public:
        Segment(SegmentState state);
        ~Segment() = default;
        void takeDamage(int damage);
        SegmentState getState() const noexcept;

    private:
        SegmentState state_;
    };

    std::vector<Segment> segments_;
};

std::ostream& operator<<(std::ostream& os, const Ship& ship);

#endif //SHIP_HPP