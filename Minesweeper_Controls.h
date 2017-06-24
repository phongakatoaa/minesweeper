#ifndef CONTROLS_H

#include <SDL2/SDL.h>

enum KEYS {
    W, A, S, D, ESC, SPACE, SHIFT, DEFAULT
};
class Control {
    SDL_Event event;
    KEYS key;
public:
    void receiveKeyPressed();
    void resetKey();
    KEYS getKey() const;
};

void Control::receiveKeyPressed()
{
    while ( SDL_PollEvent( &event ) != 0 ) {
        if ( event.type == SDL_KEYDOWN ) {
            switch ( event.key.keysym.sym ) {
                case SDLK_w:        key = W; break;
                case SDLK_a:        key = A; break;
                case SDLK_s:        key = S; break;
                case SDLK_d:        key = D; break;
                case SDLK_SPACE:    key = SPACE; break;
                case SDLK_ESCAPE:   key = ESC; break;
                case SDLK_f:        key = SHIFT; break;
                default:            key = DEFAULT; break;
            }
        }
    }
}

void Control::resetKey()
{
    key = DEFAULT;
}

KEYS Control::getKey() const {
    return key;
}

#endif // CONTROLS_H
