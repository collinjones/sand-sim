#include "../include/Element.h"

Element::Element(){
    name_ = "";
    color_.r = 0;
    color_.g = 0;
    color_.b = 0;
    color_.a = 255;
}

Element::Element(string name, SDL_Color color){
    name_ = name;
    color_ = color;
}