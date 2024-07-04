#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>

#include "shape.h"
#include "object.h"
#include "vector.h"
#include "collision.h"

typedef
struct
{
    bool exit;
    int current_color;
    SDL_Color colors[4];
    Point cursor;
    RectangleCollider cursor_rect;
    RectangleCollider rects[5];
    bool cross[5];
} SquareGameState;

typedef
struct
{
    bool exit;
    Vector v[3];
    int current_color;
    SDL_Color color[2];
    float angle;
    float scale;
    Vector cursor;
    Triangle *polygon;
    Square square;
    Circle c;
} VectorGameState;

typedef
struct
{
    bool exit;
    int current_color;
    SDL_Color color[3];
    GameObject racket_1;
    GameObject racket_2;
    GameObject boll;
} PongGameState;

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

    state->v[2].x = 275;
    state->v[2].y = 325;

    state->current_color = 0;

    state->color[0].r = 0;
    state->color[0].g = 0;
    state->color[0].b = 0;
    state->color[0].a = 255;

    state->color[1].r = 255;
    state->color[1].g = 0;
    state->color[1].b = 0;
    state->color[1].a = 255;

    state->angle = 15;

    state->scale = 1;

    Vector vectors[3] = {
        {0, -30},
        {25, 30},
        {-35, 0}
    };

    state->polygon = shape_create_triangle(vectors);

    square_init(&(state->square), 25, 25);

    circle_init(&(state->c), 50);
}

void FreeVectorGameState(VectorGameState *state)
{
    shape_free_triangle(state->polygon);
}

void InitPongGameState(PongGameState *pong_game_state)
{
    pong_game_state->exit = false;

    pong_game_state->current_color = 0;

    pong_game_state->color[0].r = 0;
    pong_game_state->color[0].g = 0;
    pong_game_state->color[0].b = 0;
    pong_game_state->color[0].a = 255;

    pong_game_state->color[1].r = 255;
    pong_game_state->color[1].g = 0;
    pong_game_state->color[1].b = 0;
    pong_game_state->color[1].a = 255;

    pong_game_state->color[2].r = 0;
    pong_game_state->color[2].g = 255;
    pong_game_state->color[2].b = 0;
    pong_game_state->color[2].a = 255;

    GameObject *rk = &pong_game_state->racket_1;
    Square *racket_shape = shape_create_square(120, 15);
    rk->scene_position.x = 15;
    rk->scene_position.y = 15;
    rk->direction.x = 0;
    rk->direction.y = 0;
    rk->shape = racket_shape;
    rk->velocity.x = 0;
    rk->velocity.y = 0;
    rk->collider_type = 2;
    rk->collider = malloc(sizeof(RectangleCollider));
    RectangleCollider *rc = (RectangleCollider *)(rk->collider);
    rc->p.x = 15;
    rc->p.y = 15;
    rc->h = 120;
    rc->w = 15;

    rk = &pong_game_state->racket_2;
    rk->scene_position.x = 770;
    rk->scene_position.y = 465;
    rk->direction.x = 0;
    rk->direction.y = 0;
    rk->shape = racket_shape;
    rk->velocity.x = 0;
    rk->velocity.y = 0;
    rk->collider_type = 2;
    rk->collider = (RectangleCollider *)malloc(sizeof(RectangleCollider));
    rc = (RectangleCollider *)(rk->collider);
    rc->p.x = 770;
    rc->p.y = 465;
    rc->h = 120;
    rc->w = 15;

    Circle *boll_shape = shape_create_circle(7);
    rk = &pong_game_state->boll;
    rk->scene_position.x = 400;
    rk->scene_position.y = 300;
    rk->direction.x = 0;
    rk->direction.y = 0;
    rk->shape = boll_shape;
    rk->velocity.x = 0;
    rk->velocity.y = 0;
    rk->collider_type = 2;
    rk->collider = (CircleCollider *)malloc(sizeof(CircleCollider));
    CircleCollider *cr = (CircleCollider *)(rk->collider);
    cr->center.x = 400;
    cr->center.y = 300;
    cr->r = 7;
}

