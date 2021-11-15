#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>


#include "tic_tac_types.h"
#include "tic_tac_const_str_winners.h"

//! Check N
#ifndef N
#define N 3
#elif N < 2
#error N is to low
#endif

typedef struct
{
    int x1,y1;
    int cell_size, 
    line_size;  // always = 1
} TIC_TAC_SDL_field_t;

//! FIELD SIZE
size_t GET_SIZE()
{
    return (size_t)N;
}

#define  GET_SIZE_X() GET_SIZE()
#define  GET_SIZE_Y() GET_SIZE()


//! FIELD
TIC_TAC_PIECE** g_p_field = NULL;

//! Functional
TIC_TAC_BOOL
clean_tic_tac_field(TIC_TAC_PIECE ** p_field)
{
    //if (g_p_field != NULL)
    //{
        size_t i;
        for (i = 0; i < GET_SIZE_Y();++i)
        {
            free(p_field[i]);
        }
        free(p_field);
        p_field = NULL;
    //}
}

TIC_TAC_ERROR
fill_field_with_free_peace(TIC_TAC_PIECE * const * const p_field)
{
    //! Fill field with start value
    size_t i,j;
    for (i = 0; i < GET_SIZE_Y(); ++i)
    {
        for (j = 0; j < GET_SIZE_X(); ++j)
        {
            p_field[i][j] = TIC_TAC_PIECE_FREE_PLACE;
        }
    }
    return TIC_TAC_ERROR_NO_PROBLEM;
}

TIC_TAC_ERROR
allocate_tic_tac_field(TIC_TAC_PIECE *** p_field)
{
    size_t i,j;
    //! check p_field == NULL later
    //if (g_p_field == NULL )
    
    //! Memorry allocation
    (*p_field) = (TIC_TAC_PIECE**)malloc(sizeof(TIC_TAC_PIECE*) * GET_SIZE_X());
    if ((*p_field)  == NULL)
        return TIC_TAC_ERROR_MEMORRY_PROBLEM;

    for (i = 0; i < GET_SIZE_X(); ++i)
    {
        (*p_field) [i] = (TIC_TAC_PIECE*)malloc(sizeof(TIC_TAC_PIECE) * GET_SIZE_Y());
        if ((*p_field) [i] == NULL)
        {
            for (j = 0; j < i; ++j)
            {
                free((*p_field) [j]);
            }
            free((*p_field));
            return TIC_TAC_ERROR_MEMORRY_PROBLEM;
        }
    }
    return TIC_TAC_ERROR_NO_PROBLEM;
}

TIC_TAC_WINNER
tic_tac_get_winner(TIC_TAC_PIECE * const * const p_field)
{
    //! variables
    size_t i,j;
    uint8_t fl_need_to_continue_search = 0;

    // check rows
    for (i = 0; (i < GET_SIZE_X()); ++i)
    {
        //!
        if (p_field[i][0] == TIC_TAC_PIECE_FREE_PLACE)
            fl_need_to_continue_search = 0;
        else
            fl_need_to_continue_search = 1;

        //!
        for (j = 1; (fl_need_to_continue_search == 1) && j < GET_SIZE_Y(); ++j)
        {

            if (p_field[i][j-1] != p_field[i][j])
                fl_need_to_continue_search = 0;
        }

        //! 
        if (fl_need_to_continue_search == 1)
            return (TIC_TAC_WINNER)p_field[i][0];
    }

    //! check columns
    for (j = 0; (j < GET_SIZE_Y()); ++j)
    {
        //!
        if (p_field[0][j] == TIC_TAC_PIECE_FREE_PLACE)
            fl_need_to_continue_search = 0;
        else
            fl_need_to_continue_search = 1;

        //!
        for (i = 1; (fl_need_to_continue_search == 1) && i < GET_SIZE_X(); ++i)
        {

            if (p_field[i-1][j] != p_field[i][j])
                fl_need_to_continue_search = 0;
        }

        //!
        if (fl_need_to_continue_search == 1)
        {
            return (TIC_TAC_WINNER)p_field[0][j];
        }
    }

    //! check cross left - right
    if (p_field[0][0] == TIC_TAC_PIECE_FREE_PLACE)
        fl_need_to_continue_search = 0;
    else
        fl_need_to_continue_search = 1;
    for (i = 1; (fl_need_to_continue_search == 1) &&  i < (GET_SIZE_X() ); ++i)
        if (p_field[i][i] != p_field[i - 1][i - 1])
            fl_need_to_continue_search = 0;
    if (fl_need_to_continue_search == 1)
        return (TIC_TAC_WINNER)p_field[0][0];

    //! check cross right - left
    if (p_field[0][GET_SIZE_X()-1] == TIC_TAC_PIECE_FREE_PLACE)
        fl_need_to_continue_search = 0;
    else
        fl_need_to_continue_search = 1;
    for (i = 1; (fl_need_to_continue_search == 1) &&  i < (GET_SIZE_X() ); ++i)
        if (p_field[i][(GET_SIZE_Y() - 1) - i] != p_field[i - 1][(GET_SIZE_Y() - 2) - i])
            fl_need_to_continue_search = 0;
    if (fl_need_to_continue_search == 1)
        return (TIC_TAC_WINNER)p_field[0][0];

    //! check for (free places)
    for (i = 0; i < GET_SIZE_X(); ++i)
    {
        for (j = 0; j < GET_SIZE_Y(); ++j)
        {
            if (p_field[i][j] == TIC_TAC_PIECE_FREE_PLACE)
                return TIC_TAC_WINNER_NO_WINNER;
        }
    }

    //! 
    return TIC_TAC_WINNER_FRIENDS_WIN;
}

