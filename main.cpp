/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include "Personaje.h"


//Screen attributes
const int SCREEN_WIDTH = 675;
const int SCREEN_HEIGHT = 675;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *background = NULL;
SDL_Surface *upMessage = NULL;
SDL_Surface *downMessage = NULL;
SDL_Surface *leftMessage = NULL;
SDL_Surface *rightMessage = NULL;
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;


//The event structure
SDL_Event event;

//The font
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0, 0, 0 };

SDL_Surface *load_image( std::string filename )
{
    return IMG_Load( filename.c_str() );
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Press an Arrow Key", NULL );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the background image
    background = load_image( "background.png" );



    //Open the font
    font = TTF_OpenFont( "lazy.ttf", 72 );

    //If there was a problem in loading the background
    if( background == NULL )
    {
        return false;
    }

    //If there was an error in loading the font
    if( font == NULL )
    {
        return false;
    }




    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( background );
    SDL_FreeSurface( upMessage );
    SDL_FreeSurface( downMessage );
    SDL_FreeSurface( leftMessage );
    SDL_FreeSurface( rightMessage );

    //Close the font
    TTF_CloseFont( font );

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}

bool puedoLLegar(char tablero[9][9],int x_actual, int y_actual,int pasos, int x_final, int y_final)
{
    //Casos base
    if(pasos<0)
        return false;

    if(x_actual>=9
       || y_actual>=9
       || x_actual<0
       || y_actual<0)
       return false;

    if(tablero[y_actual][x_actual]=='#')
       return false;

    if(x_actual==x_final
       && y_actual==y_final)
       return true;

    if(tablero[y_actual][x_actual]=='O')
        pasos--;

    pasos--;

//    if(tablero[y_actual][x_actual]=='V'
//       && pasos<=0)
//        pasos=1;

    return puedoLLegar(tablero,x_actual+1,y_actual,pasos,x_final,y_final)
            || puedoLLegar(tablero,x_actual-1,y_actual,pasos,x_final,y_final)
            || puedoLLegar(tablero,x_actual,y_actual+1,pasos,x_final,y_final)
            || puedoLLegar(tablero,x_actual,y_actual-1,pasos,x_final,y_final);
}

void marcar(char tablero[9][9],char tablero_de_pasos[9][9],int x_actual, int y_actual,int pasos)
{
    //Casos base
    if(pasos<0)
        return;

    if(x_actual>=9
       || y_actual>=9
       || x_actual<0
       || y_actual<0)
       return;

    if(tablero[y_actual][x_actual]=='#')
       return;

    tablero_de_pasos[y_actual][x_actual]='P';


    if(tablero[y_actual][x_actual]=='O')
        pasos--;

    pasos--;



//    if(tablero[y_actual][x_actual]=='V'
//       && pasos<=0)
//        pasos=1;

    marcar(tablero,tablero_de_pasos,x_actual+1,y_actual,pasos);
    marcar(tablero,tablero_de_pasos,x_actual-1,y_actual,pasos);
    marcar(tablero,tablero_de_pasos,x_actual,y_actual+1,pasos);
    marcar(tablero,tablero_de_pasos,x_actual,y_actual-1,pasos);
}


void marcar_atq(char tablero[9][9],char tablero_de_pasos[9][9],int x_actual, int y_actual,int pasos_atq)
{
    //Casos base
    if(pasos_atq<0)
        return;

    if(x_actual>=9
       || y_actual>=9
       || x_actual<0
       || y_actual<0)
       return;

    if(tablero[y_actual][x_actual]=='#')
       return;

    tablero_de_pasos[y_actual][x_actual]='A';


    if(tablero[y_actual][x_actual]=='O'){
        pasos_atq--;

    }

    pasos_atq--;

    marcar_atq(tablero,tablero_de_pasos,x_actual+1,y_actual,pasos_atq);
    marcar_atq(tablero,tablero_de_pasos,x_actual-1,y_actual,pasos_atq);
    marcar_atq(tablero,tablero_de_pasos,x_actual,y_actual+1,pasos_atq);
    marcar_atq(tablero,tablero_de_pasos,x_actual,y_actual-1,pasos_atq);
}

void limpiar(char tablero_de_pasos[9][9])
{
    for(int x=0;x<9;x++)
        for(int y=0;y<9;y++)
            tablero_de_pasos[y][x]=' ';
}

int main( int argc, char* args[] )
{

    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }

    //Generate the message surfaces
