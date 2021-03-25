///  Project: Sudoku solver with protocol mode
///  Author: Artur Masalcev. Software Engineering Group 4

//Read queue.h file for more information

#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

int main()
{
    char board[9][9];

    char input_filename[] = "input.txt";
    char solution_filename[] = "solution.txt";
    char protocol_filename[] = "protocol.txt";

    FILE *input_file = fopen(input_filename, "r");

    //Read input file//
    if (input_file != NULL){ //Check whether the input file exists
        for(int i = 0; i < BOARD_SIZE; ++i){
            fgets(board[i], BOARD_SIZE + 2, input_file); //Reading BOARD_SIZE + 2 symbols because of newline
        }
    }
    else{
        printf("Error: Input output does not exist.\n");
        printf("Make sure to create file input.txt in the same directory where the program is located\n");
    }
    fclose(input_file); //Close the input file

    //Solve sudoku//
    if(is_valid_sudoku(board))solve_sudoku(board);
    else printf("Error: the given board is invalid sudoku\nCheck for mistakes and try again\n");

    //Print solution in file//
    FILE *solution_file = fopen(solution_filename, "w");

    if(solution_file != NULL){
        for(int i = 0; i < BOARD_SIZE; ++i){
            for(int j = 0; j < BOARD_SIZE; ++j){
                fputc(board[i][j], solution_file);
                if(j != BOARD_SIZE - 1)fputc(' ', solution_file);
            }
            if(i != BOARD_SIZE - 1)fputs("\n", solution_file);
        }
    }
    else printf("Error: Cannot create output file\n");

    printf("Done succesfully"); //Inform user that everything had been done successfully

    return 0;
}
