#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "functions.h"

FILE * settings;

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;
static const unsigned int BIT_PER_PIXEL = 32;

int main(int argc, char** argv) {
    
    /* Initialisation SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Création de la fenêtre (screen) */
    SDL_Surface* screen = NULL;
    if(NULL == (screen = SDL_SetVideoMode(
      WINDOW_WIDTH,
      WINDOW_HEIGHT,
      BIT_PER_PIXEL, 
      SDL_DOUBLEBUF | SDL_RESIZABLE))) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    SDL_WM_SetCaption("ARKANOPONG", NULL);
    
    /* Création d'une surface SDL (framebuffer) dans laquelle le raytracer dessinera */
    SDL_Surface* framebuffer = NULL;
    if(NULL == (framebuffer = SDL_CreateRGBSurface(SDL_SWSURFACE,
      WINDOW_WIDTH, 
      WINDOW_HEIGHT,
      BIT_PER_PIXEL,
      0, 0, 0, 0))) {
        fprintf(stderr, "Erreur d'allocation pour le framebuffer. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    /******************************************
     *               CODE DU JEU              *
     ******************************************/
    
    Ball b;
        b.speed = 1;
        b.x = 393;
        b.y = 293;
        b.dx = 0;
        b.dy = 0;

    Bar bar1;
        bar1.speed = 1;
        bar1.x = 350;
        bar1.y = 10;

    Bar bar2;
        bar2.speed = 1;
        bar2.x = 350;
        bar2.y = 580;
    
    /**
     * loop = 1 --> fenêtre SDL active
     * loop = 0 --> sortie
     */
    int loop = 1;
    while(loop) {
        
        /* Nettoyage du framebuffer */
        SDL_FillRect(framebuffer, NULL, SDL_MapRGB(framebuffer->format, 0, 0, 0));
        SDL_BlitSurface(framebuffer, NULL, screen, NULL);
        
        /* Placement des images */
        SDL_Surface *img = NULL;
        SDL_Rect center;

            /* Balle */
            center.x = b.x;
            center.y = b.y;
            center.h = 15;
            center.w = 15;
            img = IMG_Load("img/ball.png");
            SDL_BlitSurface(img, NULL, screen, &center);
            

            /* Barres */
            center.x = bar1.x;
            center.y = bar1.y;
            center.h = 10;
            center.w = 100;
            img = IMG_Load("img/bar.png");
            SDL_BlitSurface(img, NULL, screen, &center);

            center.x = bar2.x;
            center.y = bar2.y;
            center.h = 10;
            center.w = 100;
            img = IMG_Load("img/bar.png");
            SDL_BlitSurface(img, NULL, screen, &center);
        

            if(b.dx != 0 || b.dy != 0) {
                b.x += b.dx * b.speed;
                b.y += b.dy * b.speed;
            }












        /* Contrôles */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
          if(e.type == SDL_QUIT) {
              loop = 0;
              break;
          }
          
          /* Lors d'un événement souris/clavier */
          switch(e.type) {

            /* Fenêtre */
            case SDL_VIDEORESIZE:
              WINDOW_WIDTH = e.resize.w;
              WINDOW_HEIGHT = e.resize.h;
              break;

            /* Souris */
            case SDL_MOUSEBUTTONUP:
              break;

            /* Clavier */
            case SDL_KEYDOWN:
              switch(e.key.keysym.sym){
                
                case SDLK_ESCAPE: 
                  loop = 0;
                  break;

                case SDLK_LEFT: 
                  playerMove(&bar1, 0);
                  break;

                case SDLK_RIGHT: 
                  playerMove(&bar1, 1);
                  break;

                case 'a':
                  printf("Vous avez appué sur 'a'\n");
                  break;

                default : break;
              }
              break;
              
            default:
              break;
          }
        }

        /* print to file
        testFile = fopen ("tests", "w+");
        fprintf(testFile, "%d\n", b.speed);
        fclose(testFile); */

        /******************************************/

        /* Afficher à l'écran */
        SDL_Flip(screen);
    } /* fin du loop */
  
    SDL_Quit();
    
    return EXIT_SUCCESS;
}