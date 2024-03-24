#include <stdio.h>
#include <stdlib.h>

#include "hw3.h"

static const char *actual_filename = "./tests/actual_outputs/test_output.txt";

int main(void) {
    (void)actual_filename;

    int num_tiles_placed;

	GameState *game = initialize_game_state("./tests/boards/board02.txt");
    save_game_state(game, actual_filename);
    game = place_tiles(game, 4, 5, 'H', "BRAMBLEBERRY", &num_tiles_placed);
    save_game_state(game, actual_filename);
    printf("tiles placed: %d\n", num_tiles_placed);
    game = undo_place_tiles(game);
    save_game_state(game, actual_filename);
    game = place_tiles(game, 4, 5, 'V', "BRAMBLEBERRY", &num_tiles_placed);
    printf("tiles placed: %d\n", num_tiles_placed);
    save_game_state(game, actual_filename);
    game = place_tiles(game, 5, 2, 'H', "BEA ABLE", &num_tiles_placed);
    printf("tiles placed: %d\n", num_tiles_placed);
    save_game_state(game, actual_filename);
    game = place_tiles(game, 5, 1, 'H', "CL", &num_tiles_placed);
    printf("tiles placed: %d\n", num_tiles_placed);
    save_game_state(game, actual_filename);
    game = place_tiles(game, 5, 6, 'H', "ANCE", &num_tiles_placed);
    printf("tiles placed: %d\n", num_tiles_placed);
    save_game_state(game, actual_filename);
    game = place_tiles(game, 5, 7, 'H', "NC", &num_tiles_placed);
    printf("tiles placed: %d\n", num_tiles_placed);
    save_game_state(game, actual_filename);
    game = place_tiles(game, 3, 8, 'V', "EX ELLENCE", &num_tiles_placed);
    printf("tiles placed: %d\n", num_tiles_placed);
    save_game_state(game, actual_filename);
    game = place_tiles(game, 10, 3, 'H', "AB RU CATOR", &num_tiles_placed);
    printf("tiles placed: %d\n", num_tiles_placed);
    save_game_state(game, actual_filename);
    game = place_tiles(game, 8, 3, 'H', "EM EL ISHMENT", &num_tiles_placed);
    printf("tiles placed: %d\n", num_tiles_placed);
    save_game_state(game, actual_filename);
    game = undo_place_tiles(game);
    save_game_state(game, actual_filename);
    game = place_tiles(game, 8, 3, 'H', "EM AL ONURIDAE", &num_tiles_placed);
    printf("tiles placed: %d\n", num_tiles_placed);
    save_game_state(game, actual_filename);
    game = place_tiles(game, 5, 1, 'H', "AB", &num_tiles_placed);
    printf("tiles placed: %d\n", num_tiles_placed); 

    save_game_state(game, actual_filename);

    // const char *expected_filename = "./tests/expected_outputs/multiple04.txt"; 

    free_game_state(game);

    // printf("tiles placed: %d\n", num_tiles_placed);

    return 0;
}