TIC_TAC_ERROR 
init_tic_tac_field(TIC_TAC_PIECE *** p_field)
{
    //! variables
    size_t i,j;
    TIC_TAC_ERROR error;
    
    //! CHECK
    if ((*p_field) != NULL)
    {
        clean_tic_tac_field((*p_field));
    }

    error = allocate_tic_tac_field(p_field);
    
    if (error == TIC_TAC_ERROR_NO_PROBLEM)
    {

        return fill_field_with_free_peace((*p_field));
    }
    return error;
}

TIC_TAC_ERROR
set_piece(TIC_TAC_PIECE * const * const p_field, const size_t pos_x, const size_t pos_y, const TIC_TAC_PIECE piece)
{
    if (p_field[pos_y][pos_x] == TIC_TAC_PIECE_FREE_PLACE)
    {
        p_field[pos_y][pos_x] = piece;
        return TIC_TAC_ERROR_NO_PROBLEM;
    }
    
    return TIC_TAC_ERROR_NOT_EMPTY_PIECE;
}

TIC_TAC_BOOL
can_move(TIC_TAC_PIECE * const * const p_field, size_t pos_x, size_t pos_y)
{
    //! check correct
    if (pos_x >= GET_SIZE_X())
        return TIC_TAC_BOOL_FALSE;
    

    if (pos_y >= GET_SIZE_Y())
        return TIC_TAC_BOOL_FALSE;
    
    //! check free
    if (p_field[pos_y][pos_x] == TIC_TAC_PIECE_FREE_PLACE)
        return TIC_TAC_BOOL_TRUE;
    else
        return TIC_TAC_BOOL_FALSE;

    //! return true 
    return TIC_TAC_BOOL_TRUE;
}

////////////////////////////////////
/////////////  players /////////////
////////////////////////////////////

static TIC_TAC_PLAYER g_s_cur_player = TIC_TAC_PLAYER_NO;

////////////////////////////////////
//////////// game state ////////////
////////////////////////////////////

typedef enum
{
    e_ps_init = 0,
    e_ps_main_loop,
    e_ps_game_is_over,
} e_programm_state;

static e_programm_state g_s_cur_state = e_ps_init;

void
step(int x, int y)
{
 
    if (can_move(g_p_field, x, y) == TIC_TAC_BOOL_TRUE)
    {
        set_piece(g_p_field, x, y,g_s_cur_player);
        change_player();
    }
}

void
change_player()
{
    if (g_s_cur_player == TIC_TAC_PLAYER_TIC)
        g_s_cur_player = TIC_TAC_PLAYER_TAC;
    else
        g_s_cur_player = TIC_TAC_PLAYER_TIC;
}

