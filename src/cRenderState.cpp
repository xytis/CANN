#include "../include/cRenderState.h"

namespace Interface
{
    cRenderState * cRenderState::m_instance = NULL;

    cRenderState * cRenderState::
    instance()
    {
        if (!m_instance)
            throw exception::InstanceException("Instance NOT initialised!");
        return m_instance;
    }

    cRenderState* cRenderState::
    create(cMainControler * controler)
    {
        if (!m_instance)
            m_instance = new cRenderState(controler);
        return instance();
    }

    cRenderState::
    cRenderState(cMainControler * controler):
    cProgramState(controler)
    {
    }

    void cRenderState::
    init()
    {
        background = m_controler->resources.get_image("background.png");
    }

    void cRenderState::
    resume()
    {

    }

    void cRenderState::
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

    void cRenderState::
    draw()
    {
        SDLVideo::apply_surface(background, 0, 0, background->w, background->h, m_controler->screen, 0, 0);

        SDL_Flip(m_controler->screen);
    }

    void cRenderState::
    suspend()
    {

    }

    void cRenderState::
    kill()
    {

    }
};
