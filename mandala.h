// This program has no copyright.
// Contact : geographer@geographer.fr
// Website : https://blog.geographer.fr/

// Greetz to Epitech Paris Coding Club

// General includes
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>

// General defines
#define WINH 800
#define WINW 640
#define WINT "Modular Mandalas"
#define NUMBER_OF_POINTS 300
#define POINT_SIZE 1
#define STARTING_TABLE 630
#define STARTING_STEP 0.001

// Various structures
typedef struct Sdl {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event *event;
  const Uint8 *keys;
} Sdl;

typedef struct Window {
  int pading;
  int margin;
} Window;

typedef struct Color {
  int rainbow;
  int r;
  int g;
  int b;
} Color;

typedef struct Coor {
  int x;
  int y;
} Coors;

typedef struct Mandala {
  float myTable;
  float myStep;
  struct Coor coors[NUMBER_OF_POINTS];
} Mandala;

// Various prototypes
Sdl *initSdl();
Window *initWindow();
Color *initColor();
Mandala *initMandala();
int checkUserInput(Sdl *sdl, Color *color, Mandala *mandala);
void drawBackground(Sdl *sdl, Color *color);
void drawCircle(Sdl *sdl, Window *window, Mandala *mandala);
void drawMandala(Sdl *sdl, Color *color, Mandala *mandala, Window *window);
void rainbowMode(Color *color);
void drawTable(Sdl *sdl, Mandala *mandala);
void freeAllTheThings(Sdl *sdl, Window *window, Mandala *mandala, Color *color);
