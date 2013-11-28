#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
using namespace std;

class Personaje
{
    public:
        int x,y;
        SDL_Surface*imagen;
        SDL_Surface*hp;
        int vida;
        int atq;
        bool turn;
        string life;
        string toString(int num);
        TTF_Font *font = NULL;
        SDL_Color textColor ={0,0,255,0};
        Personaje(int x,int y,SDL_Surface*personaje);
        void atacar(Personaje*p);

        void dibujar(SDL_Surface *screen);
        void hp_dibujar(SDL_Surface*screen);
        virtual ~Personaje();
    protected:
    private:
};

#endif // PERSONAJE_H