void view_field(TIC_TAC_PIECE ** p_field_state, TIC_TAC_SDL_field_t *p_field, SDL_Renderer *p_renderer)
{
    int i,j;
    draw_field_2(p_field);
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
            if (g_p_field[i][j] == TIC_TAC_PIECE_TIC)
                draw_cross_in_field(p_renderer, p_field,i,j);
            else if (g_p_field[i][j] == TIC_TAC_PIECE_TAC)
                draw_circle_in_field(p_renderer, p_field,i,j);
}

void
change_state(e_programm_state e_ps_new_state)
{
    g_s_cur_state = e_ps_new_state;
    /*switch(e_ps_new_state)
    {
        case e_ps_init:
            g_s_cur_state = e_ps_;
            break;
        case e_ps_main_loop:
            g_s_cur_state = e_ps_main_loop;
            break;
        case e_ps_game_is_over:
            g_s_cur_state = e_ps_game_is_over;
            break;
    }*/
}

////////////////////////////////////
/////////////// main ///////////////
////////////////////////////////////


#define WIDTH 800
#define HEIGHT 600
#define IMG_PATH "1.png"


int get_field_width(TIC_TAC_SDL_field_t *p_field)
{
    return p_field->cell_size * 3 + p_field->line_size * 2;
}

int get_field_height(TIC_TAC_SDL_field_t *p_field)
{
    return get_field_width(p_field);
}

int get_total_field_width(TIC_TAC_SDL_field_t *p_field)
{
    return p_field->x1 + p_field->cell_size * 3 + p_field->line_size * 2;
}

int get_total_field_height(TIC_TAC_SDL_field_t *p_field)
{
    return p_field->y1 + p_field->cell_size * 3 + p_field->line_size * 2;
}

int get_col_pos( TIC_TAC_SDL_field_t *p_field, int mouse_x, int mouse_y)
{
    if (!p_field)
    {
        printf("SHIT\n");
        return -1;
    }

    if (mouse_x > get_total_field_width(p_field))
    {
        printf("SHIT: mouse_x: %d height: %d", mouse_x, get_total_field_width(p_field));
        return -1;
    }
    
    if (mouse_x < p_field->x1)
        return -1;

    if (mouse_x > p_field->x1 + 2 * p_field->line_size + 2 * p_field->cell_size)
        return 2;
    
    if (mouse_x > p_field->x1 + 1 * p_field->line_size + 1 * p_field->cell_size)
        return 1;
    
    return 0;
}

int get_row_pos( TIC_TAC_SDL_field_t *p_field, int mouse_x, int mouse_y)
{
    if (!p_field)
    {
        printf("SHIT\n");
        return -1;
    }
    if (mouse_y > get_total_field_height(p_field))
    {
        printf("SHIT: mouse_y: %d height: %d", mouse_y, get_total_field_height(p_field));
        return -1;
    }
    if (mouse_y < p_field->y1)
        return -1;
    if (mouse_y > p_field->y1 + 2 * p_field->line_size + 2 * p_field->cell_size)
        return 2;
    if (mouse_y > p_field->y1 + 1 * p_field->line_size + 1 * p_field->cell_size)
        return 1;
    return 0;
}

void draw_cross(SDL_Renderer * p_renderer, int x1, int y1, int x2, int y2)
{
    printf("draw_cross x1 = %d, y1 = %d, x2 = %d, y2 = %d\n",x1,y1,x2,y2);
    SDL_RenderDrawLine
    (
        p_renderer,
        x1 + 2,
        y1 + 2,
        x2 - 2,
        y2 - 2
    );

    SDL_RenderDrawLine
    (
        p_renderer,
        x2 - 2,
        y1 + 2,
        x1 + 2,
        y2 - 2
    );
}

void draw_cross_in_field(SDL_Renderer *p_renderer, TIC_TAC_SDL_field_t *p_field, int row_pos, int col_pos)
{
    int x1,x2,y1,y2;

    x1 = p_field->x1 + p_field->cell_size * row_pos + p_field->line_size * row_pos;
    x2 = x1 + p_field->cell_size;

    y1 = p_field->y1 + p_field->cell_size * col_pos + p_field->line_size * col_pos;
    y2 = y1 + p_field->cell_size;
    
    draw_cross(p_renderer,x1,y1,x2,y2);
}

