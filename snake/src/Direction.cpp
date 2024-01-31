#include "Direction.hpp"

std::string direction_to_string(Direction direction) {
    switch (direction) {
        case Direction::north:
            return "north";
        case Direction::south:
            return "south";
        case Direction::east:
            return "east";
        case Direction::west:
            return "west";
        default:
            return "";
    }
}

Direction get_opposite_dir(Direction direction) {
    switch (direction) {
        case Direction::north:
            return Direction::south;
        case Direction::south:
            return Direction::north;
        case Direction::east:
            return Direction::west;
        case Direction::west:
            return Direction::east;
        default:
            return direction;
    }
}
