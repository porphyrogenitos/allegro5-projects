#pragma once

#include <string>

enum class Direction {
    north,
    south,
    east,
    west
};

std::string direction_to_string(Direction direction);

Direction get_opposite_dir(Direction direction);
