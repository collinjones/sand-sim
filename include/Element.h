#ifndef _ELEMENT_
#define _ELEMENT_

#include <string>
#include </Library/Frameworks/SDL2.framework/Headers/SDL.h>

using namespace std;

class Element {

    public:
        Element();
        Element(string name, SDL_Color color);

        SDL_Color get_color(){ return color_; }
        string get_name(){ return name_; }

        void set_name(string name){ name_ = name; }
        void set_color(SDL_Color color){ color_ = color; }

    private:
        string name_;
        SDL_Color color_;

};

class Sand : public Element {
    public:
    
        Sand(){
            ;
        }
        
};

class Air : public Element {
    public:
        Air(){
            name = "Air";
        }
        

        string get_names(){ return name; }

    private:
        string name;
};

class Stone : public Element {
    public:
        Stone(){
            name = "Stone";
        }

    private:
        string name;
};

class Water : public Element {
    public:
        Water(){
            name = "Water";
        }

    private:
        string name;
};

#endif