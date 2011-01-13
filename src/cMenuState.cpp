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
        Font menu_font = {"pillbox.ttf", 12};
        m_items.reserve(2);

        ExitItem* exit_item = new ExitItem();
        exit_item->init("Exit", m_controler, menu_font);

        ExitItem* exit_item2 = new ExitItem();
        exit_item2->init("Exit2", m_controler, menu_font);

        m_items.push_back(exit_item);
        m_items.push_back(exit_item2);
    }

    void cMenuState::
    init()
    {
        background = m_controler->resources.get_image("background.png");
        m_active_item = m_items.begin();
    }

    void cMenuState::
    resume()
    {
        m_active_item = m_items.begin();
    }

    void cMenuState::
    process()
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            m_controler->checkEvent(&event);
            switch(event.type)
            {
                case SDL_KEYDOWN:

                    if(event.key.keysym.sym == SDLK_DOWN)
                    {
                        selection_down();
                        //std::cout << "Down" << std::endl;
                    }
                    else if(event.key.keysym.sym == SDLK_UP)
                    {
                        selection_up();
                        //std::cout << "Up" << std::endl;
                    }
                    else if(event.key.keysym.sym == SDLK_RETURN)
                        (*m_active_item)->action();

                    break;
            }
        }
    }

    void cMenuState::
    draw()
    {
        SDLVideo::apply_surface(background, 0, 0, background->w, background->h, m_controler->screen, 0, 0);

        SDL_Surface* menu_surface;
        std::vector<cMenuItem*>::iterator iter;
        int item_position = 0;

        for(iter = m_items.begin(); iter != m_items.end(); ++iter)
        {
            item_position = m_controler->screen->h / 10 * (iter - m_items.begin() + 1);

            if(*iter == *m_active_item)
            {
                menu_surface = (*iter)->get_active_surface();
            }
            else
            {
                menu_surface = (*iter)->get_inactive_surface();
            }

            SDLVideo::apply_surface(menu_surface, 0, 0, menu_surface->w, menu_surface->h, m_controler->screen, 400, item_position);
        }

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

    void cMenuState::
    selection_down()
    {
        m_active_item++;

        if(m_active_item == m_items.end())
        {
            m_active_item = m_items.begin();
        }
    }

    void cMenuState::
    selection_up()
    {
        m_active_item--;

        if(m_active_item < m_items.begin())
        {
            m_active_item = m_items.end() - 1;
        }
    }

    void cMenuItem::
    init(std::string text, cMainControler* controler, Font font)
    {
        m_text = std::string(text.begin(), text.end());
        m_controler = controler;
        m_font = controler->resources.get_font(font);

        m_active_color = SDLVideo::make_color(255, 0, 0);
        m_inactive_color = SDLVideo::make_color(0, 0, 0);

        m_active_surface = NULL;
        m_inactive_surface = NULL;
    }

    cMenuItem::
    ~cMenuItem()
    {
        SDL_FreeSurface(m_active_surface);
        SDL_FreeSurface(m_inactive_surface);
    }

    SDL_Surface* cMenuItem::
    get_active_surface()
    {
        if(m_active_surface == NULL)
        {
            m_active_surface = TTF_RenderText_Blended(m_font, m_text.c_str(), m_active_color);
        }

        return m_active_surface;
    }

    SDL_Surface* cMenuItem::
    get_inactive_surface()
    {
        if(m_inactive_surface == NULL)
        {
            m_inactive_surface = TTF_RenderText_Blended(m_font, m_text.c_str(), m_inactive_color);
        }

        return m_inactive_surface;
    }

    void ExitItem::
    action()
    {
        SDL_Event e;
        e.type = SDL_QUIT;
        SDL_PushEvent(&e);
    }
};
