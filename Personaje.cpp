#include "Personaje.h"

Personaje::Personaje(int x,int y,SDL_Surface*imagen)
{
    this->x=x;
    this->y=y;
    this->imagen=imagen;
    this->vida=100;
    this->life=" HP:";
    this->font = TTF_OpenFont( "lazy.ttf", 10 );
    this->hp=TTF_RenderText_Solid( font, "150", textColor );

}

void Personaje::dibujar(SDL_Surface*screen)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x*75;
    offset.y = y*75;

    //Blit
    SDL_BlitSurface( imagen, NULL, screen, &offset );

}


void Personaje::hp_dibujar(SDL_Surface*screen)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x*75;
    offset.y = y*75;

    //Blit
    SDL_BlitSurface( hp, NULL, screen, &offset );

}

Personaje::~Personaje()
{
    //dtor
}
