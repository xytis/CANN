#ifndef CWINDOW_H_INCLUDED
#define CWINDOW_H_INCLUDED

/**
 *  This class manages the window, all events that are connected to window
 *  are managed from here. Thus cMainControler is needed.
 */

#include <SDL/SDL.h>

#include "cMainControler.hpp"
#include "Utils/cResolver.hpp"
#include "Utils/exception.hpp"

namespace Interface
{
    class cWindow
    {
        private:
            //Whether the window is windowed or not
            bool windowed;
            //Whether the window is fine
            bool windowOK;

            SDL_Surface * screen;

            int s_width;
            int s_height;
            int s_bpp;

            cMainControler * m_controler;

            friend class cResizeResolver;
            friend class cActivityResolver;
            friend class cExposeResolver;
        public:
            //Constructor
            cWindow(cMainControler *);
            void init(std::string title, int width, int height, int bpp);
            SDL_Surface * get_screen() {return screen;};

            //Turn fullscreen on/off
            void toggle_fullscreen();
            //Check if anything's wrong with the window
            bool error();
    };

    class cResizeResolver : public cResolver
    {
        public:
            bool Call(SDL_Event * );

            cResizeResolver(cWindow * caller):m_caller(caller) {};
        private:
            cWindow * m_caller;
    };

    class cActivityResolver : public cResolver
    {
        public:
            bool Call(SDL_Event *);

            cActivityResolver(cWindow * caller):m_caller(caller) {};
        private:
            cWindow * m_caller;
    };

    class cExposeResolver : public cResolver
    {
        public:
            bool Call(SDL_Event *);

            cExposeResolver(cWindow * caller):m_caller(caller) {};
        private:
            cWindow * m_caller;
    };
};

#endif // CWINDOW_H_INCLUDED
