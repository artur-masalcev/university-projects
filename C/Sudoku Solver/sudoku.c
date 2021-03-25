#include "sudoku.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool is_valid_sudoku(char board[BOARD_SIZE][BOARD_SIZE]){
    bool used_numbers[9] = {false};

    //Check for all rows
    for(int i = 0; i < BOARD_SIZE; ++i){
        for(int j = 0; j < BOARD_SIZE; ++j){
            if(board[i][j] > '0' && board[i][j] <= '9'){
                int pos = board[i][j] - '0' - 1;
                if(used_numbers[pos] == true)return false;
                else used_numbers[pos] = true;
            }
        }
        memset(used_numbers, false, sizeof(used_numbers));
    }

    //Check for all columns
    for(int i = 0; i < BOARD_SIZE; ++i){
        for(int j = 0; j < BOARD_SIZE; ++j){
            if(board[j][i] > '0' && board[j][i] <= '9'){
                int pos = board[j][i] - '0' - 1;
                if(used_numbers[pos] == true)return false;
                else used_numbers[pos] = true;
            }
        }
        memset(used_numbers, false, sizeof(used_numbers));
    }

    //Check for all sub boxes
    int offset_row = 0;
    int offset_col = 0;

    while(offset_col < BOARD_SIZE){
    while(offset_row < BOARD_SIZE){
    for(int i = offset_row; i < offset_row + SUBBOX_SIZE; ++i){
        for(int j = offset_col; j < offset_col + SUBBOX_SIZE; ++j){
            if(board[j][i] > '0' && board[j][i] <= '9'){
                int pos = board[j][i] - '0' - 1;
                if(used_numbers[pos] == true)return false;
                else used_numbers[pos] = true;
            }
        }
    }
        memset(used_numbers, false, sizeof(used_numbers));
        offset_row += SUBBOX_SIZE;
    }
        offset_col += SUBBOX_SIZE;
        offset_row = 0;
    }

    return true;
}

bool is_valid_placement(char board[BOARD_SIZE][BOARD_SIZE], int row, int col){
    //Check row and column
    for(int i = 0; i < BOARD_SIZE; ++i){
        if(board[row][i] == board[row][col] && col != i)return false;
        if(board[i][col] == board[row][col] && row != i)return false;
    }

    //Check 3x3 square
    int start_row;
    int start_col;

    if(row >= 6)start_row = 6;
    else if(row >= 3)start_row = 3;
    else start_row = 0;

    if(col >= 6)start_col = 6;
    else if(col >= 3)start_col = 3;
    else start_col = 0;

    for (int i = 0; i < SUBBOX_SIZE; i++){
        for (int j = 0; j < SUBBOX_SIZE; j++){
            if(i + start_row == row && j + start_col == col)continue;
            if(board[i + start_row][j + start_col] == board[row][col])return false;
        }
    }

    return true;
}

void solve_sudoku(char board[BOARD_SIZE][BOARD_SIZE]){
    FILE *protocol_file = NULL;

    int steps_count = 0;
    int level = 0;

    //Print the first part of the protocol if needed//
    if(PROTOCOL_MODE){
        char protocol_filename[] = "protocol.txt";
        protocol_file = fopen(protocol_filename, "w");
        if(protocol_file != NULL){
            fputs("Artur Masalcev. Software Engineering 1 year 4 group  1 subgroup \nMain task 2. Variant 8\nThis program solves 9x9 sudoku board using backtracking technique\n\n",
                protocol_file);
            fputs("PART 1 - INPUT\n\n", protocol_file);
            fputs("  Y, ROW\n  ^\n", protocol_file);
            for(int i = 0; i < BOARD_SIZE; ++i){
                for(int j = 0; j < BOARD_SIZE; ++j){
                    if(j == 0)fprintf(protocol_file, "%d |  ", BOARD_SIZE - i);
                    fputc(board[i][j], protocol_file);
                    if(j != BOARD_SIZE - 1)fputc(' ', protocol_file);
                }
                if(i != BOARD_SIZE - 1)fputs("\n", protocol_file);
            }
            fputs("\n   ---------------------> X, COLUMN\n     1 2 3 4 5 6 7 8 9\n", protocol_file);
            fputs("\n\nPART 2 - EXECUTION\n\n", protocol_file);
        }
        else printf("Warning: cannot create protocol file");
    }

    solve_sudoku_inner(board, 0, 0, protocol_file, &steps_count, &level);

    if(PROTOCOL_MODE && protocol_file != NULL){
        fputs("\nPART 3 - RESULT\n\n", protocol_file);
        fprintf(protocol_file, "Steps count: %d\n", steps_count);
        fputs("Solution:\n\n", protocol_file);

        fputs("  Y, ROW\n  ^\n", protocol_file);
        for(int i = 0; i < BOARD_SIZE; ++i){
            for(int j = 0; j < BOARD_SIZE; ++j){
                if(j == 0)fprintf(protocol_file, "%d |  ", BOARD_SIZE - i);
                fputc(board[i][j], protocol_file);
                if(j != BOARD_SIZE - 1)fputc(' ', protocol_file);
            }
            if(i != BOARD_SIZE - 1)fputs("\n", protocol_file);
        }
        fputs("\n   ---------------------> X, COLUMN\n     1 2 3 4 5 6 7 8 9\n", protocol_file);
    }
}

bool solve_sudoku_inner(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, FILE *protocol_file, int *steps_count, int *level){
    //Base case
    if(row == BOARD_SIZE - 1 && col == BOARD_SIZE - 1){
        if(board[row][col] != '.')return true;
        else{
            for(int i = 1; i <= 9; ++i){
                board[row][col] = i + '0';
                if(is_valid_placement(board, row, col)){
                    fprintf(protocol_file, "%5d)", *steps_count + 1);
                    for(int i = 0; i < *level; ++i)fputc('-', protocol_file);
                    fprintf(protocol_file, "Row: %d, Column: %d. Placing %d\n", row + 1, col + 1, i);
                    return true;
                }
            }
        }
        return false;
    }

    //Check if it is needed to move to the next row
    if(col == BOARD_SIZE){
        ++row;
        col = 0;
    }

    //Skip if the number is already placed
    if(board[row][col] != '.')return solve_sudoku_inner(board, row, col + 1, protocol_file, steps_count, level);

    //From number 1 to 9 try all the possible combinations
    for(int i = 1; i <= 9; ++i){
        board[row][col] = i + '0';

        //If the placement is valid continue examing this combination
        if(is_valid_placement(board, row, col)){
            *steps_count += 1;
            if(PROTOCOL_MODE && protocol_file != NULL){
                fprintf(protocol_file, "%5d)", *steps_count);
                for(int i = 0; i < *level; ++i)fputc('-', protocol_file);
                fprintf(protocol_file, "Row: %d, Column: %d. Placing %d\n", row + 1, col + 1, i);
            }
            *level += 1;
            if(solve_sudoku_inner(board, row, col + 1, protocol_file, steps_count, level))return true;
        }
    }

    //Stepback if all combinations have lead to wrong solution
    *steps_count += 1;
    if(PROTOCOL_MODE && protocol_file != NULL){
        fprintf(protocol_file, "%5d)", *steps_count);
        for(int i = 0; i < *level; ++i)fputc('-', protocol_file);
        fputs("no possible placements. Backtrack\n", protocol_file);
    }

    board[row][col] = '.';

    *level -= 1;
    return false;
}
