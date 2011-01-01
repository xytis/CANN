#include "../include/cMenuState.h"

namespace Interface
{
    cMenuState * cMenuState::m_instance = NULL;

    cMenuState * cMenuState::
    instance()
    {
        if (!m_instance)
            throw exception::InstanceException("Instance NOT initialised!");
        return m_instance;
    }

    cMenuState* cMenuState::
    create(cMainControler * controler)
    {
        if (!m_instance)
            m_instance = new cMenuState(controler);
        return instance();
    }

    cMenuState::
    cMenuState(cMainControler * controler):
    cProgramState(controler)
    {
    }

    void cMenuState::
    init()
    {
        background = m_controler->resources.get_image("background.png");
    }

    void cMenuState::
    resume()
    {

    }

    void cMenuState::
    process()
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    /*
                    if(event.key.keysym.sym == SDLK_DOWN)
                        move_down();
                    else if(event.key.keysym.sym == SDLK_UP)
                        move_up();
                    else if(event.key.keysym.sym == SDLK_RETURN)
                        (*m_active_item)->action();
                    */
                    break;
            }
        }
    }

    void cMenuState::
    draw()
    {
        SDLVideo::apply_surface(background, 0, 0, background->w, background->h, m_controler->screen, 0, 0);

        SDL_Flip(m_controler->screen);
    }

    void cMenuState::
    suspend()
    {

    }

    void cMenuState::
    kill()
    {

    }
};
