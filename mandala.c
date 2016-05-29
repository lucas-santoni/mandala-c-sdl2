// This program has no copyright.
// Contact : geographer@geographer.fr
// Website : https://blog.geographer.fr/

// Greetz to Epitech Paris Coding Club

// Compilation :
// $ gcc mandala.c -o mandala.out -lSDL2 -lm

////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>

////////////////////////////////////////

#define WINH 800
#define WINW 640
#define WINT "Mandala WTF !"
#define NUMBER_OF_POINTS 300
#define POINT_SIZE 1
#define STARTING_TABLE 630
#define STARTING_STEP 0.001

////////////////////////////////////////

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

////////////////////////////////////////

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

////////////////////////////////////////

int main(int argc, char *argv[]) {
  Sdl *sdl = initSdl();
  Window *window = initWindow();
  Color *color = initColor();
  Mandala *mandala = initMandala();

  while (checkUserInput(sdl, color, mandala) == 0) {
    drawBackground(sdl, color);
    drawMandala(sdl, color, mandala, window);
    SDL_RenderPresent(sdl->renderer);

    mandala->myTable += mandala->myStep;
  }

  freeAllTheThings(sdl, window, mandala, color);
  return 0;
}

////////////////////////////////////////

Sdl *initSdl() {
  Sdl *sdl = (struct Sdl*)malloc(sizeof(Sdl));

  sdl->window = SDL_CreateWindow(
      WINT,
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      WINH,
      WINW,
      SDL_WINDOW_SHOWN);

  sdl->renderer = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_SOFTWARE);
  sdl->keys = SDL_GetKeyboardState(NULL);

  return sdl;
}

////////////////////////////////////////

Window *initWindow() {
  Window *window = (struct Window*)malloc(sizeof(Window));

  if (WINW > WINH) {
    window->pading = WINH / 10;
    window->margin = WINW - WINH + window->pading;
  }
  else {
    window->pading = WINW / 10;
    window->margin = window->pading;
  }

  return window;
}

////////////////////////////////////////

Color *initColor() {
  Color *color = (struct Color*)malloc(sizeof(Color));

  color->rainbow = 0;
  color->r = 255;
  color->g = 0;
  color->b = 0;

  return color;
}

////////////////////////////////////////

Mandala *initMandala() {
  Mandala *mandala = (struct Mandala*)malloc(sizeof(Mandala));

  mandala->myTable = STARTING_TABLE;
  mandala->myStep = STARTING_STEP;

  return mandala;
}

////////////////////////////////////////

int checkUserInput(Sdl *sdl, Color *color, Mandala *mandala) {
  SDL_PollEvent(sdl->event);

  while (sdl->keys[SDL_SCANCODE_SPACE]) {
    SDL_Delay(1);
    SDL_PollEvent(sdl->event);
  }

  if (sdl->keys[SDL_SCANCODE_R])
    color->rainbow = 1;
  else
    color->rainbow = 0;

  if (sdl->keys[SDL_SCANCODE_LEFT] && sdl->keys[SDL_SCANCODE_RIGHT] && mandala->myTable >= 0 + (STARTING_STEP * 4))
    mandala->myStep = -STARTING_STEP * 4;
  else if (sdl->keys[SDL_SCANCODE_LEFT] && mandala->myTable >= 0 + (STARTING_STEP * 4))
    mandala->myStep = -STARTING_STEP * 4;
  else if (sdl->keys[SDL_SCANCODE_RIGHT])
    mandala->myStep = STARTING_STEP * 4;
  else
    mandala->myStep = STARTING_STEP;

  if (sdl->keys[SDL_SCANCODE_ESCAPE] /*|| sdl->event->type == SDL_QUIT*/)
    return 1;
  else
    return 0;
}

////////////////////////////////////////

void drawBackground(Sdl *sdl, Color *color) {
  if (color->rainbow == 1)
    SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);
  else
    SDL_SetRenderDrawColor(sdl->renderer, 200, 200, 180, 255);

  SDL_RenderClear(sdl->renderer);
}

////////////////////////////////////////

void drawMandala(Sdl *sdl, Color *color, Mandala *mandala, Window *window) {
  if (color->rainbow == 1) {
    rainbowMode(color);
    SDL_SetRenderDrawColor(sdl->renderer, color->r, color->g, color->b, 255);
  }
  else
    SDL_SetRenderDrawColor(sdl->renderer, 90, 90, 90, 255);

  drawCircle(sdl, window, mandala);
  drawTable(sdl, mandala);
}

////////////////////////////////////////

void rainbowMode(Color *color) {
  if (color->r == 255 && color->g < 255 && color->b == 0)
    color->g++;
  if (color->r > 0 && color->g == 255 && color->b == 0)
    color->r--;
  if (color->r == 0 && color->g == 255 && color->b < 255)
    color->b++;
  if (color->r == 0 && color->g > 0 && color->b == 255)
    color->g--;
  if (color->r < 255 && color->g == 0 && color->b == 255)
    color->r++;
  if (color->r == 255 && color->g == 0 && color->b > 0)
    color->b--;
}

////////////////////////////////////////

void drawCircle(Sdl *sdl, Window *window, Mandala *mandala) {
  float i;
  int j = 0;

  SDL_Rect point;
  point.w = POINT_SIZE;
  point.h = POINT_SIZE;

  for (i = 0; i < 360; i+=(360.0 / NUMBER_OF_POINTS)) {
    point.x = ((WINW + (WINH - WINW)) / 2 - cos(i * (M_PI / 180)) * (WINW - window->margin) / 2);
    mandala->coors[j].x = point.x;

    point.y = ((WINH - (WINH - WINW)) / 2 - sin(i * (M_PI / 180)) * (WINH - window->margin - (WINH - WINW)) / 2);
    mandala->coors[j].y = point.y;

    SDL_RenderFillRect(sdl->renderer, &point);
    j++;
  }
}

////////////////////////////////////////

void drawTable(Sdl *sdl, Mandala *mandala) {
  int i;
  int result = 0;

  for (i = 0; i < NUMBER_OF_POINTS; i++) {
    result = mandala->myTable * i;

    if (result >= NUMBER_OF_POINTS)
      SDL_RenderDrawLine(sdl->renderer, mandala->coors[i].x, mandala->coors[i].y, mandala->coors[(int)fmod(result, NUMBER_OF_POINTS)].x, mandala->coors[(int)fmod(result, NUMBER_OF_POINTS)].y);

    else
      SDL_RenderDrawLine(sdl->renderer, mandala->coors[i].x, mandala->coors[i].y, mandala->coors[(int)result].x, mandala->coors[(int)result].y);
  }
}

////////////////////////////////////////

void freeAllTheThings(Sdl *sdl, Window *window, Mandala *mandala, Color *color) {
  free(window);
  free(mandala);
  free(color);

  SDL_DestroyRenderer(sdl->renderer);
  SDL_DestroyWindow(sdl->window);
  free(sdl);

  SDL_Quit();

  // You may observe memory leaks using this program
  // SDL2 leaks by itself
}
