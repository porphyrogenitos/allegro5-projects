#include "Snake.hpp"

/**
 * @brief Returns the direction of velocity of a Snake segment.
 * 
 * @param index The index of the segment (in direction_arr).
 * @return Direction 
 */
Direction Snake::get_segment_direction(int index) const {
	return direction_arr[index];
}

/**
 * @brief Returns the positional direction of a Snake segment relative to the segment in front.
 * 
 * @param index The index of the segment (in direction_arr).
 * @return Direction 
 */
Direction Snake::get_segment_position(int index) const {
	// The position of a segment S1 relative to the segment in front S0 is the opposite
	// direction of S0.
	return get_opposite_dir(direction_arr[index]);
}

/**
 * @brief Snake moves by one. Updates the direction of each segment.
 * 
 */
void Snake::move() {
	for (int i = length - 1; i > 0; i--) {
		direction_arr[i] = direction_arr[i - 1];
	}
}

/**
 * @brief Sets the head of the snake (direction_arr[0]) to the new direction. However, returns
 * immediately if the new direction is equal or opposite to the head direction.
 * 
 * @param new_dir The new direction of the head.
 */
void Snake::update_head_dir(Direction new_dir) {
	Direction head_dir = direction_arr[0];

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
	
	direction_arr[0] = new_dir;
}

/**
 * @brief Grows the snake by one.
 * 
 */
void Snake::grow() {
	length++;

	// The direction of the new tail segment is set to the same as the old tail segment.
	direction_arr[length - 1] = direction_arr[length - 2];
}

/**
 * @brief Temporary print function, just for debugging.
 * 
 */
void Snake::print() {

	for (int i = 0; i < get_length(); i++) {
		std::string dir = direction_to_string(direction_arr[i]);
		std::cout << std::to_string(i) << "," << dir << " "; 
	}
	std::cout << std::endl;
}