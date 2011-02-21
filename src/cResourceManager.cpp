#include "../include/cResourceManager.h"

namespace Interface
{
    SDL_Surface* cResourceManager::
    get_image(std::string filename, void * owner)
    {
    	Image I;
    	I.filename = filename;
    	I.owner = owner;
    	return get_image(I);
    }

    SDL_Surface* cResourceManager::
    get_image(Image I)
    {
        std::string  filename = resource_dir + I.filename;

        SDL_Surface * loaded;
        SDL_Surface * copy;
        std::map<Image,SDL_Surface*>::iterator iter = images.find(I);
        //If it's not the first time owner requests an image:
        if(iter != images.end())
        {
            return iter->second;
        }
        //If it's the first time:
        else
        {
            SDL_Surface *loadedImage = NULL;
            SDL_Surface *optimizedImage = NULL;

            loadedImage = IMG_Load(filename.c_str());

            if(loadedImage != NULL)
            {
                optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
                std::cout << "Image loaded: " << filename << std::endl;
                SDL_FreeSurface(loadedImage);
            }
            else
            {
                std::cout << "Image failed to load: " << IMG_GetError() << std::endl;
                throw exception::custom(IMG_GetError());
            }

            images[I] = optimizedImage;

            return optimizedImage;
        }
    }

    void cResourceManager::
    release_image(Image I)
    {
        std::map<Image,SDL_Surface*>::iterator iter = images.find(I);
        if(iter != images.end())
        {
            SDL_FreeSurface(iter->second);
        }
        images.erase(iter);
    }

    void cResourceManager::
    clean_up()
    {
        // Clear loaded image surfaces
        std::map<Image,SDL_Surface*>::iterator image_iter;
        for(image_iter = images.begin(); image_iter != images.end(); ++image_iter)
        {
            SDL_FreeSurface(image_iter->second);
        }
        images.clear();

        // Clear loaded fonts
        std::map<Font,TTF_Font*,FontCompare>::iterator font_iter;
        for(font_iter = fonts.begin(); font_iter != fonts.end(); ++font_iter)
        {
            TTF_CloseFont(font_iter->second);
        }

        fonts.clear();
    }

    void cResourceManager::
    release_by_owner(void * owner)
    {
    	/*
    	OwnerCompare c;
    	c.owner = owner;
    	std::map<Image,SDL_Surface*>::iterator image_iter;
    	while ((image_iter = find_if(images.begin(), images.end(), c.compare)) != images.end())
    	{
    		SDL_FreeSurface(image_iter->second);
    		images.erase(image_iter, ++image_iter);
    	}
    	*/
    }

    TTF_Font* cResourceManager::
    get_font(std::string filename, int size)
    {
    	Font F;
    	F.filename = filename;
    	F.size = size;
    	return get_font(F);
    }

    TTF_Font* cResourceManager::
    get_font(Font font)
    {
        std::map<Font,TTF_Font*,FontCompare>::iterator iter = fonts.find(font);
        if(iter != fonts.end())
        {
            return iter->second;
        }
        else
        {
            fonts[font] = TTF_OpenFont((resource_dir + font.filename).c_str(), font.size);
        }

        return fonts[font];
    }

    void cResourceManager::
    release_font(Font font)
    {
        std::map<Font,TTF_Font*,FontCompare>::iterator iter = fonts.find(font);
        if(iter != fonts.end())
        {
            TTF_CloseFont(iter->second);
        }
    }

};
