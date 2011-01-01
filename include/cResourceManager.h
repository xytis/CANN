#ifndef CRESOURCEMANAGER_H_INCLUDED
#define CRESOURCEMANAGER_H_INCLUDED

#include "../include/exception.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <string>
#include <map>
#include <iostream>

/**
    TODO:
        Reikia kad cResourceManager slėptų nuo programos visus veiksmus susijusius su failais.
        T.y. ir tekstinių failų užkrovimą ir animacijų ar tekstūrų sukūrimą
        ir fontų ar .ini failų sukėlimą į struktūras
*/

namespace Interface
{
    class cResourceManager
    {
        private:
            std::map<std::string, SDL_Surface*> images;
            std::string resource_dir;
        public:
            cResourceManager(std::string dir):resource_dir(dir) {};
            SDL_Surface* get_image(std::string);
            void release_image(std::string);
            void clean_up();
    };
};

#endif // CRESOURCEMANAGER_H_INCLUDED
