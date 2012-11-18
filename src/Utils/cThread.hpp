#ifndef CTHREAD_H_INCLUDED
#define CTHREAD_H_INCLUDED

#include <SDL/SDL_thread.h>
#include <exception>
#include <string>

class SDL_ThreadCreateException;

class cThread
{
   public:
      cThread();
      int Start(void * arg);
      int Wait();
      void Kill();
   protected:
      int Run(void * arg);
      static int EntryPoint(void*);
      void Setup();
      virtual void Execute(void*) = 0;
      void * Arg() const {return Arg_;}
      void Arg(void* a){Arg_ = a;}
   private:
      SDL_Thread * Thread_;
      void * Arg_;

};

class SDL_ThreadCreateException: public std::exception
{
    private:
        std::string m_reason;
    public:
        SDL_ThreadCreateException(std::string reason) throw()
        {
            m_reason = reason;
        }
        const char* what() const throw()
        {
            return m_reason.c_str();
        }
        ~SDL_ThreadCreateException () throw () {}
};
#endif // CTHREAD_H_INCLUDED
