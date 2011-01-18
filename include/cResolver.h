#ifndef CRESOLVER_H_INCLUDED
#define CRESOLVER_H_INCLUDED

#include <SDL/SDL.h>

//Makes the diferent resolving procedures usable =]
class cResolver
{
    public:
        virtual bool Call(SDL_Event *) = 0;
};

#endif // CRESOLVER_H_INCLUDED
