#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>

#include "vector.h"
#include "collision.h"

typedef
struct
{
    bool exit;
    int current_color;
    SDL_Color colors[4];
    Point cursor;
    Rect cursor_rect;
    Rect rects[5];
    bool cross[5];
} SquareGameState;

typedef
struct
{
    bool exit;
    Vector v[3];
    int current_color;
    SDL_Color color[2];
} VectorGameState;

void InitSquareGameState(SquareGameState *state)
{
    SquareGameState tmp = {
        false,
        0,
        {
            {255, 0, 0, 255},
            {0, 255, 0, 255},
            {0, 0, 255, 255},
            {255, 255, 255, 255}
        },
        {0, 0},
        {{0, 0}, 25, 25},
        {
            {{25, 25}, 50, 125},
            {{125, 450}, 75, 100},
            {{525, 300}, 50, 125},
            {{350, 400}, 75, 100},
            {{200, 475}, 50, 125},
        },
        {false, false, false, false, false}
    };
    *state = tmp;
}

void InitVectorGameState(VectorGameState *state)
{
    state->exit = false;

    state->v[0].x = 325;
    state->v[0].y = 275;

    state->v[1].x = 275;
    state->v[1].y = 275;

    state->v[2].x = 325;
    state->v[2].y = 275;

    state->current_color = 0;

    state->color[0].r = 0;
    state->color[0].g = 0;
    state->color[0].b = 0;
    state->color[0].a = 255;

    state->color[1].r = 255;
    state->color[1].g = 0;
    state->color[1].b = 0;
    state->color[1].a = 255;
}

int SquareInputHandler(SquareGameState *game_state)
{
    if(NULL == game_state) {
        return 1;
    }

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_MOUSEMOTION:
            game_state->cursor.x = event.motion.x;
            game_state->cursor.y = event.motion.y;
            break;
        case SDL_KEYDOWN:
            if(SDLK_SPACE == event.key.keysym.sym) {
                if(0 == event.key.repeat) {
                    game_state->current_color += 1;
                    game_state->current_color = game_state->current_color % 4;
                }
            }

            if(SDLK_ESCAPE != event.key.keysym.sym) {
                break;
            }
        case SDL_QUIT:
            game_state->exit = true;
            break;
        default:
            break;
        }
    }

    return 0;
}

int SquareActionHandler(SquareGameState *game_state)
{
    game_state->cursor_rect.p = game_state->cursor;

    for(int i = 0; i < 5; ++i) {
        game_state->cross[i] = rect_cross_rect(game_state->rects[i], game_state->cursor_rect);
    }

    return 0;
}

int SquareRender(SDL_Renderer *renderer, SquareGameState *game_state)
{
    SDL_Color *palette = game_state->colors;
    int clear_color_index = game_state->current_color;
    SDL_Color *clear_color = &(palette[clear_color_index]);

    if(0 != SDL_SetRenderDrawColor(renderer,
                                   clear_color->r,
                                   clear_color->g,
                                   clear_color->b,
                                   clear_color->a)) {
        return 1;
    }

    if(SDL_RenderClear(renderer) != 0) {
        return 1;
    }

    for(int i = 0; i < 5; ++i) {
        SDL_Color *draw_color;
        if(game_state->cross[i]) {
            draw_color = &(palette[2]);
        } else {
            draw_color = &(palette[1]);
        }
        SDL_SetRenderDrawColor(renderer,
                               draw_color->r,
                               draw_color->g,
                               draw_color->b,
                               draw_color->a);
        SDL_Rect sdl_rect;
        Rect *rect = &(game_state->rects[i]);
        sdl_rect.x = rect->p.x;
        sdl_rect.y = rect->p.y;
        sdl_rect.h = rect->h;
        sdl_rect.w = rect->w;
        if(SDL_RenderFillRect(renderer, &sdl_rect) != 0) {
            return 1;
        }
    }

    SDL_Color *color = &(palette[3]);
    SDL_SetRenderDrawColor(renderer,
                           color->r,
                           color->g,
                           color->b,
                           color->a);
    SDL_Rect sdl_rect;
    Rect *rect = &(game_state->cursor_rect);
    sdl_rect.x = rect->p.x;
    sdl_rect.y = rect->p.y;
    sdl_rect.h = rect->h;
    sdl_rect.w = rect->w;
    if(SDL_RenderFillRect(renderer, &sdl_rect) != 0) {
        return 1;
    }

    SDL_RenderPresent(renderer);

    return 0;
}

int VectorInputHandler(VectorGameState *state)
{
    if(NULL == state) {
        return 1;
    }

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_KEYDOWN:
            // ...code...;

            if(SDLK_ESCAPE != event.key.keysym.sym) {
                break;
            }
        case SDL_QUIT:
            state->exit = true;
            break;
        default:
            break;
        }
    }

    return 0;
}

int VectorActionHandler(VectorGameState *state)
{
    return 0;
}

int VectorRender(SDL_Renderer *renderer, VectorGameState *state)
{
    SDL_Color *palette = state->color;
    int clear_color_index = state->current_color;
    SDL_Color *clear_color = &(palette[clear_color_index]);
    if(0 != SDL_SetRenderDrawColor(renderer,
                                   clear_color->r,
                                   clear_color->g,
                                   clear_color->b,
                                   clear_color->a)) {
        return 1;
    }
    if(SDL_RenderClear(renderer) != 0) {
        return 1;
    }
    for(int i = 0; i < 2; ++i) {
        SDL_Color *draw_color = &(palette[0]);
        SDL_SetRenderDrawColor(renderer,
                               draw_color->r,
                               draw_color->g,
                               draw_color->b,
                               draw_color->a);
    }

    SDL_Color *color = &(palette[1]);
    SDL_SetRenderDrawColor(renderer,
                           color->r,
                           color->g,
                           color->b,
                           color->a);
    SDL_RenderDrawLine(renderer,  275, 275,
                       state->v[0].x, state->v[0].y);
    SDL_RenderDrawLine(renderer,  300, 225,
                       state->v[1].x, state->v[1].y);
    SDL_RenderDrawLine(renderer,  300, 225,
                       state->v[2].x, state->v[2].y);

    SDL_RenderPresent(renderer);

    return 0;
}

int main()
{
    if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Pong", 0, 0, 800, 600, 0);
    if(window == NULL) {
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) {
        return 1;
    }

    SquareGameState square_game_state;
    InitSquareGameState(&square_game_state);
    while(!(square_game_state.exit)) {
        SquareInputHandler(&square_game_state);

        SquareActionHandler(&square_game_state);

        SquareRender(renderer, &square_game_state);
    }

    VectorGameState vector_game_state;
    InitVectorGameState(&vector_game_state);
    while(!(vector_game_state.exit)) {
        VectorInputHandler(&vector_game_state);

        VectorActionHandler(&vector_game_state);

        VectorRender(renderer, &vector_game_state);
    }

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
