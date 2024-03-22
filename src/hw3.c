#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include "hw3.h"

#define DEBUG(...)                              \
    fprintf(stderr, "[          ] [ DEBUG ] "); \
    fprintf(stderr, __VA_ARGS__);               \
    fprintf(stderr, " -- %s()\n", __func__)

bool firstWord = true;

GameState *initialize_game_state(const char *filename) {
    (void)filename;
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
                // printf("%d %d %c |", i, j, c);
                board[i][j] = c;
                boardDepth[i][j] = (c == '.') ? 0 : 1;
                if(c != '.') {
                    firstWord = false;
                }
            } else {
                j--;
            }
        }
    }

    GameState *game = (GameState *)malloc(sizeof(GameState));
    game->numOfRow = numOfRow;
    game->numOfCol = numOfCol;
    game->board = board;
    game->boardDepth = boardDepth;
    game->previous = NULL;

    return game;
}

bool checkValid(GameState *game, int row, int col, char direction, const char *tiles) {
    (void)game;
    (void)row;
    (void)col;
    (void)direction;
    (void)tiles;

    if(row < 0 || col < 0 || row > game->numOfRow || col > game->numOfCol) {
        return false;
    } else if(direction != 'H' && direction != 'V') {
        return false;
    }

    char **board = game->board;
    int **boardDepth = game->boardDepth;

    char fullWordCreated[46];//45 is the length of the longest word in the english dictionary
    int index = 0;

    int r, c;
    bool stuffBefore = false, spaceInTiles = false, stuffAfter = false;//for checking if covers up the entire previous word

    (void)board;
    (void)boardDepth;
    (void)fullWordCreated;
    (void)index;
    (void)r;
    (void)c;
    (void)stuffBefore;
    (void)stuffAfter;
    (void)spaceInTiles;
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
    while(*tiles != '\0') {
        if(*tiles == ' ') {
            spaceInTiles = true;
            fullWordCreated[index] = board[r][c];
        } else {
            fullWordCreated[index] = *tiles;
            if(boardDepth[r][c] == 5) {//check if depth will be taller than 5
                return false;
            }
        }
        index++;
        tiles++;
        if(direction == 'H') {
            c++;
        } else {
            r++;
        }
    }

    //add stuff after tile to word
    while(r < game->numOfRow && c < game->numOfCol) {
        // printf("r: %d\n", r);
        // printf("c: %d\n", c);
        // printf("board: %c\n", board[r][c]);
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
    FILE *wordTxt = fopen("./tests/words.txt", "r");
    
    // if((wordTxt = fopen("./tests/words.txt", "r")) == NULL) {
    //     printf("wordTxt Null\n");
    //     exit(EXIT_FAILURE);
    // }

    fullWordCreated[index] = '\n';//there's a \n char at the end of all words in words.txt
    index++;
    fullWordCreated[index] = '\0';
    index++;
    char str[46];//45 is the length of the longest word in the english dictionary
    while(fgets(str, 46, wordTxt) != NULL) {
        for(int i = 0; str[i] != '\n'; i++) {
            str[i] = toupper(str[i]);
        }
        if(strcmp(fullWordCreated, str) == 0) {
            return true;
        }
    }

    return false;
}

GameState *place_tiles(GameState *game, int row, int col, char direction, const char *tiles, int *num_tiles_placed) {
    (void)game;
    (void)row;
    (void)col;
    (void)direction;
    (void)tiles;

    int tilesPlaced = 0;
    if(!checkValid(game, row, col, direction, tiles)) {
        *num_tiles_placed = tilesPlaced;
        return game;
    }

    char **board = game->board;
    int **boardDepth = game->boardDepth;

    GameState *newGame = (GameState*)malloc(sizeof(GameState));

    (void)newGame;
    (void)board;
    (void)boardDepth;
    int tilesLen = strlen(tiles);

    if(direction == 'H' && col + tilesLen > game->numOfCol) {//check if board needs to be expanded
        newGame->numOfCol = col + tilesLen;
        newGame->numOfRow = game->numOfRow;
    } else if(direction == 'V' && row + tilesLen > game->numOfRow) {
        newGame->numOfCol = game->numOfCol;
        newGame->numOfRow = row + tilesLen;
    } else {
        newGame->numOfCol = game->numOfCol;
        newGame->numOfRow = game->numOfRow;
    }

    char **newBoard = (char **)malloc(newGame->numOfRow * sizeof(char *));
    for(int i = 0; i < newGame->numOfRow; i++) {
        newBoard[i] = (char *)malloc(newGame->numOfCol * sizeof(char));
    }

    int **newBoardDepth = (int **)malloc(newGame->numOfRow * sizeof(int *));
    for(int i = 0; i < newGame->numOfRow; i++) {
        newBoardDepth[i] = (int *)malloc(newGame->numOfCol * sizeof(int));
    }

    for(int r = 0; r < newGame->numOfRow; r++) {
        for(int c = 0; c < newGame->numOfCol; c++) {
            if((direction == 'H' && r == row && c >= col && c < col+tilesLen && *tiles != ' ') ||
                (direction == 'V' && r >= row && c == col && r < row+tilesLen && *tiles != ' ')) {
                //falls within tiles on the board
                newBoard[r][c] = *tiles;
                // printf("%d %d %c |", r, c, newBoard[r][c]);
                tiles++;
                newBoardDepth[r][c] = boardDepth[r][c]+1;
                tilesPlaced++;
            } else if(r >= game->numOfRow || c >= game->numOfCol) {
                //falls outside the bound of the old board
                newBoard[r][c] = '.';
                // printf("%d %d %c |", r, c, newBoard[r][c]);
                newBoardDepth[r][c] = 0;
            } else {
                //copied from old board
                newBoard[r][c] = board[r][c];
                // printf("%d %d %c |", r, c, newBoard[r][c]);
                newBoardDepth[r][c] = boardDepth[r][c];
            }
        }
    }

    newGame->board = newBoard;
    newGame->boardDepth = newBoardDepth;
    newGame->previous = game;

    *num_tiles_placed = tilesPlaced;
    return newGame;
}

GameState *undo_place_tiles(GameState *game) {
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