void draw_circle_in_field(SDL_Renderer *p_renderer, TIC_TAC_SDL_field_t *p_field, int row_pos, int col_pos)
{
    int x1,x2,y1,y2;

    x1 = p_field->x1 + p_field->cell_size * row_pos + p_field->line_size * row_pos;
    x2 = x1 + p_field->cell_size;

    y1 = p_field->y1 + p_field->cell_size * col_pos + p_field->line_size * col_pos;
    y2 = y1 + p_field->cell_size;
    
    draw_ellipse(p_renderer, x1 + (x2-x1)/2,y1 + (y2-y1)/2, (x2-x1)/2, (y2-y1)/2);
    //draw_cross(p_renderer,x1,y1,x2,y2);
}
void draw_ellipse(SDL_Renderer* r, int x0, int y0, int radiusX, int radiusY)
{
    float pi  = 3.14159265358979323846264338327950288419716939937510;
    float pih = pi / 2.0; //half of pi

    //drew  28 lines with   4x4  circle with precision of 150 0ms
    //drew 132 lines with  25x14 circle with precision of 150 0ms
    //drew 152 lines with 100x50 circle with precision of 150 3ms
    const int prec = 27; // precision value; value of 1 will draw a diamond, 27 makes pretty smooth circles.
    float theta = 0;     // angle that will be increased each loop

    //starting point
    int x  = (float)radiusX * cos(theta);//start point
    int y  = (float)radiusY * sin(theta);//start point
    int x1 = x;
    int y1 = y;

    //repeat until theta >= 90;
    float step = pih/(float)prec; // amount to add to theta each time (degrees)
    for(theta=step;  theta <= pih;  theta+=step)//step through only a 90 arc (1 quadrant)
    {
        //get new point location
        x1 = (float)radiusX * cosf(theta) + 0.5; //new point (+.5 is a quick rounding method)
        y1 = (float)radiusY * sinf(theta) + 0.5; //new point (+.5 is a quick rounding method)

        //draw line from previous point to new point, ONLY if point incremented
        if( (x != x1) || (y != y1) )//only draw if coordinate changed
        {
            SDL_RenderDrawLine(r, x0 + x, y0 - y,    x0 + x1, y0 - y1 );//quadrant TR
            SDL_RenderDrawLine(r, x0 - x, y0 - y,    x0 - x1, y0 - y1 );//quadrant TL
            SDL_RenderDrawLine(r, x0 - x, y0 + y,    x0 - x1, y0 + y1 );//quadrant BL
            SDL_RenderDrawLine(r, x0 + x, y0 + y,    x0 + x1, y0 + y1 );//quadrant BR
        }
        //save previous points
        x = x1;//save new previous point
        y = y1;//save new previous point
    }
    //arc did not finish because of rounding, so finish the arc
    if(x!=0)
    {
        x=0;
        SDL_RenderDrawLine(r, x0 + x, y0 - y,    x0 + x1, y0 - y1 );//quadrant TR
        SDL_RenderDrawLine(r, x0 - x, y0 - y,    x0 - x1, y0 - y1 );//quadrant TL
        SDL_RenderDrawLine(r, x0 - x, y0 + y,    x0 - x1, y0 + y1 );//quadrant BL
        SDL_RenderDrawLine(r, x0 + x, y0 + y,    x0 + x1, y0 + y1 );//quadrant BR
    }
}


