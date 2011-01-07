#ifndef CMENUSTATE_H_INCLUDED
#define CMENUSTATE_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "../include/sdl_video.h"

#include "../include/cMainControler.h"

namespace Interface
{

    class cMenuItem
    {
        public:
            virtual ~cMenuItem();

            void init(std::string text, cMainControler* controler, Font font);
            virtual void action() = 0;
            SDL_Surface* get_active_surface();
            SDL_Surface* get_inactive_surface();
        protected:
            cMainControler* m_controler;
            std::string m_text;
        private:
            TTF_Font* m_font;
            SDL_Surface* m_active_surface;
            SDL_Surface* m_inactive_surface;
            SDL_Color m_active_color;
            SDL_Color m_inactive_color;
    };


    class ExitItem : public cMenuItem
    {
        public:
            void action();
    };

    class cMenuState : public cProgramState
    {
        public:
            void init();
            void resume();
            void process();
            void draw();
            void suspend();
            void kill();

            static cMenuState * create(cMainControler *);
            static cMenuState * instance();
        protected:
            cMenuState(cMainControler * controler);
        private:
            static cMenuState * m_instance;
            SDL_Surface* background;

            //Never to touch
            cMenuState();
            ~cMenuState() {};
    };
};

#endif // CMENUSTATE_H_INCLUDED
