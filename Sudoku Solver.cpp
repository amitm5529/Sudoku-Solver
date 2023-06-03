#include <iostream>
using namespace std;

// Size of the Sudoku grid
const int N = 9;

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            cout << grid[row][col] << " ";
        cout << endl;
    }
}

// Function to check if the assigned digit is safe at a particular location
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if the number already exists in the current row
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num)
            return false;
    }

    // Check if the number already exists in the current column
    for (int i = 0; i < N; i++) {
        if (grid[i][col] == num)
            return false;
    }

    // Check if the number already exists in the current 3x3 grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num)
                return false;
        }
    }

    return true;
}

// Function to find the unassigned location and return the next empty cell
bool findEmptyLocation(int grid[N][N], int& row, int& col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0)
                return true;
        }
    }
    return false;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // Check if there is any unassigned location
    if (!findEmptyLocation(grid, row, col))
        return true; // All cells are assigned

    // Try different numbers from 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // Recursively solve the rest of the puzzle
            if (solveSudoku(grid))
                return true;

            // If the current assignment doesn't lead to a solution, backtrack and try another number
            grid[row][col] = 0;
        }
    }

    return false; // No solution exists
}

int main() {
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid)) {
        cout << "Solution:\n";
        printGrid(grid);
    }
    else {
        cout << "No solution exists.\n";
    }

    return 0;
}