void draw_field_2(SDL_Renderer *p_renderer, TIC_TAC_SDL_field_t const * const p_field)
{
    int width =  get_field_width(p_field);
    int height = get_field_height(p_field);
    int x1 = p_field->x1;
    int y1 = p_field->y1;
    SDL_SetRenderDrawColor(p_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    SDL_RenderDrawLine
    (
        p_renderer,
        x1 + p_field->cell_size, 
        y1,
        x1 + p_field->cell_size , 
        y1 + height
    );

    SDL_RenderDrawLine
    (
        p_renderer,
        x1 + p_field->cell_size *2 + p_field->line_size,
        y1,
        x1 + p_field->cell_size  *2 + p_field->line_size,
        y1 + height
    );

    SDL_RenderDrawLine
    (
        p_renderer,
        x1 , 
        y1 + p_field->cell_size,
        x1 + width , 
        y1 + p_field->cell_size
    );

    SDL_RenderDrawLine
    (
        p_renderer,
        x1,
        y1 + p_field->cell_size *2 + p_field->line_size,
        x1 + width,
        y1 + p_field->cell_size *2 + p_field->line_size
    );
}

void draw_field(SDL_Renderer * p_renderer, int x1, int y1, int x2, int y2)
{
    int width = x2 - x1;
    int height = y2 - y1;
    int field_width = 1;
    int line_pos_1_x = (width - field_width* 2) / 3;
    int line_pos_1_y = (height - field_width* 2) / 3;
    SDL_SetRenderDrawColor(p_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    SDL_RenderDrawLine
    (
        p_renderer, 
        x1 + line_pos_1_x, 
        y1,
        x1 + x1 + line_pos_1_x, 
        y2
    );
    SDL_RenderDrawLine
    (
        p_renderer,
        x1 + line_pos_1_x + line_pos_1_x,
        y1,
        x1 + x1 + line_pos_1_x + line_pos_1_x, 
        y2
    );


    SDL_RenderDrawLine
    (
        p_renderer, 
        x1, 
        y1 + line_pos_1_y,
        x2, 
        y1 + line_pos_1_y 
        );
    SDL_RenderDrawLine(p_renderer, x1, y1 + line_pos_1_y + line_pos_1_y, x2, y1 + line_pos_1_y + line_pos_1_y);

}

int main (int argc, char *argv[]) {

    // variable declarations
    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *img = NULL;
    SDL_Event e;
    TIC_TAC_SDL_field_t my_field = {.cell_size = 64, .line_size = 1, .x1 = 15, .y1 = 15};
    int row_pos,col_pos;;
    int w, h; // texture width & height
    int x = 5, y = 5;


    init_tic_tac_field(&g_p_field);
    g_s_cur_player = TIC_TAC_PLAYER_TIC;
    g_s_cur_state = e_ps_init;
    change_state(e_ps_main_loop);
    

    // Initialize SDL.
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
            return 1;
    
    // create the window and renderer
    // note that the renderer is accelerated
    win = SDL_CreateWindow("Image Loading", 100, 100, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    // main loop
    while (1) 
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        //draw_field(renderer,0,0,256,256);
        //draw_cross(renderer, 0 , 0 , 64, 64);
        //draw_ellipse(renderer, 120,120, 20,40);
        draw_field_2(renderer, &my_field);
        // event handling
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        if ( SDL_PollEvent(&e) ) 
        {
            if (e.type == SDL_QUIT)
                break;
            else if( /*e.type == SDL_MOUSEMOTION ||*/ e.type == SDL_MOUSEBUTTONDOWN /* || e.type == SDL_MOUSEBUTTONUP*/)
            {
                SDL_GetMouseState( &x, &y );
                row_pos = get_row_pos(&my_field,x,y);
                col_pos = get_col_pos(&my_field,x,y);
                if (row_pos != -1 && col_pos != -1)
                {
                    //draw_cross_in_field(renderer, &my_field,col_pos,row_pos);
                    //draw_circle_in_field(renderer, &my_field,col_pos,row_pos);
                    //SDL_RenderPresent(renderer);
                    //SDL_Delay(1000);

                    step(row_pos, col_pos);
                    printf("row_pos = %d col_pos =%d\n", row_pos, col_pos);
                }
                else
                {
                    printf("free\n");
                }
            }
            else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
                break;
        }
        //printf("x = %d y =%d\n", x, y);
        //SDL_RenderDrawLine(renderer, 10, 70, x, y);
        // clear the screen

        // copy the texture to the rendering context
        //SDL_RenderCopy(renderer, img, NULL, &texr);
        // flip the backbuffer
        // this means that everything that we prepared behind the screens is actually shown
                    view_field(g_p_field, &my_field,renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(15);
    }
    
    SDL_DestroyTexture(img);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    
    return 0;
}