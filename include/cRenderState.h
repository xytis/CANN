#ifndef CRENDERSTATE_H_INCLUDED
#define CRENDERSTATE_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <vector>

#include "../include/sdl_video.h"

#include "../include/cMainControler.h"
#include "../include/cThread.h"
#include "../include/cRenderObject.h"

namespace Interface
{
    class cSimulationThread;
    class cEventThread;
    class cRedBlock;

    class cRenderState : public cProgramState
    {
        public:
            void init();
            void resume();
            void process();
            void draw();
            void suspend();
            void kill();

            //static cRenderState * create(cMainControler *);
            //static cRenderState * instance();

            friend class cKeyResolver;
            friend class cMouseResolver;
            cRenderState(cMainControler * controler);
        protected:

        private:
            //static cRenderState * m_instance;
            SDL_Surface* background;

            cSimulationThread * background_thread;
            cEventThread * foreground_thread;

            std::vector<cRenderObject *> m_objects;

            //Never to touch
            cRenderState();
    };

    class cRedBlock : public cRenderObject
    {
        public:
            cRedBlock(cMainControler *);
            void process();
    };

    class cSimulationThread : public cThread
    {
        public:
            cSimulationThread();
        private:
            void Execute(void* arg);
    };

    class cEventThread : public cThread
    {
        public:
            cEventThread(cMainControler *);
        private:
            void Execute(void* arg);
            cMainControler * m_controler;
    };

    class cKeyResolver : public cResolver
    {
        public:
            bool Call(SDL_Event * e);

            cKeyResolver(cRenderState * caller):m_caller(caller) {};
        private:
            cRenderState * m_caller;
    };

    class cMouseResolver : public cResolver
    {
        public:
            bool Call(SDL_Event * e);

            cMouseResolver(cRenderState * caller):m_caller(caller) {};
        private:
            cRenderState * m_caller;
    };
};

#endif // CRENDERSTATE_H_INCLUDED
