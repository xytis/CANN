#include "cWindow.hpp"

namespace Interface
{
    cWindow::cWindow(cMainControler * controler):m_controler(controler) {};

    void cWindow::
    init(std::string title, int width, int height, int bpp)
    {
        SDL_WM_SetCaption(title.c_str(), NULL);
        screen = SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE | SDL_RESIZABLE);
        s_width = width;
        s_height = height;
        s_bpp = bpp;
        if( screen == NULL )
        {
            windowOK = false;
            throw exception::SDLException(SDL_GetError(), exception::SDLException::SURFACE);
        }

        windowed = true;

        m_controler->register_resolver(SDL_VIDEORESIZE, new cResizeResolver(this));
        m_controler->register_resolver(SDL_ACTIVEEVENT, new cActivityResolver(this));
        m_controler->register_resolver(SDL_VIDEOEXPOSE, new cExposeResolver(this));
    }

    void cWindow::
    toggle_fullscreen()
    {
        //If the screen is windowed
        if( windowed == true )
        {
            //Set the screen to fullscreen
            screen = SDL_SetVideoMode( s_width, s_height, s_bpp, SDL_SWSURFACE | SDL_RESIZABLE | SDL_FULLSCREEN );

            //If there's an error
            if( screen == NULL )
            {
                windowOK = false;
                throw exception::SDLException(SDL_GetError(), exception::SDLException::SURFACE);
            }

            //Set the window state flag
            windowed = false;
        }
        //If the screen is fullscreen
        else if( windowed == false )
        {
            //Window the screen
            screen = SDL_SetVideoMode( s_width, s_height, s_bpp, SDL_SWSURFACE | SDL_RESIZABLE );

            //If there's an error
            if( screen == NULL )
            {
                windowOK = false;
                throw exception::SDLException(SDL_GetError(), exception::SDLException::SURFACE);
            }

            //Set the window state flag
            windowed = true;
        }
    }

    bool cResizeResolver::
    Call(SDL_Event * event)
    {
        m_caller->screen = SDL_SetVideoMode( event->resize.w, event->resize.h, m_caller->s_bpp, SDL_SWSURFACE | SDL_RESIZABLE );
        m_caller->s_width = event->resize.w;
        m_caller->s_height = event->resize.h;

        //If there's an error
        if( m_caller->screen == NULL )
        {
            m_caller->windowOK = false;
            throw exception::SDLException(SDL_GetError(), exception::SDLException::SURFACE);
        }
        return true;
    }

    bool cActivityResolver::
    Call(SDL_Event * event)
    {
        if( event->active.state & SDL_APPACTIVE )
        {
            //If the application is no longer active
            if( event->active.gain == 0 )
            {
                SDL_WM_SetCaption( "Window Event Test: Iconified", NULL );
            }
            else
            {
                SDL_WM_SetCaption( "Window Event Test", NULL );
            }
        }
        //If something happened to the keyboard focus
        else if( event->active.state & SDL_APPINPUTFOCUS )
        {
            //If the application lost keyboard focus
            if( event->active.gain == 0 )
            {
                SDL_WM_SetCaption( "Window Event Test: Keyboard focus lost", NULL );
            }
            else
            {
                SDL_WM_SetCaption( "Window Event Test", NULL );
            }
        }
        //If something happened to the mouse focus
        else if( event->active.state & SDL_APPMOUSEFOCUS )
        {
            //If the application lost mouse focus
            if( event->active.gain == 0 )
            {
                SDL_WM_SetCaption( "Window Event Test: Mouse Focus Lost", NULL );
            }
            else
            {
                SDL_WM_SetCaption( "Window Event Test", NULL );
            }
        }
        return true;
    }

    bool cExposeResolver::
    Call(SDL_Event * event)
    {
        //Update the screen
        if( SDL_Flip( m_caller->screen ) == -1 )
        {
            //If there's an error
            m_caller->windowOK = false;
            throw exception::SDLException(SDL_GetError(), exception::SDLException::SURFACE);
        }
        return true;
    }

};
