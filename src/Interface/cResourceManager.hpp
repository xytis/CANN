#ifndef CRESOURCEMANAGER_H_INCLUDED
#define CRESOURCEMANAGER_H_INCLUDED

#include "Utils/exception.hpp"
#include "Utils/sdl_video.hpp"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <string>
#include <map>
#include <iostream>

#include <algorithm>

/**
    TODO:
        Reikia kad cResourceManager slėptų nuo programos visus veiksmus susijusius su failais.
        T.y. ir tekstinių failų užkrovimą ir animacijų ar tekstūrų sukūrimą
        ir fontų ar .ini failų sukėlimą į struktūras
*/

namespace Interface
{

    struct Font
    {
        std::string filename;   /*!< Filename for the font relative to the root directory. */
        int size;               /*!< Font size */
    };

    struct Image
    {
    	std::string filename;
    	void * owner;
    };

    //! Class for std::map to compare two Font classes.
    /*!
     Class with () operator overridden used for std::map to sort on.
     Checks filename alphabetically, if it's the same filename it then
     uses the size property for comparison.
    */
    struct FontCompare
    {
        //! Returns True if f1 is evaluated less than f2
        /*!
         \param f A Font class
         \param f2 A Font class
         \return True if f1 evaluated ltutess than f2
         \sa ResourceMap::fonts
        */
        bool operator()(Font f1, Font f2)
        {
            int cres = strcmp(f1.filename.c_str(), f2.filename.c_str());
            if(cres < 0)
                return true;
            else if(cres > 0)
                return false;
            else
                return (f1.size < f2.size);
        }
    };

    struct ImageCompare
    {
    	bool operator()(Image i1, Image i2)
    	{
    		int cres = strcmp(i1.filename.c_str(), i2.filename.c_str());
			if(cres < 0)
				return true;
			else if(cres > 0)
				return false;
			else
				return (i1.owner < i2.owner);
    	}
    };

    struct OwnerCompare
    {
    	void * owner;
    	bool compare(Image i)
    	{
    		return i.owner == owner;
    	}
    	bool compare(Font f)
    	{
    		return false;
    	}
    };

    class cResourceManager
    {
        private:
            std::map<Font, TTF_Font*,FontCompare> fonts;
            std::map<Image, SDL_Surface*, ImageCompare> images;
            std::string resource_dir;
        public:
            cResourceManager(std::string dir):resource_dir(dir) {};
            SDL_Surface* get_image(std::string filename, void * owner);
            SDL_Surface* get_image(Image);
            TTF_Font* get_font(std::string filename, int size);
            TTF_Font* get_font(Font);
            void release_by_owner(void * owner);
            void release_image(Image);
            void release_font(Font);
            void clean_up();
    };
};

#endif // CRESOURCEMANAGER_H_INCLUDED