void FreePongGameState(PongGameState *pong_game_state)
{
    shape_free_square(pong_game_state->racket_1.collider);
    shape_free_square(pong_game_state->racket_2.collider);
    shape_free_circle(pong_game_state->boll.collider);
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
        RectangleCollider *rect = &(game_state->rects[i]);
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
    RectangleCollider *rect = &(game_state->cursor_rect);
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
        case SDL_MOUSEMOTION:
            state->cursor.x = event.motion.x;
            state->cursor.y = event.motion.y;
            break;
        case SDL_KEYDOWN:
            if(SDLK_a == event.key.keysym.sym) {
                state->angle += 5;
            }

            if(SDLK_d == event.key.keysym.sym) {
                state->angle -= 5;
            }

            if(SDLK_w == event.key.keysym.sym) {
                state->scale += 0.125;
            }

            if(SDLK_s == event.key.keysym.sym) {
                state->scale -= 0.125;
            }

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

    Vector v[3];
    for(int i = 0; i < 3; ++i) {
        v[i] = vector_summ(state->v[i], vector_multiplication(state->cursor, -1));
        v[i] = vector_rotate(v[i], state->angle);
        v[i] = vector_summ(v[i], state->cursor);
    }

    SDL_RenderDrawLine(renderer,  state->v[0].x, state->v[0].y,
                       state->v[1].x, state->v[1].y);
    SDL_RenderDrawLine(renderer,  state->v[1].x, state->v[1].y,
                       state->v[2].x, state->v[2].y);
    SDL_RenderDrawLine(renderer, state->v[2].x, state->v[2].y,
                       state->v[0].x, state->v[0].y);


    SDL_RenderDrawLine(renderer,  v[0].x, v[0].y,
                       v[1].x, v[1].y);
    SDL_RenderDrawLine(renderer,  v[1].x, v[1].y,
                       v[2].x, v[2].y);
    SDL_RenderDrawLine(renderer, v[2].x, v[2].y,
                       v[0].x, v[0].y);

    AnyShape result;
    result = triangle_rotate(state->polygon, state->angle);
    result = triangle_scale(&result, state->scale);
    shape_draw(renderer, &result, 625, 425);

    AnyShape c;
    c = shape_scale(&(state->c), state->scale * 0.5);
    shape_draw(renderer, (Shape *)(&c), 650, 125);

    AnyShape r;
    r = shape_scale(&(state->square), state->scale);
    r = shape_rotate(&r, state->angle);
    shape_draw(renderer, &r, 375, 275);

    SDL_RenderPresent(renderer);

    return 0;
}

int PongInputHandler(PongGameState *pong_game_state)
{
    if(NULL == pong_game_state) {
        return 1;
    }

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_KEYDOWN:
            if(SDLK_ESCAPE != event.key.keysym.sym) {
                break;
            }
        case SDL_QUIT:
            pong_game_state->exit = true;
            break;
        default:
            break;
        }
    }

    return 0;
}

int PongActionHandler(PongGameState *pong_game_state)
{
    return 0;
}

int PongRender(SDL_Renderer *renderer, PongGameState *pong_game_state)
{
    SDL_Color *palette = pong_game_state->color;
    int clear_color_index = pong_game_state->current_color;
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

    for(int i = 0; i < 3; ++i) {
        SDL_Color *draw_color = &(palette[0]);
        SDL_SetRenderDrawColor(renderer,
                               draw_color->r,
                               draw_color->g,
                               draw_color->b,
                               draw_color->a);
    }
    SDL_Color *color = &(palette[2]);
    SDL_SetRenderDrawColor(renderer,
                           color->r,
                           color->g,
                           color->b,
                           color->a);

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

    /* SquareGameState square_game_state;
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
    FreeVectorGameState(&vector_game_state); */

    PongGameState pong_game_state;
    InitPongGameState(&pong_game_state);
    while(!(pong_game_state.exit)) {
        PongInputHandler(&pong_game_state);

        PongActionHandler(&pong_game_state);

        PongRender(renderer, &pong_game_state);
    }
    FreePongGameState(&pong_game_state);

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
