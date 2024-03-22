#include <stdio.h>
#include <stdlib.h>

#include "hw3.h"

int main(void) {
    int num_tiles_placed;
    GameState *game = initialize_game_state("./tests/boards/board01.txt"); 
    game = place_tiles(game, 0, 2, 'V', "UNICED", &num_tiles_placed);

    printf("tiles placed: %d\n", num_tiles_placed);

    return 0;
}
