#include "Snake.hpp"

/**
 * @brief Returns the position of a Snake segment at index.
 * 
 * @param index The index of the segment.
 * @return std::pair<int, int> 
 */
Tile Snake::get_segment_position(int index) const {
	return segments[index];
}

/**
 * @brief Snake moves by one.
 * 
 */
void Snake::move() {
	// Erase old values of occupied_tiles
    for (int i = 0; i < get_length(); i++) {
        occupied_tiles.erase(get_segment_position(i));
    }

	// Move all body segments.
	for (int i = length - 1; i > 0; i--) {
		segments[i] = segments[i - 1];
	}

	// Move head row-column position
	switch (head_dir)
	{
	case Direction::east:
		segments[0].second++;
		break;
	case Direction::west:
		segments[0].second--;
		break;
	case Direction::north:
		segments[0].first--;
		break;
	case Direction::south:
		segments[0].first++;
		break;
	
	default:
		break;
	}

	// Add all segments into occupied_tiles
	for (int i = 0; i < get_length(); i++) {
        occupied_tiles.insert(get_segment_position(i));
    }
}

/**
 * @brief Sets the head of the snake to the new direction. However, returns
 * immediately if the new direction is equal or opposite to the current head direction.
 * 
 * @param new_dir The new direction of the head.
 */
void Snake::update_head_dir(Direction new_dir) {
	// These two if-statements ensure that the snake does not go against the direction
	// in which it's moving, and does not need to update if new_dir == head_dir.
	if ((head_dir == Direction::east || head_dir == Direction::west)
			&& (new_dir == Direction::east || new_dir == Direction::west)) {
		return;
	}
	if ((head_dir == Direction::north || head_dir == Direction::south)
			&& (new_dir == Direction::north || new_dir == Direction::south)) {
		return;
	}
	
	head_dir = new_dir;
}

/**
 * @brief Grows the snake by one.
 * 
 */
void Snake::grow() {
	length++;
	segments[length - 1] = segments[length - 2];
}

/**
 * @brief Temporary print function, just for debugging.
 * 
 */
void Snake::print() {

	for (int i = 0; i < get_length(); i++) {
		Tile tile = segments[i];
		std::cout << "(" << std::to_string(tile.first) << "," << std::to_string(tile.second) << ")"; 
	}
	std::cout << std::endl;
}