#include "../include/cThread.h"

cThread::cThread()
{

}

int cThread::Start(void * arg)
{
   Arg(arg); // store user data
   int code = pthread_create(& ThreadId_, NULL, cThread::EntryPoint, this);
   return code;
}

int cThread::Run(void * arg)
{
   Setup();
   Execute( arg );
}

/*static */
void * cThread::EntryPoint(void * pthis)
{
   cThread * pt = (cThread*)pthis;
   pt->Run( pt->Arg() );
}

void cThread::Setup()
{
        // Do any setup here
}
