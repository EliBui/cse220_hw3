#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "hw3.h" 

#define DEBUG(...) fprintf(stderr, "[          ] [ DEBUG ] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, " -- %s()\n", __func__)

GameState* initialize_game_state(const char *filename) {
    File *file = fopen(filename, "r");
    char c;
    char numOfRow = 0;
    char numOfCol = 1; //one extra for null terminator
    char 
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

    rewind(file);

    for(int i = 0; i < numOfRow; i++) {
        for(int j = 0; j < numOfCol; j++) {
            fscanf(file, "%c", &c);
            board[i][j] = (c == '\n') ? '\0' : c;
        }
    }

    struct GameState = {.numOfRow = numOfRow, 
                        .numOfCol = numOfCol,
                        .board = board
                       };

    return NULL;
}

GameState* place_tiles(GameState *game, int row, int col, char direction, const char *tiles, int *num_tiles_placed) {
    (void)game;
    (void)row;
    (void)col;
    (void)direction;
    (void)tiles;
    (void)num_tiles_placed;
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
