#pragma once

class Model {
    private:
        char board[3][3]
        {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
        };
        char winner {' '};
        char cur_player {'X'};
        int num_plays = {0};
        int board_size = 3;
        bool is_finished = false;

    public:
        char get_symbol(int r, int c) {
            return board[r][c];
        }
        int get_board_size() {
            return board_size;
        }

        char get_cur_player() {
            return cur_player;
        }

        char get_winner() {
            return winner;
        }

        bool has_winner() {
            return get_winner() == 'X' || get_winner() == 'O';
        }

        bool board_is_full() {
            return num_plays == 9;
        }
        void play(int r, int c);

        char is_slot_available(int r, int c) {
            return board[r][c] == ' ';
        }

};