//    upMessage = TTF_RenderText_Solid( font, "Up was pressed.", textColor );
//    downMessage = TTF_RenderText_Solid( font, "Down was pressed.", textColor );
//    leftMessage = TTF_RenderText_Solid( font, "Left was pressed", textColor );
//    rightMessage = TTF_RenderText_Solid( font, "Right was pressed", textColor );



    SDL_Surface* pasillo = load_image("tablero/pasillo.png");
    SDL_Surface* muro = load_image("tablero/muro.png");
    SDL_Surface* cursor = load_image("tablero/cursor.png");
    SDL_Surface* obstaculo = load_image("tablero/obstaculo.png");
    SDL_Surface* ventaja = load_image("tablero/ventaja.png");

    char tablero[9][9]={{' ','#',' ','O','V',' ','#',' ','O'},
                        {' ','#',' ','#',' ',' ','#',' ','O'},
                        {'V','#',' ','#',' ',' ','#',' ','O'},
                        {'V','#',' ','#','#',' ',' ',' ','O'},
                        {' ','#',' ','#',' ',' ','#',' ','O'},
                        {'V','#',' ','#',' ',' ','#',' ','O'},
                        {'V','#',' ','#','#',' ','#',' ','O'},
                        {' ','#',' ','#',' ',' ','#',' ','O'},
                        {' ','O','O',' ',' ',' ','#',' ','O',}};

    char tablero_de_pasos[9][9]={{' ',' ',' ',' ',' ',' ',' ',' ',' '},
                                 {' ',' ',' ',' ',' ',' ',' ',' ',' '},
                                 {' ',' ',' ',' ',' ',' ',' ',' ',' '},
                                 {' ',' ',' ',' ',' ',' ',' ',' ',' '},
                                 {' ',' ',' ',' ',' ',' ',' ',' ',' '},
                                 {' ',' ',' ',' ',' ',' ',' ',' ',' '},
                                 {' ',' ',' ',' ',' ',' ',' ',' ',' '},
                                 {' ',' ',' ',' ',' ',' ',' ',' ',' '},
                                 {' ',' ',' ',' ',' ',' ',' ',' ',' '}};



    SDL_Surface* pasos_surface = load_image("pasos.png");
    SDL_Surface* atq_surface = load_image("ataque.png");

    SDL_Surface* personaje_surface = load_image("personaje.png");
     SDL_Surface* enemigo_surface = load_image("enem.png");
    Personaje personaje(2,3,personaje_surface);

    Personaje enemigo(5,5,enemigo_surface);




    SDL_Surface* cursor_surface = load_image("cursor.png");
    int cursor_x=0;
    int cursor_y=0;

    //While the user hasn't quit
    while( quit == false )
    {
        //If there's an event to handle
        if( SDL_PollEvent( &event ) )
        {
            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
            {
                //Set the proper message surface
                switch( event.key.keysym.sym )
                {
                    case SDLK_UP:

                        cursor_y--;
                    break;
                    case SDLK_DOWN:

                        cursor_y++;
                    break;
                    case SDLK_LEFT:

                        cursor_x--;
                    break;
                    case SDLK_RIGHT:

                        cursor_x++;
                    break;
                    case SDLK_RETURN:
                        if(puedoLLegar(tablero,personaje.x,personaje.y,2,cursor_x,cursor_y))
                        {
                            personaje.x=cursor_x;
                            personaje.y=cursor_y;

                            limpiar(tablero_de_pasos);



                           marcar_atq(tablero,tablero_de_pasos,personaje.x,personaje.y,3);
                            marcar(tablero,tablero_de_pasos,personaje.x,personaje.y,2);

                        }
//
//                         if(puedoLLegar(tablero,enemigo.x,enemigo.y,2,cursor_x,cursor_y))
//                        {
//                            enemigo.x=cursor_x;
//                            enemigo.y=cursor_y;
//
//                            limpiar(tablero_de_pasos);
//
//
//                           marcar_atq(tablero,tablero_de_pasos,enemigo.x,enemigo.y,3);
//                            marcar(tablero,tablero_de_pasos,enemigo.x,enemigo.y,2);
//
//                        }



                    break;
                }
            }

            //If the user has Xed out the window
            else if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

        //Apply the background
        apply_surface( 0, 0, background, screen );

        //If a message needs to be displayed
        if( message != NULL )
        {
            //Apply the background to the screen
            apply_surface( 0, 0, background, screen );

            //Apply the message centered on the screen
            apply_surface( ( SCREEN_WIDTH - message->w ) / 2, ( SCREEN_HEIGHT - message->h ) / 2, message, screen );

            //Null the surface pointer
            message = NULL;
        }

        for(int x=0;x<9;x++)
            for(int y=0;y<9;y++)
            {
                if(tablero[y][x]==' ')
                    apply_surface(x*75,y*75,pasillo,screen);
                if(tablero[y][x]=='#')
                    apply_surface(x*75,y*75,muro,screen);
                if(tablero[y][x]=='O')
                    apply_surface(x*75,y*75,obstaculo,screen);
                if(tablero[y][x]=='V')
                    apply_surface(x*75,y*75,ventaja,screen);
            }

        for(int x=0;x<9;x++)
            for(int y=0;y<9;y++){
                if(tablero_de_pasos[y][x]=='P')
                    apply_surface(x*75,y*75,pasos_surface,screen);

                if(tablero_de_pasos[y][x]=='A')
                    apply_surface(x*75,y*75,atq_surface,screen);
            }




        personaje.dibujar(screen);
        personaje.hp_dibujar(screen);


        enemigo.dibujar(screen);
        enemigo.hp_dibujar(screen);

        apply_surface(cursor_x*75,cursor_y*75,cursor_surface,screen);

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }
    }

    //Clean up
    clean_up();

    return 0;
}
