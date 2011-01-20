#include "../include/cRenderState.h"

namespace Interface
{
    /*
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
    */

    cRenderState::
    cRenderState(cMainControler * controler):
    cProgramState(controler),
    background_thread(NULL),
    foreground_thread(NULL)
    {
    }

    void cRenderState::
    init()
    {
        background = m_controler->resources.get_image("background.png");
        resume();
    }

    void cRenderState::
    resume()
    {
        m_controler->register_resolver(SDL_KEYDOWN, new cKeyResolver(this));
        background_thread = new cSimulationThread();
        foreground_thread = new cEventThread(m_controler);
    }

    void cRenderState::
    process()
    {
        //Foreground thread runs while background thread sets the flag to true.
        bool end = false;
        background_thread->Start((void *)&end);
        foreground_thread->Start((void *)&end);
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
        delete background_thread;
        delete foreground_thread;
        m_controler->release_resolver(SDL_KEYDOWN);
    }

    void cRenderState::
    kill()
    {
        suspend();
    }

    cSimulationThread::
    cSimulationThread():
    cThread()
    {

    }

    void cSimulationThread::
    Execute(void * arg)
    {
        std::cout << "Background thread" << std::endl;
        SDL_Delay(20);
        *((bool*)arg) = true;
    }

    cEventThread::
    cEventThread(cMainControler * controler):
    cThread(),
    m_controler(controler)
    {

    }

    void cEventThread::
    Execute(void * arg)
    {
        SDL_Event event;
        while (*((bool*)arg)==false)
        {
            if(SDL_PollEvent(&event))
            {
                m_controler->check(&event);
            }
            else
            {
                SDL_Delay(1);
            }
        }
    }

    bool cKeyResolver::
    Call(SDL_Event * event)
    {
        if(event->key.keysym.sym == SDLK_ESCAPE)
        {
            m_caller->m_controler->pop();
            return true;
        }
        else if(event->key.keysym.sym == SDLK_UP)
        {
            return true;
        }
        else if(event->key.keysym.sym == SDLK_RETURN)
        {
            return true;
        }
        return false;
    }
};
