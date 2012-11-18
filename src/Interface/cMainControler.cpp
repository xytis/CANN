#include "cMainControler.hpp"

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

        m_window = new cWindow(this);
        m_window->init(title, width, height, bpp);

        screen = m_window->get_screen();

        if(TTF_Init() == -1)
        {
            throw exception::SDLexception(TTF_GetError(), exception::SDLexception::TTF);
        }

        running = true;
        register_resolver(SDL_QUIT, new cExitResolver(this));
    }

    void cMainControler::
    resume()
    {
        states.top()->resume();
        //? Ką daryti kad vėl parodytų vaizdą?
    }

    void cMainControler::
    run()
    {
        const int FPS = 25;
        const int SKIP_TICKS = 1000 / FPS;

        Uint32 next_tick = SDL_GetTicks();
        int sleep_time;


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
    suspend()
    {
        states.top()->suspend();
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

        resources.clean_up();
        m_event_resolvers.clear();
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
    register_resolver(SDL_EventType key, cResolver * resolver)
    {
        m_event_resolvers[key] = resolver;
    }

    void cMainControler::
    release_resolver(SDL_EventType key)
    {
        m_event_resolvers.erase(key);
    }

    void cMainControler::
    check(SDL_Event * e)
    {
        std::map<Uint8, cResolver *>::iterator iter;
        iter = m_event_resolvers.find(e->type);
        if (iter != m_event_resolvers.end())
        {
            std::cout << "Event : " << int(e->type);
            if (iter->second->Call(e))
                std::cout << " handled" << std::endl;
            else
                std::cout << " mishandled" << std::endl;
        }
        else
        {
            std::cout << "##Unhandled event: " << int(e->type) << std::endl;
        }
    }

    void cMainControler::
    wait_for(SDL_EventType type)
    {
        SDL_Event event;
        while (event.type != type)
        {
            std::cout << "Waiting..." << std::endl;
            SDL_WaitEvent(&event);
            check(&event);
        }
    }

    bool cExitResolver::
    Call(SDL_Event * event)
    {
        m_caller->kill();
        return true;
    }
};
