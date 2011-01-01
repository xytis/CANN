#ifndef CMENUSTATE_H_INCLUDED
#define CMENUSTATE_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "../include/sdl_video.h"

#include "../include/cMainControler.h"

namespace Interface
{
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
    };
};

#endif // CMENUSTATE_H_INCLUDED
