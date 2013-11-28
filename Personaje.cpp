#include "Personaje.h"

Personaje::Personaje(int x,int y,SDL_Surface*imagen)
{
    this->x=x;
    this->y=y;
    this->imagen=imagen;
    this->vida=100;
    this->font = TTF_OpenFont("imagine_font.ttf", 10 );
   // this->hp=TTF_RenderText_Solid( font, this->toString(this->vida).c_str(), textColor );
    this->atq=50;
    this->turn=true;
}

void Personaje::dibujar(SDL_Surface*screen)
{
    this->hp_dibujar(screen);
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

string Personaje:: toString(int number)
{
    if (number == 0)
        return "0";
    string temp="";
    string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0;i<(int)temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}

void Personaje :: atacar(Personaje *p){
  //  this->vida-=p->atq;
    this->vida-=10;

}
