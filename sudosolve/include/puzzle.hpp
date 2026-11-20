// C++ Headers
#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

// Constants
const int BOARD_ROW_NUM = 9; // number of rows on the board
const int BOARD_COLUMN_NUM = 9; // number of columns on the board
const int TOTAL_ELEMENT_COUNT = BOARD_ROW_NUM*BOARD_COLUMN_NUM; // total number of elements on the board

/**
 * @class Puzzle
 * @brief Contains the members and methods required to solve the puzzle.
 */
class Puzzle {

    public:
        /**
         * @brief Method to populate the `m_board` member variable
         *
         * @param rows A `std::array` of `std::string` representing the rows of the board
         * @return true The board is valid
         * @return false The board is invalid
         */
        bool populate_board(const std::array<std::string, BOARD_ROW_NUM>& rows);

        /**
         * @brief Method to print the board (// TODO generalize to any output stream?)
         */
        void print_board();

        /**
         * @brief Construct a new Puzzle object
         */
        Puzzle();

        /**
         * @brief Method to solve the board
         */
        void solve_board();

    private:
        /**
         * @brief Method to determine whether the state of the board is valid and
         * the number of filled elements.
         *
         * @return std::pair<bool, int> `std::pair` of a `bool` representing the
         * validity of the board (`true` for valid; `false` otherwise) and an
         * `int` representing the number of filled elements
         */
        std::pair<bool, int> check_state();

        /**
         * @brief Method to obtain the index of a `target` element in a 1D `vector`.
         * Essentially just a wrapper for `std::find` and `std::distance`.
         *
         * @param target The element for which to search `vector`
         * @param vector The `vector` in which to search for `target`
         * @return int The index location of `target` in `vector`; `vector.end()`
         * if `target` is not in `vector`
         */
        int get_index(const int& target, const std::vector<int>& vector);

        /**
         * @brief 2D array representing the state of the board
         */
        std::array<std::array<int, BOARD_COLUMN_NUM>, BOARD_ROW_NUM> m_board;

        /**
         * @brief 1D vector of eligible candidates for an empty board position
         */
        std::vector<int> m_candidates;

        /**
         * @brief `std::pair` holding the validity of the board (`bool`) and
         * the number of solved elements (`int`)
         */
        std::pair<bool, int> m_state_pair;
};