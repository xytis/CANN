#include "../include/cMainControler.h"

namespace Interface
{
    cMainControler* cMainControler::m_instance = NULL;

    cMainControler* cMainControler::
    instance()
    {
        if (!m_instance)
            throw exception::InstanceException("Instance NOT initialised!");
        return m_instance;
    }

    cMainControler* cMainControler::
    create()
    {
        if (!m_instance)
            m_instance = new cMainControler();
        return instance();
    }

    void cMainControler::
    init(std::string title, int width, int height, int bpp)
    {
        if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            throw exception::SDLexception(SDL_GetError(), exception::SDLexception::INIT);
        }

        SDL_WM_SetCaption(title.c_str(), NULL);

        screen = SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE);

        if(screen == NULL)
        {
            throw exception::SDLexception(SDL_GetError(), exception::SDLexception::SURFACE);
        }

        if(TTF_Init() == -1)
        {
            throw exception::SDLexception(TTF_GetError(), exception::SDLexception::TTF);
        }

        running = true;
    }

    void cMainControler::
    run()
    {
        const int FPS = 25;
        const int SKIP_TICKS = 1000 / FPS;

        Uint32 next_tick = SDL_GetTicks();
        Uint32 sleep_time;

        SDL_Event* events;
        int num_events;

        while(running)
        {
            SDL_PumpEvents();

            try
            {
                states.top()->process();
                states.top()->draw();
            }
            catch (exception::kill_event &e)
            {
                running=false;
                continue;
            }
            next_tick += SKIP_TICKS;
            sleep_time = next_tick - SDL_GetTicks();

            if(sleep_time > 0)
            {
                SDL_Delay(sleep_time);
            }
        }
    }

    void cMainControler::
    kill()
    {
        throw exception::kill_event();
    }

    void cMainControler::
    clean_up()
    {
        while(!states.empty())
        {
            states.top()->kill();
            states.pop();
        }
        SDL_FreeSurface(screen);

        //resources.clean_up();
        SDL_Quit();

    }

    void cMainControler::
    change_state(cProgramState* state)
    {
        if(!states.empty())
        {
            states.top()->kill();
            states.pop();
        }

        states.push(state);
        states.top()->init();
    }

    void cMainControler::
    push(cProgramState* state)
    {
        if(!states.empty())
        {
            states.top()->suspend();
        }

        states.push(state);
        states.top()->init();
    }

    void cMainControler::
    pop()
    {
        if(states.size() > 1)
        {
            states.top()->kill();
            states.pop();
            states.top()->resume();
        }
        else
        {
            kill();
        }
    }

    cProgramState* cMainControler::
    get_state()
    {
        return states.top();
    }

    void cMainControler::
    checkEvent(SDL_Event * E)
    {
        if (E->type==SDL_QUIT)
            throw exception::kill_event();
    }
};
