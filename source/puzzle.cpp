// Local Headers
#include "puzzle.hpp"

std::pair<bool, int> Puzzle::check_state() {

    int current_number;
    std::pair<bool, int> return_pair(true, 0);

    // Determine number of filled elements on the board
    for (int i = 0; i < m_board.size(); i++){ // iterate through rows on the board
        return_pair.second += std::count_if(m_board[i].begin(), m_board[i].end(), [](int i) { return i != 0; });
    }

    // Check to ensure valid entries in each row
    for (int row_0 = 0; row_0 < m_board.size(); row_0++){ // iterate through rows on the board
        for (int column_0 = 0; column_0 < m_board[row_0].size(); column_0++){ // iterate through columns on the board
            current_number = m_board[row_0][column_0];
            if (current_number == 0) {
                NULL;
            } else {
                // Check validity between rows (i.e., check the column)
                for (int row_1 = 0; row_1 < m_board.size(); row_1++) { // iterate through rows on the board
                    if (current_number == m_board[row_1][column_0] && row_0 != row_1) {
                        return_pair.first = false; // the state of the board is not valid
                        std::cerr << "Error in column: " << column_0 + 1 << std::endl;
                        return return_pair;
                    }
                }
                // Check validity between columns (i.e., check the row)
                for (int column_1 = 0; column_1 < m_board[row_0].size(); column_1++){ // iterate through columns on the board
                    if (current_number == m_board[row_0][column_1] && column_0 != column_1){
                        return_pair.first = false; // the state of the board is not valid
                        std::cerr << "Error in row: " << row_0 + 1 << std::endl;
                        return return_pair;
                    }
                }
                // Check validity among each local group
                int row_modulo_neg = -std::abs(row_0 % 3);
                int column_modulo_neg = -std::abs(column_0 % 3);
                for (int row_1 = row_modulo_neg; row_1 < row_modulo_neg + 3; row_1++) {
                    for (int column_1 = column_modulo_neg; column_1 < column_modulo_neg + 3; column_1++) {
                        if (row_1 == 0 && column_1 == 0) {
                            NULL;
                        } else if (current_number == m_board[row_0 + row_1][column_0 + column_1]) {
                            return_pair.first = false; // the local group is not valid
                            std::cerr << "Error in local group: (" << row_0/3 << ", " << column_0/3 << ")" << std::endl;
                            return return_pair;
                        }
                    }
                }
            }
        }
    }
    return return_pair;
}

int Puzzle::get_index(const int &target, const std::vector<int> &vector) {
    std::vector<int>::const_iterator target_element_it = std::find(vector.begin(), vector.end(), target); 
    return std::distance(vector.begin(), target_element_it);
}

bool Puzzle::populate_board(const std::array<std::string, BOARD_ROW_NUM> &rows) {
    for (int i = 0; i < rows.size(); i++) {
        m_board[0][i] = static_cast<int>(rows[0][i] - '0'); // populate first row
        m_board[1][i] = static_cast<int>(rows[1][i] - '0'); // populate second row
        m_board[2][i] = static_cast<int>(rows[2][i] - '0'); // populate third row
        m_board[3][i] = static_cast<int>(rows[3][i] - '0'); // populate fourth row
        m_board[4][i] = static_cast<int>(rows[4][i] - '0'); // populate fifth row
        m_board[5][i] = static_cast<int>(rows[5][i] - '0'); // populate sixth row
        m_board[6][i] = static_cast<int>(rows[6][i] - '0'); // populate seventh row
        m_board[7][i] = static_cast<int>(rows[7][i] - '0'); // populate eighth row
        m_board[8][i] = static_cast<int>(rows[8][i] - '0'); // populate ninth row
    }
    m_state_pair = check_state(); // check the state of the input board (to ensure valid configuration)
    return m_state_pair.first;
}

Puzzle::Puzzle() {
    m_board = {{{0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0,0}}};
    m_candidates = {1,2,3,4,5,6,7,8,9};
}

