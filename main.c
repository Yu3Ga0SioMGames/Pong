#include <stdint.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "shape.h"
#include "object.h"
#include "collision.h"

const int racket_speed = 6;
const int racket_height = 120;
const int racket_weight = 25;

typedef
struct
{
    bool exit;
    bool r1Up;
    bool r1Down;
    bool r2Up;
    bool r2Down;
    int current_color;
    SDL_Color color[3];
    GameObject racket_1;
    GameObject racket_2;
    GameObject boll;
} PongGameState;

void InitPongGameState(PongGameState *pong_game_state)
{
    pong_game_state->exit = false;

    pong_game_state->r1Up = false;
    pong_game_state->r1Down = false;
    pong_game_state->r2Up = false;
    pong_game_state->r2Down = false;

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
    Square *racket_shape = shape_create_square(racket_height, racket_weight);
    // Vector collider_displacement = ;
    rk->scene_position.x = 40;
    rk->scene_position.y = 90;
    rk->direction.x = 0;
    rk->direction.y = 0;
    rk->shape = racket_shape;
    rk->velocity.x = 0;
    rk->velocity.y = 0;
    rk->collider_type = 2;
    rk->collider = malloc(sizeof(RectangleCollider));
    RectangleCollider *rc = (RectangleCollider *)(rk->collider);
    rc->p.x = rk->scene_position.x;
    rc->p.y = rk->scene_position.y;
    rc->w = racket_shape->points->x;
    rc->h = racket_shape->points->y;
    // rk->collider_displacement.x = ;

    rk = &pong_game_state->racket_2;
    rk->scene_position.x = 760;
    rk->scene_position.y = 525;
    rk->direction.x = 0;
    rk->direction.y = 0;
    rk->shape = racket_shape;
    rk->velocity.x = 0;
    rk->velocity.y = 0;
    rk->collider_type = 2;
    rk->collider = (RectangleCollider *)malloc(sizeof(RectangleCollider));
    rc = (RectangleCollider *)(rk->collider);
    rc->p.x = rk->scene_position.x;
    rc->p.y = rk->scene_position.y;
    rc->w = racket_shape->points->x;
    rc->h = racket_shape->points->y;

    Circle *boll_shape = shape_create_circle(1);
    rk = &pong_game_state->boll;
    rk->scene_position.x = 400;
    rk->scene_position.y = 300;
    rk->direction.x = 0;
    rk->direction.y = 0;
    rk->shape = boll_shape;
    rk->velocity.x = 0;
    rk->velocity.y = 0;
    rk->collider_type = 1;
    rk->collider = (CircleCollider *)malloc(sizeof(CircleCollider));
    CircleCollider *cr = (CircleCollider *)(rk->collider);
    cr->center.x = rk->scene_position.x;
    cr->center.y = rk->scene_position.y;
    cr->r = boll_shape->radius * 10;
}

void FreePongGameState(PongGameState *pong_game_state)
{
    shape_free_square(pong_game_state->racket_1.collider);
    shape_free_square(pong_game_state->racket_2.collider);
    shape_free_circle(pong_game_state->boll.collider);
}

int PongInputHandler(PongGameState *pong_game_state)
{
    if(NULL == pong_game_state) {
        return 1;
    }

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_KEYUP:
            switch(event.key.keysym.sym) {
            case SDLK_LSHIFT:
                pong_game_state->r1Up = false;
                break;
            case SDLK_LCTRL:
                pong_game_state->r1Down = false;
                break;
            case SDLK_RSHIFT:
                pong_game_state->r2Up = false;
                break;
            case SDLK_RCTRL:
                pong_game_state->r2Down = false;
                break;
            }
            break;
        case SDL_KEYDOWN: {
            switch(event.key.keysym.sym) {
            case SDLK_LSHIFT:
                pong_game_state->r1Up = true;
                break;
            case SDLK_LCTRL:
                pong_game_state->r1Down = true;
                break;
            case SDLK_RSHIFT:
                pong_game_state->r2Up = true;
                break;
            case SDLK_RCTRL:
                pong_game_state->r2Down = true;
                break;
            }

            if(SDLK_ESCAPE != event.key.keysym.sym) {
                break;
            }
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
    int x_mov = 0;
    int y_mov = 0;
    if(pong_game_state->r1Up) {
        y_mov -= racket_speed;
    }
    if(pong_game_state->r1Down) {
        y_mov += racket_speed;
    }
    move_gameobject_bounded(&(pong_game_state->racket_1), x_mov, y_mov, 0, 800, 0, 600);

    x_mov = 0;
    y_mov = 0;
    if(pong_game_state->r2Up) {
        y_mov -= racket_speed;
    }
    if(pong_game_state->r2Down) {
        y_mov += racket_speed;
    }
    move_gameobject(&(pong_game_state->racket_2), x_mov, y_mov);

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

    draw_gameobject(renderer,
                    &(pong_game_state->racket_1),
                    pong_game_state->racket_1.scene_position.x,
                    pong_game_state->racket_1.scene_position.y);
    draw_gameobject(renderer,
                    &(pong_game_state->racket_2),
                    pong_game_state->racket_2.scene_position.x,
                    pong_game_state->racket_2.scene_position.y);

    color = &(palette[1]);
    SDL_SetRenderDrawColor(renderer,
                           color->r,
                           color->g,
                           color->b,
                           color->a);

    draw_gameobject(renderer,
                    &(pong_game_state->boll),
                    pong_game_state->boll.scene_position.x,
                    pong_game_state->boll.scene_position.y);

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

    PongGameState pong_game_state;
    InitPongGameState(&pong_game_state);
    while(!(pong_game_state.exit)) {
        PongInputHandler(&pong_game_state);

        PongActionHandler(&pong_game_state);

        PongRender(renderer, &pong_game_state);

        SDL_Delay(1000 / 90);
    }
    FreePongGameState(&pong_game_state);

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
