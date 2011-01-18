#ifndef CPROGRAMSTATE_H_INCLUDED
#define CPROGRAMSTATE_H_INCLUDED

namespace Interface
{
    class cMainControler;

    class cProgramState
    {
        public:
            virtual void init() = 0;
            virtual void resume() = 0;
            //Here user interaction or calculations take place.
            virtual void process() = 0;
            virtual void draw() = 0;
            virtual void suspend() = 0;
            virtual void kill() = 0;
        protected:
            cProgramState(cMainControler * controler):
                m_controler(controler) {};
            cMainControler * m_controler;
    };
};

#endif // CPROGRAMSTATE_H_INCLUDED
