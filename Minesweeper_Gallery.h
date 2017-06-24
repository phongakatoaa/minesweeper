#ifndef GALLERY_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

extern SDL_Surface* screenSurface;
// g_ stand for gallery_
std::vector < SDL_Surface* > g_block;
std::vector < SDL_Surface* > g_mine;
std::vector < SDL_Surface* > g_normal_number;
std::vector < SDL_Surface* > g_selected_number;
std::vector < SDL_Surface* > g_flag;

SDL_Surface* loadSurface( std::string path ); //load png image using sdl2_image.h
void loadGallery(); //no need for explanation

SDL_Surface* loadSurface( std::string path )
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        std::cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, screenSurface->format, NULL );
        if( optimizedSurface == NULL )
        {
            std::cout << "Unable to optimize image " << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}

void loadGallery()
{
    SDL_Surface* load = NULL;
    //load block image ( not revealed )
    //load normal block image
    load = loadSurface( "data/media/img/normal_block.png" );
    g_block.push_back( load );
    //load selected block image
    load = loadSurface( "data/media/img/selected_block.png" );
    g_block.push_back( load );
    //load null block
    load = loadSurface( "data/media/img/revealed_null_block.png" );
    g_block.push_back( load );
    //load mine image
    //load normal mine image
    load = loadSurface( "data/media/img/normal_mine.png" );
    g_mine.push_back( load );
    //load player-hit-mine condition mine image
    load = loadSurface( "data/media/img/hit_mine.png" );
    g_mine.push_back( load );
    //load number-of-mines image
    //from 1-8 because the maximum number of mines surrounding a block is 8
    std::string number[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8" };
    std::string path;
    //load normal number image
    for ( int temp = 1; temp < 9; temp++ ) {
         path = "data/media/img/normal_" + number[temp] + ".png";
         std::cout << path << std::endl;
         load = loadSurface( path );
         g_normal_number.push_back( load );
    }
    //load selected number image
    for ( int temp = 1; temp < 9; temp++ ) {
         path = "data/media/img/selected_" + number[temp] + ".png";
         std::cout << path << std::endl;
         load = loadSurface( path );
         g_selected_number.push_back( load );
    }
    //load flag image
    //load normal flag image
    load = loadSurface( "data/media/img/normal_flag.png" );
    g_flag.push_back(load);
    load = loadSurface( "data/media/img/selected_flag.png" );
    g_flag.push_back(load);
}
#endif // GALLERY_H
