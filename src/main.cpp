#include <iostream>
#include <vector>

#include "../include/Board.h"
#include "../include/Element.h"
#include "../include/Util.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

using namespace std;

class Game {
    public:

        Game(){
            board = new Board();
        }

        void initialize(SDL_Renderer* renderer){

            Tile* cur_tile;

            for(int y = 0; y < SCREEN_HEIGHT; y++){
                for(int x = 0; x < SCREEN_WIDTH; x++){
                    
                    cur_tile = board->get_tile_at(x,y);

                    int r = cur_tile->e->get_color().r;
                    int g = cur_tile->e->get_color().g;
                    int b = cur_tile->e->get_color().b;
                    int a = cur_tile->e->get_color().a;


                    SDL_SetRenderDrawColor(renderer, r, g, b, a);
                    SDL_RenderDrawPoint(renderer, x, y);
                     
                }
            }
            SDL_RenderPresent(renderer);

            // for(int y = 250; y < 260; y++){
            //     for(int x = 250; x < 260; x++){
                    
            //     }
            // }
        }

        void draw(SDL_Renderer* renderer){

            Tile* cur_tile;
            SDL_Color sand_color = board->get_sand_color();
            buttons = SDL_GetMouseState(&mouseX, &mouseY);
            int y_down, x_left, x_right, x, y;
            string cur_tile_element;
            
            if ((buttons & SDL_BUTTON_LMASK) != 0) {
                cur_tile = board->get_tile_at(mouseX,mouseY);
                cur_tile->e = new Sand();
                cur_tile->e->set_color(sand_color);
                cur_tile->e->set_name("Sand");
                board->set_tile_to_at(cur_tile, mouseX, mouseY);
                
            }

            for ( y = SCREEN_HEIGHT-1; y > 0; y--){
                for ( x = 0; x < SCREEN_WIDTH; x++){
                    
                    y_down = y+1;
                    x_left = x-1;
                    x_right = x+1;
                    cur_tile = board->get_tile_at(x, y);
                    cur_tile_element = cur_tile->e->get_name();

                    /* Skip tile if element is Air or Rock */
                    if(cur_tile_element == "AIR" || cur_tile_element == "ROCK"){
                        continue;
                    }

                    /* Move tile down if nothing below */
                    if(board->can_move(cur_tile, x, y_down)){
                        board->move(x, y, x, y_down);
                    }

                }
            }


            /* MAIN DRAWING LOOP */
            for( y = 0; y < SCREEN_HEIGHT; y++){
                for( x = 0; x < SCREEN_WIDTH; x++){

                    cur_tile = board->get_tile_at(x,y);
                    board->set_coord_to_tile_color(x, y, cur_tile->e->get_color(), renderer);
                }
            }
        }
 
    private:
        Board* board; 
        int mouseX;
        int mouseY;
        Uint32 buttons;

};

int main () {

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
    }
    else {
        
        window = SDL_CreateWindow("Sand Simulation by Collin Jones",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

        if ( window == NULL ) {
            cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        }
        else {

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            //SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
            SDL_Event e;
            Game Sand;
            bool quit = false;
            Sand.initialize(renderer);

            while (!quit){

                while (SDL_PollEvent(&e)){
                    if (e.type == SDL_QUIT){
                        quit = true;
                    }
                }

                //Update screen
                Sand.draw(renderer);
                SDL_RenderPresent( renderer );
                
                
            }
        }
    }

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();

    return EXIT_SUCCESS;
}