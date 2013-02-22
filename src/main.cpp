
#include "Interface/cMainControler.hpp"
#include "Interface/cMenuState.hpp"

#include <iostream>
#include <fstream>
#include <vector>

int main ( int argc, char** argv )
{
    Interface::cMainControler * program = Interface::cMainControler::create();
    
    program->init("CANN", 640, 480, 32);
    
    Interface::cMenuState * menu = new Interface::cMainMenu(program);
    //Interface::cRenderState * render = Interface::cRenderState::create(program);
    program->push(menu);
    //program->push(render);
    
    program->run();
    program->clean_up();
}

