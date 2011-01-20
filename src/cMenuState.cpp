#include "../include/cMenuState.h"

namespace Interface
{
    /**
     *  Main menu
     */

    cMainMenu::
    cMainMenu(cMainControler * controler):cMenuState(controler)
    {
        Font menu_font = {"X-Files.ttf", 14};
        m_items.reserve(4);

        SDL_Rect box;
        box.x = 200;
        box.y = 100;
        box.w = 200;
        box.h = 50;

        StartItem* start_item = new StartItem();
        start_item->init("Start", m_controler, menu_font, box);

        box.y += box.h+10;

        PreferencesItem* preferences_item = new PreferencesItem();
        preferences_item->init("Preferences", m_controler, menu_font, box);

        box.y += box.h+10;

        FullscreenItem* fullscreen_item = new FullscreenItem();
        fullscreen_item->init("Fullscreen", m_controler, menu_font, box);

        box.y += box.h+10;

        ExitItem* exit_item = new ExitItem();
        exit_item->init("Exit", m_controler, menu_font, box);


        m_items.push_back(start_item);
        m_items.push_back(preferences_item);
        m_items.push_back(fullscreen_item);
        m_items.push_back(exit_item);
    }

    void cMainMenu::
    init()
    {
        background = m_controler->resources.get_image("background.png");
        resume();
    }

    void cMainMenu::
    process()
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            m_controler->check(&event);
        }
    }

    void cMainMenu::
    kill()
    {
        suspend();
    }

    /**
     *  Preferences menu
     */

    cPreferencesMenu::
    cPreferencesMenu(cMainControler * controler):cMenuState(controler)
    {
        Font menu_font = {"X-Files.ttf", 14};
        m_items.reserve(4);

        SDL_Rect box;
        box.x = 200;
        box.y = 100;
        box.w = 200;
        box.h = 50;

        EmptyItem* empty_item = new EmptyItem();
        empty_item->init("Empty", m_controler, menu_font, box);

        box.y += box.h+10;

        FullscreenItem* fullscreen_item = new FullscreenItem();
        fullscreen_item->init("Fullscreen", m_controler, menu_font, box);

        box.y += box.h+10;

        BackItem* back_item = new BackItem();
        back_item->init("back", m_controler, menu_font, box);


        m_items.push_back(empty_item);
        m_items.push_back(fullscreen_item);
        m_items.push_back(back_item);
    }

    void cPreferencesMenu::
    init()
    {
        background = m_controler->resources.get_image("background.png");
        resume();
    }

    void cPreferencesMenu::
    process()
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            m_controler->check(&event);
        }
    }

    void cPreferencesMenu::
    kill()
    {
        suspend();
    }
