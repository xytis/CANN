#include "SDL/SDL.h"

#ifndef SDL_VIDEO_H_INCLUDED
#define SDL_VIDEO_H_INCLUDED

class SDLVideo
{
    public:
        static void apply_surface(
            SDL_Surface* src_surface, int src_x, int src_y, int src_w, int src_h,
            SDL_Surface* dst_surface, int dst_x, int dst_y, int alpha = 255
        );
        static SDL_Color make_color(int r, int g, int b);
};

#endif // SDL_VIDEO_H_INCLUDED
