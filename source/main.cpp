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

int main(int argc, char **argv){

    // ======================== COMMAND LINE ARGUMENTS ========================
    // Create `options_description` object for defining program options
    boost::program_options::options_description description ("Options");
    // Add program options to the `options_description` object
    description.add_options()
                ("help,h", "Display this help message.");
    // Create `variables_map` object for storing program options (name-value)
    boost::program_options::variables_map vm;
    // Process command line arguments and store results in `variables_map` object
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, description), vm);
    // Perform final option processing (e.g. apply default values)
    boost::program_options::notify(vm);

    // Check for "help" option presence
    if (vm.count("help")) {
        std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
        std::cout << description << std::endl;
        return 1;
    }
    // ====================== END COMMAND LINE ARGUMENTS ======================

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