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

        m_objects.push_back(new cRedBlock(m_controler));

        resume();
    }

    void cRenderState::
    resume()
    {
        m_controler->register_resolver(SDL_KEYDOWN, new cKeyResolver(this));
        m_controler->register_resolver(SDL_MOUSEMOTION, new cMouseResolver(this));
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

        background_thread->Wait();
        foreground_thread->Wait();
    }

    void cRenderState::
    draw()
    {
        SDLVideo::apply_surface(background, 0, 0, background->w, background->h, m_controler->screen, 0, 0);

        for (int i = 0; i < m_objects.size(); i++)
            m_objects[i]->draw();

        SDL_Flip(m_controler->screen);
    }

    void cRenderState::
    suspend()
    {
        delete background_thread;
        delete foreground_thread;
        m_controler->release_resolver(SDL_KEYDOWN);
        m_controler->release_resolver(SDL_MOUSEMOTION);
    }

    void cRenderState::
    kill()
    {
        suspend();
    }

    cRedBlock::
    cRedBlock(cMainControler * controler):
    cRenderObject(controler)
    {
        load_sprite("red_cube.png");
        box.h = 50;
        box.w = 50;
        SDL_Rect * n_clip = new SDL_Rect;
        n_clip->x = 0;
        n_clip->y = 0;
        n_clip->h = box.h;
        n_clip->w = box.w;
        add_clip(std::string("default"),n_clip);
        set_state("default");
    }

    void cRedBlock::
    process()
    {

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
        while (SDL_PollEvent(&event))
        {
            m_controler->check(&event);
        }
        /* Makes bad stuff happen. Something is not ok, when one thread is on waiting mode,
            and other kills it...
        //If after main work is done, other thread is not done yet
        //Continue waiting.
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
        */
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

    bool cMouseResolver::
    Call(SDL_Event * event)
    {
        m_caller->m_objects[0]->box.x = event->motion.x;
        m_caller->m_objects[0]->box.y = event->motion.y;
        return true;
    }
};
