#pragma once

enum class Direction {
    north,
    south,
    east,
    west
};

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
