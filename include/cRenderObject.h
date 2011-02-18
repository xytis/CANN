#ifndef CRENDEROBJECT_H_INCLUDED
#define CRENDEROBJECT_H_INCLUDED

#include "../include/cMainControler.h"

namespace Interface
{
    class cRenderObject
    {
        public:
            virtual void process() = 0;
            void draw()
            {
                SDL_BlitSurface( m_sprite, m_clip[m_state], m_controler->screen, &box );
            };
            SDL_Rect box;

        protected:
            cRenderObject(cMainControler * controler):
            m_controler(controler)
            {};
            void load_sprite(std::string filename)
            {
                m_sprite = m_controler->resources.get_image(filename, this);
            };
            void add_clip(std::string state, SDL_Rect * clip)
            {
                m_clip[state] = clip;
            };
            void set_state(std::string state)
            {
                m_state = state;
            };
        private:
            cMainControler * m_controler;
            SDL_Surface * m_sprite;
            std::map<std::string, SDL_Rect *> m_clip;
            std::string m_state;
    };
};

#endif // CRENDEROBJECT_H_INCLUDED
