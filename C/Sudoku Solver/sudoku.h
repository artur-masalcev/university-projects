/**
Sudoku solver
Author: Artur Masalcev(artur.masalcev@stud.mif.vu.lt)

Overview:
This program solves 9x9 sudoku board from a input.txt file and prints out the solution to solution.txt file
This implementation supports protocol mode, that allows the user to get a overview of algorithm execution. To enable protocol
    mode PROTOCOL_MODE variable should be true, protocol will be printed in the separate txt file.

Description and list of supported operations:
_Bool is_valid_sudoku(char board[BOARD_SIZE][BOARD_SIZE]); - check whether the 9x9 board is a valid sudoku board
_Bool is_valid_placement(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) - check whether the placement in the particular
    row and column is valid
void solve_sudoku(char board[BOARD_SIZE][BOARD_SIZE]) - driver function needed to be used by user to solve 9x9 sudoku board
_Bool solve_sudoku_inner(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, FILE *protocol_file, int *steps_count, int *level) -
    recursively solves the sudoku board using backtracking approach. DO NOT USE IT IN YOUR CODE, you should pass the board to
    solve_sudoku function

Error codes:
No error codes

Constants:
PROTOCOL_MODE - modify this variable to turn on and off the protocol mode.

Used libraries:
<stdio.h> - file i/o
<string.h> - used for managing arrays (memset function)
<stdbool.h> - boolean data type
*/

#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdio.h>

#define BOARD_SIZE 9
#define SUBBOX_SIZE 3
#define PROTOCOL_MODE true //set to true if the protocol is needed

_Bool is_valid_sudoku(char board[BOARD_SIZE][BOARD_SIZE]);
_Bool is_valid_placement(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);
void solve_sudoku(char board[BOARD_SIZE][BOARD_SIZE]);
_Bool solve_sudoku_inner(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, FILE *protocol_file, int *steps_count, int *level);

#endif
