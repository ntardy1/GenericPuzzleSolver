// C++ Headers
#include <algorithm>
#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <array>
#include <string>
#include <stdlib.h>
#include <vector>

// Local Headers
#include "sudoSolveConfig.h"
#include "puzzle.hpp"

int main(){

    std::string line; // string to hold each line of the input file as it is read
    std::array<std::string, BOARD_ROW_NUM> rows;
    std::ifstream puzzles_file("../input/puzzles.txt"); // `std::ifstream` object to associate with the input file

    if (!puzzles_file.is_open()) { // if the file was not successfully opened
        std::cerr << "Error opening input file" << std::endl;
        return -1;
    }

    int idx = 0; // index
    while (std::getline(puzzles_file, line)) {
        rows[idx] = {{line}};
        idx++;
    }

    puzzles_file.close(); // close the file to release resources

    Puzzle puzzle; // instantiate Puzzle object with default constructor

    std::cout << "sudoSolve Version: v" << sudoSolve_VERSION_MAJOR << "." \
                                        << sudoSolve_VERSION_MINOR << std::endl;

    if (!puzzle.populate_board(rows)) {
        return -1;
    };
    puzzle.solve_board();

    return 0;
}