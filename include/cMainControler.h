#ifndef CMAINCONTROLER_H_INCLUDED
#define CMAINCONTROLER_H_INCLUDED

//Single instance class

#ifdef __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#else
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#endif

#include <string>
#include <stack>
#include <map>

#include "../include/exception.h"
#include "../include/cProgramState.h"
#include "../include/cResourceManager.h"
#include "../include/cWindow.h"
#include "../include/cResolver.h"

namespace Interface
{
    class cResourceManager;
    class cWindow;

    class cMainControler
    {
        public:
            static  cMainControler * instance();

            static  cMainControler * create();

            void    init(std::string title, int width, int height, int bpp);
            void    resume();
            void    run();
            void    suspend();
            void    kill();
            void    clean_up();

            void    change_state(cProgramState* state);
            void    push(cProgramState* state);
            void    pop();
            cProgramState* get_state();


            void    register_resolver(SDL_EventType, cResolver *);
            void    release_resolver(SDL_EventType);
            void    check (SDL_Event*);
            void    wait_for(SDL_EventType);

            SDL_Surface     * screen;
            cWindow         * m_window;
            cResourceManager resources;

            friend class cExitResolver;


        private:
            friend  class cProgramState;

            static  cMainControler  * m_instance;



            std::map<Uint8, cResolver *> m_event_resolvers;

            cMainControler():resources("resources/") {};
            ~cMainControler() {};

            std::stack<cProgramState*> states;
            bool running;
    };

    class cExitResolver : public cResolver
    {
        public:
            bool Call(SDL_Event *);

            cExitResolver(cMainControler * caller):m_caller(caller) {};
        private:
            cMainControler * m_caller;
    };

};
#endif // CMAINCONTROLER_H_INCLUDED
