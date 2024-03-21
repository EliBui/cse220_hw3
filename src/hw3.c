#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include "hw3.h" 

#define DEBUG(...) fprintf(stderr, "[          ] [ DEBUG ] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, " -- %s()\n", __func__)

bool firstWord = true;

GameState* initialize_game_state(const char *filename) {
    FILE *file = fopen(filename, "r");
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
                if(c != '.') {
                    firstWord = false;
                }
            }
        }
    }

    struct GameState *currGameState = (struct GameState*)malloc(sizeof(struct GameState));
    currGameState->numOfRow = numOfRow;
    currGameState->numOfCol = numOfCol;
    currGameState->board = board;
    currGameState->previous = NULL;

    return currGameState;
}

bool checkValid(GameState *game, int row, int col, char direction, const char *tiles) {
    if(row < 0 || col < 0 || row > game->numOfRow || col > game->numOfCol) {
        return false;
    } else if(direction != 'H' && direction != 'V') {
        return false;
    }

    char **board = game->board;

    char fullWordCreated[46];//45 is the length of the longest word in the english dictionary
    int index = 0;

    int r, c;
    bool stuffBefore = false, spaceInTiles = false, stuffAfter = false;//for checking if covers up the entire previous word
    
    //add any char before tiles to the word
    r = (direction == 'V') ? row-1 : row;
    c = (direction == 'H') ? col-1 : col;
    while(r >= 0 && c >= 0) {
        if(board[r][c] == '.') {
            break;
        } else {
            stuffBefore = true;
            fullWordCreated[index] = board[r][c];
            index++;
        }

        if(direction == 'H') {
            c--;
        } else {
            r--;
        }
    }//stuff copied over will be backward
    for(int k = 0; k < index/2; k++) {//flip the copied stuff
        char temp = fullWordCreated[k];
        fullWordCreated[k] = fullWordCreated[index-k-1];
        fullWordCreated[index-k-1] = temp;
    }

    //add tiles to the word
    r = row;
    c = col;
    while(tiles != '\0') {
        if(tiles == ' ') {
            spaceInTiles = true;
            fullWordCreated[index] = board[r][c];
        } else {
            fullWordCreated[index] = tiles;
        }
        index++;
        if(direction == 'H') {
            c++;
        } else {
            r++;
        }
    }

    //add stuff after tile to word
    while(r < game->numOfRow && c < game->numOfCol) {
        if(board[r][c] == '.') {
            break;
        } else {
            stuffAfter = true;
            fullWordCreated[index] = board[r][c];
            index++;
        }

        if(direction == 'H') {
            c++;
        } else {
            r++;
        }
    }

    //check if tiles covers the entire existing word
    if(!firstWord && !stuffBefore && !spaceInTiles && !stuffAfter) {
        return false;
    }

    //check if word exists in word.txt
    FILE *wordTxt = fopen("words.txt", "r");
    fullWordCreated[index] = '\n';
    index++;
    fullWordCreated[index] = '\0';
    index++;
    char str[46];//45 is the length of the longest word in the english dictionary
    while(fgets(str, 46, wordTxt) != NULL) {
        if(strcmp(fullWordCreated, str) == 0) {
            return true;
        }
    }

    return false;
}

GameState* place_tiles(GameState *game, int row, int col, char direction, const char *tiles, int *num_tiles_placed) {
    if(!checkValid(game, row, col, direction, tiles)) {
        *num_tiles_placed = 0;
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
