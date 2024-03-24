#include <stdio.h>
#include <stdlib.h>

#include "hw3.h"

static const char *actual_filename = "./tests/actual_outputs/test_output.txt";

int main(void) {
    (void)actual_filename;

    int num_tiles_placed; (void) num_tiles_placed;

	GameState *game = initialize_game_state("./tests/boards/board08.txt"); 
    game = place_tiles(game, 6, 13, 'H', "ROID", &num_tiles_placed);
    printf("tiles placed: %d\n", num_tiles_placed);//0
    save_game_state(game, actual_filename);

    // const char *expected_filename = "./tests/expected_outputs/invalid_horiz_touch06.txt"; 

    free_game_state(game);

    // printf("tiles placed: %d\n", num_tiles_placed);

    return 0;
}