void Puzzle::print_board() {
    for (int i = 0; i < m_board.size(); i++){
        for (int j = 0; j < m_board[i].size(); j++){
            if (j == m_board[i].size() - 1){
                std::cout << m_board[i][j] << "\n";
            } else {
                std::cout << m_board[i][j] << " ";
            }
        }
    }
}

void Puzzle::solve_board() {

    std::cout << "INPUT BOARD (" << m_state_pair.second << "/" \
                                 << TOTAL_ELEMENT_COUNT << "):" << std::endl;
    print_board();

    int counter = 0; // the number of rows that have been solved
    int row = 0; // the row position of the current element under examination
    int column = 0; // the column position of the current element under examination
    int currentSpot; // the value of the current element under examination

    while (m_state_pair.second < TOTAL_ELEMENT_COUNT) { // while at least one row remains unsolved
        m_candidates = {1,2,3,4,5,6,7,8,9}; // reset the list of possible candidates
        if (row == 9){ // the end of the board has been reached and not solved
            break;
        }
        if (std::find(m_board[row].begin(), m_board[row].end(), 0) == m_board[row].end()){ // if the row has been completely solved
            if (row == 8){ // at the end of the board, update the solution counter
                NULL;
            } else { // not at the end of the board, update both the solution counter and row number
                row++;
            }
        } else {
            currentSpot = m_board[row][column]; // current board position under examination
            if (currentSpot != 0 && column == 8){ // if at the right edge of the board and the spot is filled, reset column and increase row
                column = 0;
                row++;
            } else if (currentSpot != 0 && column != 8){ // if at a filled spot that is not the right edge, increase column
                column++;
            } else { // the spot is not filled
                // Removing candidates based on other elements in shared column
                for (int i = 0; i < m_board.size(); i++){
                    if (m_board[i][column] != 0 && std::find(m_candidates.begin(), m_candidates.end(), m_board[i][column]) != m_candidates.end()){
                        m_candidates.erase(m_candidates.begin() + get_index(m_board[i][column], m_candidates));
                    }
                }
                // Removing candidates based on other elements in shared row
                for (int i = 0; i < m_board.size(); i++){
                    if (m_board[row][i] != 0 && std::find(m_candidates.begin(), m_candidates.end(), m_board[row][i]) != m_candidates.end()){
                        m_candidates.erase(m_candidates.begin() + get_index(m_board[row][i], m_candidates));
                    }
                }
                // Removing candidates based on local groups (3x3)
                int row_modulo_neg = -std::abs(row % 3); // 0, -1, or -2
                int column_modulo_neg = -std::abs(column % 3); // 0, -1, or -2
                for (int i = row_modulo_neg; i < row_modulo_neg + 3; i++){
                    for (int j = column_modulo_neg; j < column_modulo_neg + 3; j++){
                        if (m_board[row + i][column + j] != 0 && std::find(m_candidates.begin(), m_candidates.end(), m_board[row + i][column + j]) != m_candidates.end()){
                            m_candidates.erase(m_candidates.begin() + get_index(m_board[row + i][column + j], m_candidates));
                        }
                    }
                }
                // If there is only one candidate left, it has to go in the current spot
                if (m_candidates.size() == 1){
                    m_board[row][column] = m_candidates[0]; // update the m_board with the newly solved element
                    row = 0; // reset the row position
                    column = 0; // reset the column position
                } else if (column == 8){
                    column = 0; // reset the column position
                    row++; // increment the row position
                } else {
                    column++; // increment the column position
                }
                m_state_pair = check_state(); // check the state of the board
            }
        }
    }
    if (row == 9){ // if the end of the board has been reached and not solved
        std::cout << "INCOMPLETE SOLUTION (" << m_state_pair.second << "/" \
                                             << TOTAL_ELEMENT_COUNT << "):" << std::endl;
    } else { // the board has been solved
        std::cout << "BOARD SOLVED:" << std::endl;
    }
    print_board();
}