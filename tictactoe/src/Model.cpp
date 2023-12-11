#include "Model.h"

// Update board with the move of cur_player, checking first if they can even make a move.
// Then check if the cur_player has won.
// If they didn't win, update cur_player to the next player turn.
void Model::play(int r, int c) {
    if (is_finished || !is_slot_available(r, c))
        return;

    board[r][c] = cur_player;

    // Check row
    for (int i = 0; i < board_size; i++) {
        if (board[i][c] != cur_player)
            break;
        if (i == board_size - 1) {
            winner = cur_player;
            is_finished = true;
            return;
        }
    }

    // Check column
    for (int i = 0; i < board_size; i++) {
        if (board[r][i] != cur_player)
            break;
        if (i == board_size - 1) {
            winner = cur_player;
            is_finished = true;
            return;
        }
    }

    // Check diagonal (from top-left corner)
    for (int i = 0; i < board_size; i++) {
        if (board[i][i] != cur_player)
            break;
        if (i == board_size - 1) {
            winner = cur_player;
            is_finished = true;
            return;
        }
    }

    // Check diagonal (from top-right corner)
    for (int i = 0; i < board_size; i++) {
        if (board[i][board_size - i] != cur_player)
            break;
        if (i == board_size - 1) {
            winner = cur_player;
            is_finished = true;
            return;
        }
    }

    num_plays++;

    if (cur_player == 'X')
        cur_player = 'O';
    else
        cur_player = 'X';

    if (board_is_full())
        is_finished = true;
}