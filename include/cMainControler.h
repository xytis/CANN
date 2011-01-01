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

#include "../include/exception.h"
#include "../include/cProgramState.h"
#include "../include/cResourceManager.h"

namespace Interface
{
    class cResourceManager;

    class cMainControler
    {
        public:
            static  cMainControler * instance();

            static  cMainControler * create();

            void init(std::string title, int width, int height, int bpp);

            void    run();
            void    kill();
            void    clean_up();

            void    change_state(cProgramState* state);
            void    push(cProgramState* state);
            void    pop();
            cProgramState* get_state();

            SDL_Surface     * screen;
            cResourceManager resources;

        private:
            friend  class cProgramState;

            static  cMainControler  * m_instance;



            cMainControler():resources("resources/") {};
            ~cMainControler() {};

            std::stack<cProgramState*> states;
            bool running;
    };
};
#endif // CMAINCONTROLER_H_INCLUDED
