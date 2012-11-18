#ifndef CMENUSTATE_H_INCLUDED
#define CMENUSTATE_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <vector>

#include "Utils/sdl_video.hpp"

#include "cMainControler.hpp"
#include "cRenderState.hpp"

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
            SDL_Surface* get_active_text();
            SDL_Surface* get_inactive_text();
            SDL_Rect     m_box;
        protected:
            cMainControler* m_controler;
            std::string m_text;
        private:
            TTF_Font* m_font;
            SDL_Surface* m_active_surface;
            SDL_Surface* m_inactive_surface;
            SDL_Surface* m_active_text;
            SDL_Surface* m_inactive_text;
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

    class PreferencesItem : public cMenuItem
    {
        public:
            void action();
    };

    class BackItem : public cMenuItem
    {
        public:
            void action();
    };

    class StartItem : public cMenuItem
    {
        public:
            void action();
    };

    class EmptyItem : public cMenuItem
    {
        public:
            void action();
    };

    class cMenuState : public cProgramState
    {
        public:
            virtual void init() = 0;
            void resume();
            virtual void process() = 0;
            void draw();
            void suspend();
            virtual void kill() = 0;

            //static cMenuState * create(cMainControler *);
            //static cMenuState * instance();
            //here goes friend cResolver classes.

            friend class cKeyResolver;
            friend class cMouseResolver;
            friend class cClickResolver;

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

        protected:
            cMenuState(cMainControler * controler);
            std::vector<cMenuItem*>::iterator m_active_item;
            std::vector<cMenuItem*> m_items;
            SDL_Surface* background;
            void selection_down();
            void selection_up();
        private:
            //static cMenuState * m_instance;

            //Never to touch
            cMenuState();
    };

    class cMainMenu : public cMenuState
    {
        public:
            cMainMenu(cMainControler * controler);
            void init();
            void process();
            void kill();
    };

    class cPreferencesMenu : public cMenuState
    {
        public:
            cPreferencesMenu(cMainControler * controler);
            void init();
            void process();
            void kill();
    };


};

#endif // CMENUSTATE_H_INCLUDED
