// C++ Headers
#include <algorithm>
#include <format>
#include <iostream>
#include <array>
#include <string>
#include <stdlib.h>
#include <vector>

// Local Headers
#include "sudoSolveConfig.h"

const int BOARD_ROW_NUM = 9; // number of rows on the board
const int BOARD_COLUMN_NUM = 9; // number of columns on the board

/// @brief Method to print the board to the `std::cout` stream
/// @param array The array representing the board
void printBoard(std::array<std::array<int, BOARD_COLUMN_NUM>, BOARD_ROW_NUM> array){
    for (int i = 0; i < array.size(); i++){
        for (int j = 0; j < array[i].size(); j++){
            if (j == array[i].size() - 1){
                std::cout << array[i][j] << "\n";
            } else {
                std::cout << array[i][j] << " ";
            }
        }
    }
}

/// @brief Method to get the index of a target element in a 1D vector
/// @param target The target element to look for
/// @param vector The vector to look through
/// @return The index of the target element in the vector (-1 if not found)
int getIndex(int target, std::vector<int> vector){
    for (int i = 0; i < vector.size(); i++){
        if (vector[i] == target){
            return i;
        }
    }
    return -1;
}

int main(){

    std::string first; // string to hold representation of the first board row
    std::string second; // string to hold representation of the second board row
    std::string third; // string to hold representation of the third board row
    std::string fourth; // string to hold representation of the fourth board row
    std::string fifth; // string to hold representation of the fifth board row
    std::string sixth; // string to hold representation of the sixth board row
    std::string seventh; // string to hold representation of the seventh board row
    std::string eighth; // string to hold representation of the eighth board row
    std::string ninth; // string to hold representation of the ninth board row

    // Board Input (0s indicate empty spot)
    first   = "200410007"; // first row of the board
    second  = "080700002"; // second row of the board
    third   = "000900050"; // third row of the board
    fourth  = "007200609"; // fourth row of the board
    fifth   = "010006500"; // fifth row of the board
    sixth   = "000000080"; // sixth row of the board
    seventh = "005602490"; // seventh row of the board
    eighth  = "006800025"; // eighth row of the board
    ninth   = "700540060"; // ninth row of the board

    std::array<std::array<int, BOARD_COLUMN_NUM>, BOARD_ROW_NUM> masterVector = {
        {{0,0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0,0}}}; // 2D array representing the state of the board

    int num_solved_elements = 0; // the number of unsolved elements remaining on the board
    int total_element_count = BOARD_ROW_NUM*BOARD_COLUMN_NUM; // total number of elements on the board

    std::cout << "Program Version: " << sudoSolve_VERSION_MAJOR << "." << sudoSolve_VERSION_MINOR << std::endl;

    // Populate masterVector with board input
    for (int i = 0; i < first.length(); i++){
        masterVector[0][i] = static_cast<int>(first[i] - '0');
        masterVector[1][i] = static_cast<int>(second[i] - '0');
        masterVector[2][i] = static_cast<int>(third[i] - '0');
        masterVector[3][i] = static_cast<int>(fourth[i] - '0');
        masterVector[4][i] = static_cast<int>(fifth[i] - '0');
        masterVector[5][i] = static_cast<int>(sixth[i] - '0');
        masterVector[6][i] = static_cast<int>(seventh[i] - '0');
        masterVector[7][i] = static_cast<int>(eighth[i] - '0');
        masterVector[8][i] = static_cast<int>(ninth[i] - '0');
    }

    int currentNumber;
    // Check to ensure valid entries in each row
    // TODO does not check columns or local groups
    for (int i = 0; i < masterVector.size(); i++){
        for (int j = 0; j < masterVector[0].size(); j++){
            currentNumber = masterVector[i][j];
            for (int k = 0; k < masterVector[0].size(); k++){
                if (currentNumber == 0){
                    NULL;
                }
                else if (currentNumber == masterVector[i][k] && j != k){
                    std::cout << "Error in Row " << i + 1 << "\n";
                    break;
                }
            }
        }
        num_solved_elements += std::count_if(masterVector[i].begin(), masterVector[i].end(), [](int i) { return i != 0; });
    }

    std::cout << std::format("INPUT BOARD ({}/{}):", num_solved_elements, total_element_count) << std::endl;
    printBoard(masterVector);

    int counter = 0; // the number of rows that have been solved
    int row = 0; // the row position of the current element under examination
    int column = 0; // the column position of the current element under examination
    int currentSpot; // the value of the current element under examination

    std::vector<int> candidates; // 1D vector of eligible candidates for the current board position

    while (counter < 9){ // while at least one row remains unsolved
        candidates = {1,2,3,4,5,6,7,8,9}; // reset the list of possible candidates
        if (row == 9){ // the end of the board has been reached and not solved
            break;
        }
        if (std::find(masterVector[row].begin(), masterVector[row].end(), 0) == masterVector[row].end()){ // if the row has been completely solved
            if (row == 8){ // at the end of the board, update the solution counter
                counter++;
            } else { // not at the end of the board, update both the solution counter and row number
                counter++;
                row++;
            }
        } else {
            currentSpot = masterVector[row][column]; // current board position under examination
            if (currentSpot != 0 && column == 8){ // if at the right edge of the board and the spot is filled, reset column and increase row
                column = 0;
                row++;
            } else if (currentSpot != 0 && column != 8){ // if at a filled spot that is not the right edge, increase column
                column++;
            } else { // the spot is not filled
                // Removing candidates based on other elements in shared column
                for (int i = 0; i < masterVector.size(); i++){
                    if (masterVector[i][column] != 0 && std::find(candidates.begin(), candidates.end(), masterVector[i][column]) != candidates.end()){
                        candidates.erase(candidates.begin() + getIndex(masterVector[i][column], candidates));
                    }
                }
                // Removing candidates based on other elements in shared row
                for (int i = 0; i < masterVector.size(); i++){
                    if (masterVector[row][i] != 0 && std::find(candidates.begin(), candidates.end(), masterVector[row][i]) != candidates.end()){
                        candidates.erase(candidates.begin() + getIndex(masterVector[row][i], candidates));
                    }
                }
                // Removing candidates based on local groups (3x3)
                if (column == 0 || column == 3 || column == 6){ // if first column in the local group
                    if (row == 0 || row == 3 || row == 6){ // if first row in the local group
                        for (int i = 0; i < 3; i++){
                            for (int j = 0; j < 3; j++){
                                if (masterVector[row + i][column + j] != 0 && std::find(candidates.begin(), candidates.end(), masterVector[row + i][column + j]) != candidates.end()){
                                candidates.erase(candidates.begin() + getIndex(masterVector[row + i][column + j], candidates));
                                }
                            }
                        }
                    } else if (row == 1 || row == 4 || row == 7){ // if second row in the local group
                        for (int i = -1; i < 2; i++){
                            for (int j = 0; j < 3; j++){
                                if (masterVector[row + i][column + j] != 0 && std::find(candidates.begin(), candidates.end(), masterVector[row + i][column + j]) != candidates.end()){
                                    candidates.erase(candidates.begin() + getIndex(masterVector[row + i][column + j], candidates));
                                }
                            }
                        }
                    } else { // third row in the local group
                        for (int i = -2; i < 1; i++){
                            for (int j = 0; j < 3; j++){
                                if (masterVector[row + i][column + j] != 0 && std::find(candidates.begin(), candidates.end(), masterVector[row + i][column + j]) != candidates.end()){
                                    candidates.erase(candidates.begin() + getIndex(masterVector[row + i][column + j], candidates));
                                }
                            }
                        }
                    }
                } else if (column == 1 || column == 4 || column == 7){ // if second column in the local group
                    if (row == 0 || row == 3 || row == 6){ // if first row in the local group
                        for (int i = 0; i < 3; i++){
                            for (int j = -1; j < 2; j++){
                                if (masterVector[row + i][column + j] != 0 && std::find(candidates.begin(), candidates.end(), masterVector[row + i][column + j]) != candidates.end()){
                                    candidates.erase(candidates.begin() + getIndex(masterVector[row + i][column + j], candidates));
                                }
                            }
                        }
                    } else if (row == 1 || row == 4 || row == 7){ // if second row in the local group
                        for (int i = -1; i < 2; i++){
                            for (int j = -1; j < 2; j++){
                                if (masterVector[row + i][column + j] != 0 && std::find(candidates.begin(), candidates.end(), masterVector[row + i][column + j]) != candidates.end()){
                                    candidates.erase(candidates.begin() + getIndex(masterVector[row + i][column + j], candidates));
                                }
                            }
                        }
                    } else { // third row in the local group
                        for (int i = -2; i < 1; i++){
                            for (int j = -1; j < 2; j++){
                                if (masterVector[row + i][column + j] != 0 && std::find(candidates.begin(), candidates.end(), masterVector[row + i][column + j]) != candidates.end()){
                                    candidates.erase(candidates.begin() + getIndex(masterVector[row + i][column + j], candidates));
                                }
                            }
                        }
                    }
                } else { // third column in the local group
                    if (row == 0 || row == 3 || row == 6){ // if first row in the local group
                        for (int i = 0; i < 3; i++){
                            for (int j = -2; j < 1; j++){
                                if (masterVector[row + i][column + j] != 0 && std::find(candidates.begin(), candidates.end(), masterVector[row + i][column + j]) != candidates.end()){
                                    candidates.erase(candidates.begin() + getIndex(masterVector[row + i][column + j], candidates));
                                }
                            }
                        }
                    } else if (row == 1 || row == 4 || row == 7){ // if second row in the local group
                        for (int i = -1; i < 2; i++){
                            for (int j = -2; j < 1; j++){
                                if (masterVector[row + i][column + j] != 0 && std::find(candidates.begin(), candidates.end(), masterVector[row + i][column + j]) != candidates.end()){
                                    candidates.erase(candidates.begin() + getIndex(masterVector[row + i][column + j], candidates));
                                }
                            }
                        }
                    } else { // third row in the local group
                        for (int i = -2; i < 1; i++){
                            for (int j = -2; j < 1; j++){
                                if (masterVector[row + i][column + j] != 0 && std::find(candidates.begin(), candidates.end(), masterVector[row + i][column + j]) != candidates.end()){
                                    candidates.erase(candidates.begin() + getIndex(masterVector[row + i][column + j], candidates));
                                }
                            }
                        }
                    }
                }
                // If there is only one candidate left, it has to go in the current spot
                if (candidates.size() == 1){
                    masterVector[row][column] = candidates[0]; // update the masterVector with the newly solved element
                    row = 0; // reset the row position
                    column = 0; // reset the column position
                    counter = 0; // reset the solution counter
                } else if (column == 8){
                    column = 0; // reset the column position
                    row++; // increment the row position
                } else {
                    column++; // increment the column position
                }
            }
        }
    }
    if (row == 9){ // if the end of the board has been reached and not solved
        std::cout << "INCOMPLETE SOLUTION:" << std::endl;
    } else { // the board has been solved
        std::cout << "BOARD SOLVED:" << std::endl;
    }
    printBoard(masterVector);
}