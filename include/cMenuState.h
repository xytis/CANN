#ifndef CMENUSTATE_H_INCLUDED
#define CMENUSTATE_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <vector>

#include "../include/sdl_video.h"

#include "../include/cMainControler.h"

namespace Interface
{

    class cMenuItem
    {
        public:
            virtual ~cMenuItem();

            void init(std::string text, cMainControler* controler, Font font, SDL_Rect box);
            virtual void action() = 0;
            SDL_Surface* get_active_surface();
            SDL_Surface* get_inactive_surface();
            SDL_Rect     m_box;
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

    class FullscreenItem : public cMenuItem
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
            //here goes friend cResolver classes.

            friend class cKeyResolver;
            friend class cMouseResolver;
            friend class cClickResolver;

        protected:
            cMenuState(cMainControler * controler);
            std::vector<cMenuItem*>::iterator m_active_item;
            std::vector<cMenuItem*> m_items;
            SDL_Surface* background;
            void selection_down();
            void selection_up();
        private:


            static cMenuState * m_instance;

            //Never to touch
            cMenuState();
            ~cMenuState() {};
    };

    class cKeyResolver : public cResolver
    {
        public:
            bool Call(SDL_Event * e);

            cKeyResolver(cMenuState * caller):m_caller(caller) {};
        private:
            cMenuState * m_caller;
    };

    class cMouseResolver : public cResolver
    {
        public:
            bool Call(SDL_Event * e);

            cMouseResolver(cMenuState * caller):m_caller(caller) {};
        private:
            cMenuState * m_caller;
    };

    class cClickResolver : public cResolver
    {
        public:
            bool Call(SDL_Event * e);

            cClickResolver(cMenuState * caller):m_caller(caller) {};
        private:
            cMenuState * m_caller;
    };
};

#endif // CMENUSTATE_H_INCLUDED
