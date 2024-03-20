#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "hw3.h" 

#define DEBUG(...) fprintf(stderr, "[          ] [ DEBUG ] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, " -- %s()\n", __func__)

const int LONGEST_WORD_LEN = 45;

GameState* initialize_game_state(const char *filename) {
    File *file = fopen(filename, "r");
    char c;
    char numOfRow = 0;
    char numOfCol = 0;
    while(fscanf(file, "%c", &c) == 1) {
        if(c != '\n') {
            if(numOfRow == 0) {
                numOfCol++;
            }
        } else {
            numOfRow++;
        }
    }

    char **board = (char **)malloc(numOfRow * sizeof(char *));
    for(int i = 0; i < numOfRow; i++) {
        board[i] = (char *)malloc(numOfCol * sizeof(char));
    }

    int **boardDepth = (int **)malloc(numOfRow * sizeof(int *));
    for(int i = 0; i < numOfRow; i++) {
        boardDepth[i] = (int *)malloc(numOfCol * sizeof(int));
    }

    rewind(file); //move pointer of file back to beginning

    for(int i = 0; i < numOfRow; i++) {
        for(int j = 0; j < numOfCol; j++) {
            fscanf(file, "%c", &c);
            if(c != '\n') {
                board[i][j] = c;
                boardDepth[i][j] = (c == '.') ? 0 : 1;
            }
        }
    }

    GameState *currGameState;
    currGameState->numOfRow = numOfRow;
    currGameState->numOfCol = numOfCol;
    currGameState->board = board;
    currGameState->previous = null;

    return currGameState;
}

bool checkValid(GameState *game, int row, int col, char direction, const char *tiles) {
    if(row < 0 || col < 0 || row > game->numOfRow || col > game->numOfCol) {
        return false;
    } else if(direction != 'H' && direction != 'V') {
        return false;
    }

    char *fullWordInput[LONGEST_WORD_LEN+1];


    return true;
}

GameState* place_tiles(GameState *game, int row, int col, char direction, const char *tiles, int *num_tiles_placed) {
    if(!checkValid(game, row, col, direction, tiles)) {
        return game;
    }

    return NULL;
}

GameState* undo_place_tiles(GameState *game) {
    (void)game;
    return NULL;
}

void free_game_state(GameState *game) {
    (void)game;
}

void save_game_state(GameState *game, const char *filename) {
    (void)game;
    (void)filename;
}
