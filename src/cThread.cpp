#include "../include/cThread.h"

cThread::
cThread()
{

}

int cThread::
Start(void * arg)
{
    Arg(arg); // store user data
    Thread_ = SDL_CreateThread(cThread::EntryPoint, this);
    //int code = pthread_create(& ThreadId_, NULL, cThread::EntryPoint, this);
    //return code;
    if ( Thread_ == NULL )
    {
        throw (SDL_ThreadCreateException(SDL_GetError()));
    }
    return 0;
}

int cThread::
Wait()
{
    int status;
    SDL_WaitThread(Thread_, &status);
    return status;
}

void cThread::
Kill()
{
    SDL_KillThread(Thread_);
    Thread_ = NULL;
}

int cThread::
Run(void * arg)
{
   Setup();
   Execute( arg );
}

/*static */
int cThread::
EntryPoint(void * pthis)
{
   cThread * pt = (cThread*)pthis;
   pt->Run( pt->Arg() );
}

void cThread::
Setup()
{
        // Do any setup here
}
