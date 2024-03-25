#include <stdio.h>
#include <stdlib.h>

#include "hw3.h"

static const char *actual_filename = "./tests/actual_outputs/test_output.txt";

int main(void) {
    (void)actual_filename;

    int num_tiles_placed; (void) num_tiles_placed;

	GameState *game = initialize_game_state("./tests/boards/board02.txt"); 
    game = place_tiles(game,0 , 0, 'H', "CANDY", &num_tiles_placed);
    printf("tiles placed: %d\n", num_tiles_placed);
    game = place_tiles(game,0 , 0, 'H', "R", &num_tiles_placed);
    printf("tiles placed: %d\n", num_tiles_placed);
    game = place_tiles(game,0 , 0, 'H', "B", &num_tiles_placed);
    printf("tiles placed: %d\n", num_tiles_placed);
    game = place_tiles(game,0 , 0, 'H', "S", &num_tiles_placed);
    printf("tiles placed: %d\n", num_tiles_placed);
    game = place_tiles(game,0 , 0, 'H', "H", &num_tiles_placed);
    printf("tiles placed: %d\n", num_tiles_placed);
    game = place_tiles(game,0 , 0, 'H', "D", &num_tiles_placed);
    printf("tiles placed: %d\n", num_tiles_placed);
    save_game_state(game, actual_filename);

    // const char *expected_filename = "./tests/expected_outputs/height_exceed_limit01.txt"; 

    free_game_state(game);

    // printf("tiles placed: %d\n", num_tiles_placed);

    return 0;
}
