#include "../include/sdl_video.h"

void SDLVideo::apply_surface(SDL_Surface* src_surface, int src_x, int src_y, int src_w, int src_h,
    SDL_Surface* dst_surface, int dst_x, int dst_y, int alpha)
{
    SDL_Rect src_rect, dst_offset;

    src_rect.x = src_x;
    src_rect.y = src_y;
    src_rect.w = src_w;
    src_rect.h = src_h;

    dst_offset.x = dst_x;
    dst_offset.y = dst_y;

    SDL_SetAlpha(src_surface, SDL_SRCALPHA, alpha);
    SDL_BlitSurface(src_surface, &src_rect, dst_surface, &dst_offset);
}

SDL_Color SDLVideo::make_color(int r, int g, int b)
{
    SDL_Color c = {r, g, b};
    return c;
}
