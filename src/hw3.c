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
bool connectToExistingWord = false;

GameState *initialize_game_state(const char *filename) {
    (void)filename;
    FILE *file = fopen(filename, "r");
    char c;
    int numOfRow = 0;
    int numOfCol = 0;
    while (fscanf(file, "%c", &c) == 1) {
        if (c != '\n') {
            if (numOfRow == 0) {
                numOfCol++;
            }
        } else {
            numOfRow++;
        }
    }

    char **board = (char **)malloc(numOfRow * sizeof(char *));
    for (int i = 0; i < numOfRow; i++) {
        board[i] = (char *)malloc(numOfCol * sizeof(char));
    }

    int **boardDepth = (int **)malloc(numOfRow * sizeof(int *));
    for (int i = 0; i < numOfRow; i++) {
        boardDepth[i] = (int *)malloc(numOfCol * sizeof(int));
    }

    rewind(file); // move pointer of file back to beginning

    for (int i = 0; i < numOfRow; i++) {
        for (int j = 0; j < numOfCol; j++) {
            fscanf(file, "%c", &c);
            if(c != '\n') {
                // printf("%d %d %c |", i, j, c);
                board[i][j] = c;
                boardDepth[i][j] = (c == '.') ? 0 : 1;
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
    game->boardDepth = boardDepth;
    game->previous = NULL;
    fclose(file);
    return game;
}

char *extractSideChar(GameState *game, int row, int col, char direction, const char tile) {
    char *str = (char *)malloc(46 * sizeof(char));
    int index = 0;
    char **board = game->board;

    //add stuff before tile
    int r = (direction == 'V') ? row : row-1;
    int c = (direction == 'H') ? col : col-1;
    while(r >= 0 && c >= 0) {
        if(board[r][c] == '.') {
            break;
        } else {
            str[index] = board[r][c];
            index++;
        }

        if(direction == 'V') {
            c--;
        } else {
            r--;
        }
    }//stuff copied over will be backward
    for(int k = 0; k < index/2; k++) {//flip the copied stuff
        char temp = str[k];
        str[k] = str[index-k-1];
        str[index-k-1] = temp;
    }

    //add tile 
    r = row;
    c = col;
    str[index] = tile;
    index++;
    if(direction == 'V') {
        c++;
    } else {
        r++;
    }

    //add stuff after tile
    while(r < game->numOfRow && c < game->numOfCol) {
        // printf("r: %d\n", r);
        // printf("c: %d\n", c);
        // printf("board: %c\n", board[r][c]);
        if(board[r][c] == '.') {
            break;
        } else {
            str[index] = board[r][c];
            index++;
        }

        if(direction == 'V') {
            c++;
        } else {
            r++;
        }
    }
    
    str[index] = '\n';
    index++;
    str[index] = '\0';
    return str;
}

void free2DArr(void **arr, int length) {//void ** so it can take both int and char
    for(int i = 0; i < length; i++) {
        free(arr[i]);
    }
    free(arr);
}

bool checkValid(GameState *game, int row, int col, char direction, const char *tiles) {
    (void)game;
    (void)row;
    (void)col;
    (void)direction;
    (void)tiles;
    
    if(row < 0 || col < 0 || row >= game->numOfRow || col >= game->numOfCol) {
        return false;
    } else if (direction != 'H' && direction != 'V') {
        return false;
    }

    char **board = game->board;
    int **boardDepth = game->boardDepth;

    char *fullWordCreated = (char *)malloc(46 * sizeof(char)); // 45 is the length of the longest word in the english dictionary
    int index = 0;

    int r, c;
    // bool stuffBefore = false, spaceInTiles = false, stuffAfter = false;//for checking if covers up the entire previous word

    int tilesLen = strlen(tiles);
    char **allWords = (char **)malloc((tilesLen + 1) * sizeof(char*));//+1 for tiles too
    // for(int i = 0; i < tilesLen; i++) {
    //     allWords[i] = (char *)malloc(46 * sizeof(char));
    // }
    // char **sideWordsPtr = &allWords;
    int allWordsIndex = 0;
    bool *allWordsBool = (bool *)malloc((tilesLen + 1) * sizeof(bool));
    // bool *sideWordsBoolPtr = &allWordsBool;
    
    (void) allWords;
    (void) allWordsBool;
    // (void) sideWordsPtr;
    // (void) sideWordsBoolPtr;
    (void) allWordsIndex;
    (void) board;
    (void) boardDepth;
    (void) fullWordCreated;
    (void) index;
    (void) r;
    (void) c;
    // (void) stuffBefore;
    // (void) stuffAfter;
    // (void) spaceInTiles;
    //add any char before tiles to the word
    r = (direction == 'V') ? row-1 : row;
    c = (direction == 'H') ? col-1 : col;
    while(r >= 0 && c >= 0) {
        if(board[r][c] == '.') {
            break;
        } else {
            // stuffBefore = true;
            connectToExistingWord = true;
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
            // spaceInTiles = true;
            connectToExistingWord = true;
            fullWordCreated[index] = board[r][c];
        } else {
            fullWordCreated[index] = *tiles;
            if(r < game->numOfRow && c < game->numOfCol && (boardDepth[r][c] == 5 || board[r][c] == *tiles)) {//check if depth will be taller than 5
                free2DArr((void **)allWords, allWordsIndex);
                free(allWordsBool);
                return false;
            }
            if(r < game->numOfRow && c < game->numOfCol) {
                if(direction == 'V' && ((c+1 < game->numOfCol && board[r][c+1] != '.') || (c-1 >= 0 && board[r][c-1] != '.'))) {
                    allWords[allWordsIndex] = extractSideChar(game, r, c, direction, *tiles);
                    allWordsBool[allWordsIndex] = false;
                    allWordsIndex++;
                    connectToExistingWord = true;
                } else if (direction == 'H' && ((r+1 < game->numOfRow && board[r+1][c] != '.') || (r-1 >= 0 && board[r-1][c] != '.'))) {
                    allWords[allWordsIndex] = extractSideChar(game, r, c, direction, *tiles);
                    allWordsBool[allWordsIndex] = false;
                    allWordsIndex++;
                    connectToExistingWord = true;
                }
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
            // stuffAfter = true;
            connectToExistingWord = true;
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
    // if(!firstWord && !stuffBefore && !spaceInTiles && !stuffAfter) {
    //     return false;
    // }

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
    allWords[allWordsIndex] = fullWordCreated;
    allWordsBool[allWordsIndex] = false;
    allWordsIndex++;
    char str[46];//45 is the length of the longest word in the english dictionary
    while(fgets(str, 46, wordTxt) != NULL) {
        for(int i = 0; str[i] != '\n'; i++) {
            str[i] = toupper(str[i]);
        }
        for(int i = 0; i < allWordsIndex; i++) {
            if(strcmp(allWords[i], str) == 0) {
                allWordsBool[i] = true;
            }
        }
    }
    fclose(wordTxt);

    for(int i = 0; i < allWordsIndex; i++) {
        if(!allWordsBool[i]) {
            free2DArr((void **)allWords, allWordsIndex);
            free(allWordsBool);
            return false;
        }
    }

    free2DArr((void **)allWords, allWordsIndex);
    free(allWordsBool);
    return true;
}

//returns true if it covers existing words and false otherwise
bool checkCoverFullWord(GameState *game, GameState *newGame, int row, int col, char direction) {
    int length = (direction == 'V') ? game->numOfRow : game->numOfCol;
    int **oldBoardDepth = game->boardDepth;
    int **newBoardDepth = newGame->boardDepth;
    int oldLine[length];
    int newLine[length];//we dont care about elements that are beyond the old board

    for(int i = 0; i < length; i++) {
        if(direction == 'H') {
            oldLine[i] = oldBoardDepth[row][i];
            newLine[i] = newBoardDepth[row][i];
        } else {
            oldLine[i] = oldBoardDepth[i][col];
            newLine[i] = newBoardDepth[i][col];
        }
    }

    int nonZeros = 0, oldSum = 0, newSum = 0;
    for(int i = 0; i < length; i++) {
        if(oldLine[i] != 0) {
            nonZeros++;
            oldSum += oldLine[i];
            newSum += newLine[i];
        } else {
            if(nonZeros > 1 && (newSum - oldSum) == nonZeros) {
                //a valid word on the same line must be at least 2 letters long
                //anything less than 2 letters long is not a word so covering it is fine
                //if a word is fully covered then the new sum is = old sum + the length of the word
                return true;
            }
            nonZeros = 0;
            oldSum = 0;
            newSum = 0;
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
    connectToExistingWord = false;
    if (!checkValid(game, row, col, direction, tiles)) {
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

    //fill in newBoard and newBoardDepth
    for(int r = 0; r < newGame->numOfRow; r++) {
        for(int c = 0; c < newGame->numOfCol; c++) {
            //check if the word being place is the first word on the board
            if(firstWord && r < game->numOfRow && c < game->numOfCol && board[r][c] != '.') {
                firstWord = false;
            }

            if((direction == 'H' && r == row && c >= col && c < col+tilesLen && *tiles != ' ') ||
                (direction == 'V' && r >= row && c == col && r < row+tilesLen && *tiles != ' ')) {
                //falls within tiles on the board
                newBoard[r][c] = *tiles;
                // printf("%d %d %c |", r, c, newBoard[r][c]);
                tiles++;
                newBoardDepth[r][c] = (r >= game->numOfRow || c >= game->numOfCol) ? 1 : boardDepth[r][c]+1;
                tilesPlaced++;
            } else if(r >= game->numOfRow || c >= game->numOfCol) {
                //falls outside the bound of the old board
                newBoard[r][c] = '.';
                // printf("%d %d %c |", r, c, newBoard[r][c]);
                newBoardDepth[r][c] = 0;
            } else {
                //copied from old board
                if((direction == 'H' && r == row && c >= col && c < col+tilesLen && *tiles == ' ') ||
                (direction == 'V' && r >= row && c == col && r < row+tilesLen && *tiles == ' ')) {
                    //falls within tiles but is a space char so copy from old board
                    tiles++;
                }
                newBoard[r][c] = board[r][c];
                // printf("%d %d %c |", r, c, newBoard[r][c]);
                newBoardDepth[r][c] = boardDepth[r][c];
            }
        }
    }

    newGame->board = newBoard;
    newGame->boardDepth = newBoardDepth;

    //if it is the first word, make sure the length is at least 2
    if(firstWord && tilesLen < 2) {
        *num_tiles_placed = 0;
        return game;
    }

    //check full cover or if connected to existing word
    if(!firstWord && !connectToExistingWord) {
        *num_tiles_placed = 0;
        return game;
    } else if(!firstWord && checkCoverFullWord(game, newGame, row, col, direction)) {
        *num_tiles_placed = 0;
        return game;
    }
    
    newGame->previous = game;

    *num_tiles_placed = tilesPlaced;
    return newGame;
}

void free_game_state(GameState *game) {
    (void) game;

    GameState *temp;
    do {
        free2DArr((void **)game->board, game->numOfRow);
        free2DArr((void **)game->boardDepth, game->numOfRow);
        temp = game;
        game = game->previous;
        free(temp);
    } while(game != NULL);
}

GameState *undo_place_tiles(GameState *game) {
    (void) game;

    if(game->previous == NULL) {
        return game;
    } else {
        GameState *previousGame = game->previous;
        game->previous = NULL;
        free_game_state(game);
        return previousGame;
    }
}

void save_game_state(GameState *game, const char *filename) {
    (void)game;
    (void)filename;

    FILE *file;
    if((file = fopen(filename, "w")) == NULL) {
        printf("file Null\n");
        exit(EXIT_FAILURE);
    }

    char **board = game->board;
    int **boardDepth = game->boardDepth;

    for(int i = 0; i < game->numOfRow; i++) {
        for(int j = 0; j < game->numOfCol; j++) {
            fprintf(file, "%c", board[i][j]);
        }
        fprintf(file, "\n");
    }

    for(int i = 0; i < game->numOfRow; i++) {
        for(int j = 0; j < game->numOfCol; j++) {
            fprintf(file, "%d", boardDepth[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}
