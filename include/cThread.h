#ifndef CTHREAD_H_INCLUDED
#define CTHREAD_H_INCLUDED

#include <pthread.h>

#ifndef THREADID
#define THREADID pthread_t
#endif

class cThread
{
   public:
      cThread();
      int Start(void * arg);
   protected:
      int Run(void * arg);
      static void * EntryPoint(void*);
      void Setup();
      virtual void Execute(void*) = 0;
      void * Arg() const {return Arg_;}
      void Arg(void* a){Arg_ = a;}
   private:
      THREADID ThreadId_;
      void * Arg_;

};
#endif // CTHREAD_H_INCLUDED