/*
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
*/
    /**
     *  Menu State
     */
    cMenuState::
    cMenuState(cMainControler * controler):
    cProgramState(controler),
    background(NULL)
    {

    }

    void cMenuState::
    resume()
    {
        m_active_item = m_items.end();
        m_controler->register_resolver(SDL_KEYDOWN, new cKeyResolver(this));
        m_controler->register_resolver(SDL_MOUSEMOTION, new cMouseResolver(this));
        m_controler->register_resolver(SDL_MOUSEBUTTONDOWN, new cClickResolver(this));
    }

    void cMenuState::
    draw()
    {
        SDLVideo::apply_surface(background, 0, 0, background->w, background->h, m_controler->screen, 0, 0);

        SDL_Surface* menu_surface;
        SDL_Surface* text_surface;
        std::vector<cMenuItem*>::iterator iter;

        for(iter = m_items.begin(); iter != m_items.end(); ++iter)
        {
            if(*iter == *m_active_item)
            {
                menu_surface = (*iter)->get_active_surface();
                text_surface = (*iter)->get_active_text();
            }
            else
            {
                menu_surface = (*iter)->get_inactive_surface();
                text_surface = (*iter)->get_inactive_text();
            }
            SDLVideo::apply_surface(menu_surface, 0, 0, menu_surface->w, menu_surface->h, m_controler->screen, (*iter)->m_box.x, (*iter)->m_box.y);
            SDLVideo::apply_surface(text_surface, 0, 0, text_surface->w, text_surface->h, m_controler->screen,
                                     (*iter)->m_box.x + (menu_surface->w-text_surface->w)/2,
                                     (*iter)->m_box.y + (menu_surface->h-text_surface->h)/2);
        }

        SDL_Flip(m_controler->screen);

    }

    void cMenuState::
    suspend()
    {
        m_controler->release_resolver(SDL_KEYDOWN);
        m_controler->release_resolver(SDL_MOUSEMOTION);
        m_controler->release_resolver(SDL_MOUSEBUTTONDOWN);
    }

    void cMenuState::
    selection_down()
    {
        if(m_active_item == m_items.end())
        {
            m_active_item = m_items.begin();
        }
        else
        {
            m_active_item++;

            if(m_active_item == m_items.end())
            {
                m_active_item = m_items.begin();
            }
        }
    }

    void cMenuState::
    selection_up()
    {
        if(m_active_item == m_items.end())
        {
            m_active_item = m_items.begin();
        }
        else
        {
            m_active_item--;

            if(m_active_item < m_items.begin())
            {
                m_active_item = m_items.end() - 1;
            }
        }
    }

    /**
     *  Menu Item
     */

    void cMenuItem::
    init(std::string text, cMainControler* controler, Font font, SDL_Rect box)
    {
        m_text = std::string(text.begin(), text.end());
        m_controler = controler;
        m_font = controler->resources.get_font(font);

        m_active_color = SDLVideo::make_color(0, 255, 0);
        m_inactive_color = SDLVideo::make_color(0, 0, 0);

        m_active_surface = NULL;
        m_inactive_surface = NULL;

        m_box = box;
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
            m_active_surface = m_controler->resources.get_image("button_active.png");
        }
        return m_active_surface;
    }

    SDL_Surface* cMenuItem::
    get_active_text()
    {
        if(m_active_text == NULL)
        {
            m_active_text = TTF_RenderText_Blended(m_font, m_text.c_str(), m_active_color);
        }
        return m_active_text;
    }

    SDL_Surface* cMenuItem::
    get_inactive_surface()
    {
        if(m_inactive_surface == NULL)
        {
            m_inactive_surface = m_controler->resources.get_image("button_idle.png");
        }
        return m_inactive_surface;
    }

    SDL_Surface* cMenuItem::
    get_inactive_text()
    {
        if(m_inactive_text == NULL)
        {
            m_inactive_text = TTF_RenderText_Blended(m_font, m_text.c_str(), m_inactive_color);
        }
        return m_inactive_text;
    }

    /**
     *  Buttons
     */

    void ExitItem::
    action()
    {
        SDL_Event e;
        e.type = SDL_QUIT;
        SDL_PushEvent(&e);
    }

    void FullscreenItem::
    action()
    {
        m_controler->m_window->toggle_fullscreen();
    }

    void PreferencesItem::
    action()
    {
        m_controler->push(new cPreferencesMenu(m_controler));
    }

    void BackItem::
    action()
    {
        m_controler->pop();
    }

    void StartItem::
    action()
    {
        m_controler->push(new cRenderState(m_controler));
    }

    void EmptyItem::
    action()
    {
        std::cout << " pressed: " << this->m_text;
    }

    /**
     *  Handlers
     */

    bool cMenuState::cKeyResolver::
    Call(SDL_Event * event)
    {
        if(event->key.keysym.sym == SDLK_DOWN)
        {
            m_caller->selection_down();
            return true;
            //std::cout << "Down" << std::endl;
        }
        else if(event->key.keysym.sym == SDLK_UP)
        {
            m_caller->selection_up();
            //std::cout << "Up" << std::endl;
            return true;
        }
        else if(event->key.keysym.sym == SDLK_RETURN)
        {
            if (m_caller->m_active_item != m_caller->m_items.end())
                (*m_caller->m_active_item)->action();
            return true;
        }
        return false;
    }

    bool cMenuState::cMouseResolver::
    Call(SDL_Event * event)
    {
        //Get the mouse offsets
        int x = event->motion.x;
        int y = event->motion.y;

        std::vector<cMenuItem*>::iterator iter;
        for(iter = m_caller->m_items.begin(); iter != m_caller->m_items.end(); ++iter)
        {
            if( ( x > (*iter)->m_box.x ) && ( x < (*iter)->m_box.x + (*iter)->m_box.w ) && ( y > (*iter)->m_box.y ) && ( y < (*iter)->m_box.y + (*iter)->m_box.h ) )
            {
                m_caller->m_active_item = iter;
                return true;
            }
        }
        m_caller->m_active_item = m_caller->m_items.end();
        return true;
    }

    bool cMenuState::cClickResolver::
    Call(SDL_Event * event)
    {
        //If there was a click =]
        if( event->button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            int x = event->motion.x;
            int y = event->motion.y;

            std::vector<cMenuItem*>::iterator iter;
            for(iter = m_caller->m_items.begin(); iter != m_caller->m_items.end(); ++iter)
            {
                if( ( x > (*iter)->m_box.x ) && ( x < (*iter)->m_box.x + (*iter)->m_box.w ) && ( y > (*iter)->m_box.y ) && ( y < (*iter)->m_box.y + (*iter)->m_box.h ) )
                {
                    //If it was on Button =]
                    (*iter)->action();
                    return true;
                }
            }
        }
        return false;
    }
};
