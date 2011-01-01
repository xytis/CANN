#include "../include/cResourceManager.h"

namespace Interface
{
    SDL_Surface* cResourceManager::
    get_image(std::string filename)
    {
        std::map<std::string,SDL_Surface*>::iterator iter = images.find(filename);
        if(iter != images.end())
        {
            return iter->second;
        }
        else
        {
            SDL_Surface *loadedImage = NULL;
            SDL_Surface *optimizedImage = NULL;

            filename = resource_dir + filename;

            std::cout << filename << std::endl;
            loadedImage = IMG_Load(filename.c_str());

            if(loadedImage != NULL)
            {
                optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
                SDL_FreeSurface(loadedImage);
            }
            else
            {
                std::cout << "Image failed to load: " << IMG_GetError() << std::endl;
                throw exception::custom(IMG_GetError());
            }

            images[filename] = optimizedImage;

            return optimizedImage;
        }
    }

    void cResourceManager::
    release_image(std::string filename)
    {
        std::map<std::string,SDL_Surface*>::iterator iter = images.find(filename);
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
        std::map<std::string,SDL_Surface*>::iterator image_iter;
        for(image_iter = images.begin(); image_iter != images.end(); ++image_iter)
        {
            SDL_FreeSurface(image_iter->second);
        }
        images.clear();
    }
};
