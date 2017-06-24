#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Minesweeper_Controls.h"
#include "Minesweeper_Board.h"
#include "Minesweeper_Gallery.h"
using namespace std;

const int MAXIMUM_MINES = 20;
const int BLOCK_SIZE = 40;
const int SCREEN_WIDTH = BOARD_WIDTH * BLOCK_SIZE;
const int SCREEN_HEIGHT = BOARD_HEIGHT * BLOCK_SIZE;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

void refreshScreen();
void renderGameOver();
bool winCondition( const Board& board );
void renderWin();

int main( int argc, char* args[] ) {
    srand( time(0) );

    SDL_Init( SDL_INIT_EVERYTHING ); //initializez SDL 2.0
    IMG_Init( IMG_INIT_PNG ); //initialize SDL image

    window = SDL_CreateWindow( "MINESWEEPER 2.0 (SDL)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    screenSurface = SDL_GetWindowSurface( window );

    loadGallery();

    Board board;

    board.placeMines( MAXIMUM_MINES );
    Control control;

    bool quit = false;

    while ( !quit ) {
        if ( winCondition( board ) ) {
            revealAllMines( board );
            renderBoard( board );
            SDL_Delay(2000);
            quit = true;
            renderWin();
            SDL_Delay( 5000 );
        }
        control.resetKey();
        control.receiveKeyPressed();
        if ( control.getKey() == ESC ) quit = true;
        if ( control.getKey() == SHIFT ) {
            if ( board.board[board.selected_x][board.selected_y].flagged ) board.board[board.selected_x][board.selected_y].unflag();
            else if ( !board.board[board.selected_x][board.selected_y].revealed ) board.board[board.selected_x][board.selected_y].flag();
        }
        if ( control.getKey() == SPACE && !board.board[board.selected_x][board.selected_y].flagged ) {
            if ( board.board[board.selected_x][board.selected_y].type == MINE )
                {
                    revealAllMines( board );
                    renderBoard( board );
                    SDL_Delay(2000);
                    //cout << "game over" << endl;
                    quit = true;
                    renderGameOver();
                    SDL_Delay( 5000 );
                }
            else
                expand( board, board.selected_x, board.selected_y );
                cout << surroundMines( board, board.selected_x, board.selected_y ) << endl;
        }
        else selectBlock( board, control );
        //refreshScreen();
        renderBoard( board );
        SDL_Delay(50);
    }

    SDL_FreeSurface( screenSurface );
    SDL_DestroyWindow( window );
    IMG_Quit();
    SDL_Quit();
    return 0;
}

void renderBoard( const Board& board )
{
    SDL_Rect block_position;
    block_position.h = block_position.w = BLOCK_SIZE;
    for ( int width = 0; width < BOARD_WIDTH; width++ ) {
        for ( int height = 0; height < BOARD_HEIGHT; height++ ) {
            block_position.x = width * BLOCK_SIZE;
            block_position.y = height * BLOCK_SIZE;
            if ( !board.board[width][height].revealed ) {
                if ( !board.board[width][height].selected )  {
                    if ( !board.board[width][height].flagged )
                        SDL_BlitScaled ( g_block[0], NULL, screenSurface, &block_position );
                    else
                        SDL_BlitScaled ( g_flag[0], NULL, screenSurface, &block_position );
                }
                else {
                    if ( !board.board[width][height].flagged )
                        SDL_BlitScaled ( g_block[1], NULL, screenSurface, &block_position );
                    else
                        SDL_BlitScaled ( g_flag[1], NULL, screenSurface, &block_position );
                }
            }
            else switch( board.board[width][height].type ) {
                case MINE: {
                    if ( !board.board[width][height].selected )
                        SDL_BlitScaled ( g_mine[0], NULL, screenSurface, &block_position );
                    else
                        SDL_BlitScaled ( g_mine[1], NULL, screenSurface, &block_position );
                } break;
                default:
                {
                    int getSurroundMines = surroundMines( board, width, height );
                    if ( getSurroundMines == 0 ) {
                        if ( !board.board[width][height].selected )
                            SDL_BlitScaled ( g_block[2], NULL, screenSurface, &block_position );
                        else
                            SDL_BlitScaled ( g_block[1], NULL, screenSurface, &block_position );
                    }
                    else {
                        for ( int temp = 1; temp <= 8; temp++ ) {
                            if ( getSurroundMines == temp ) {
                                if ( !board.board[width][height].selected )
                                    SDL_BlitScaled ( g_normal_number[temp - 1], NULL, screenSurface, &block_position );
                                else
                                    SDL_BlitScaled ( g_selected_number[temp - 1], NULL, screenSurface, &block_position );
                            }
                        }
                    }
                }
                break;
            }
        }
    }
    SDL_UpdateWindowSurface( window );
}

void refreshScreen()
{
    SDL_Rect Screen;
    Screen.x = Screen.y = 0;
    Screen.w = SCREEN_WIDTH; Screen.h = SCREEN_HEIGHT;
    SDL_BlitScaled( g_block[0], NULL, screenSurface, &Screen );
}

void renderGameOver()
{
    SDL_Rect GameOver;
    GameOver.x = 0; GameOver.y = 200;
    GameOver.h = 200; GameOver.w = SCREEN_WIDTH;
    SDL_BlitScaled ( loadSurface( "data/media/img/gameover.png" ), NULL, screenSurface, &GameOver );
    SDL_UpdateWindowSurface( window );
}

bool winCondition( const Board& board ) {
    for ( int width = 0; width < BOARD_WIDTH; width++ ) {
        for ( int height = 0; height < BOARD_HEIGHT; height++ ) {
            if ( board.board[width][height].type != MINE && !board.board[width][height].revealed ) return false;
        }
    }
    return true;
}

void renderWin()
{
    SDL_Rect Win;
    Win.x = 0; Win.y = 200;
    Win.h = 200; Win.w = SCREEN_WIDTH;
    SDL_BlitScaled ( loadSurface( "data/media/img/YouWin.png" ), NULL, screenSurface, &Win );
    SDL_UpdateWindowSurface( window );
}
