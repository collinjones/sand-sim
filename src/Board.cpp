#include "../include/Board.h"
#include "../include/Tile.h"

#include <memory>
#include <iostream>

using namespace std;

Board::Board(){

    set_sdl_color(&SAND_COLOR, 194, 178, 128, 255);
    set_sdl_color(&STONE_COLOR, 136, 140, 141, 255);
    set_sdl_color(&AIR_COLOR, 0, 0, 0, 255);

    /* Initialize board with air and a layer of stone */
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {

            // First 490 tiles are Air
            if(y < SCREEN_HEIGHT - 10){

                Tile* t = new Tile();

                t->e = new Air();
                t->e->set_name("Air");
                t->e->set_color(AIR_COLOR); 
                board_.push_back(t);

            }

            else{
                Tile* t = new Tile();
                
                t->e = new Stone();
                t->e->set_name("Stone");
                t->e->set_color(STONE_COLOR);
                board_.push_back(t);

            }
        }
    }
}
