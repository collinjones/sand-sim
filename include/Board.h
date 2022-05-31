#ifndef _BOARD_
#define _BOARD_

#include "Element.h"
#include "Tile.h"
#include "Config.h"
#include "Util.h"
#include <vector>
#include <iostream>

using namespace std;

class Board {

    public:

        Board();

        /* GETTERS */
        Tile* get_tile_at(int x, int y){ return board_[coord(x, y)]; }
        vector<Tile*> get_board(){return board_;}
        SDL_Color get_sand_color(){return SAND_COLOR;}
        SDL_Color get_stone_color(){return STONE_COLOR;}
        SDL_Color get_air_color(){return AIR_COLOR;}

        /* SETTERS */
        void set_tile_to_at(Tile* t, int x, int y){ board_[coord(x, y)] = t; }
        void set_sdl_color(SDL_Color* color, int r, int g, int b, int a){
            color->r = r;
            color->g = g;
            color->b = b;
            color->a = a; 
        }
        void set_coord_to_tile_color(int x, int y, SDL_Color color, SDL_Renderer* renderer){
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderDrawPoint(renderer, x, y);
        }

        /* UTILITIES */
        int coord(int x, int y){
            return x + y * SCREEN_WIDTH;
        }
        bool can_move(Tile* tile, int new_x, int new_y){

            // Out of bounds? Return false
            if(new_x < 0 || new_x >= SCREEN_WIDTH || new_y < 0 || new_y >= SCREEN_HEIGHT){
                return false;
            }
            
            Tile* new_tile = board_[coord(new_x, new_y)];
            if(new_tile->e->get_name() == "Air"){
                
                return true;
            }

            return false;

        }

        void move(int x, int y, int new_x, int new_y){

            int from_coord = coord(x, y);
            int to_coord = coord(new_x, new_y);
            Tile* to_tile = board_[to_coord];

            board_[to_coord] = board_[from_coord];
            board_[from_coord] = to_tile;

        }

        

    private:

        vector<Tile*> board_;
        SDL_Color SAND_COLOR;
        SDL_Color STONE_COLOR;
        SDL_Color AIR_COLOR;

};


#endif