#ifndef CRENDERSTATE_H_INCLUDED
#define CRENDERSTATE_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "../include/sdl_video.h"

#include "../include/cMainControler.h"

namespace Interface
{
    class cRenderState : public cProgramState
    {
        public:
            void init();
            void resume();
            void process();
            void draw();
            void suspend();
            void kill();

            static cRenderState * create(cMainControler *);
            static cRenderState * instance();
        protected:
            cRenderState(cMainControler * controler);
        private:
            static cRenderState * m_instance;
            SDL_Surface* background;

            //Never to touch
            cRenderState();
    };
};

#endif // CRENDERSTATE_H_INCLUDED
