#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL/SDL.h>
#endif

#include <iostream>
#include <fstream>
/*
#include "include/cBrain.h"
#include "include/cSensor.h"
#include "include/cMover.h"
#include "include/cNeuron.h"
#include "include/cRandomPool.h"
*/
#include "include/cMainControler.h"
#include "include/cMenuState.h"
#include "include/cRenderState.h"

int main ( int argc, char** argv )
{
/*
    std::map<unsigned,CANN::cNeuron*> map;
    std::map<unsigned,CANN::cNeuron*> map2;

    CANN::cNeuron * one, * two, *three;

    one = new CANN::cNeuron(1);
    two = new CANN::cNeuron(2);
    three = new CANN::cNeuron(3);

    one->init(0.5, 10);
    two->init(0.5, 10);
    three->init(0.5, 10);

    one->register_to(map);
    two->register_to(map);
    three->register_to(map2);

    one->link(*one, 1);
    one->link(*two, 1);
    two->link(*one, 1);
    two->link(*two, 1);
    three->link(*three, 0.5);

    one->pair(*three);
    three->pair(*one);

    CANN::cRandomPool R;
    one->mutate_links(R);

    std::cout << one->get_genome() << std::endl;
*/
/*
    std::ofstream fout("file.txt");
    CANN::cRandomPool R;
    CANN::cBrain bob(R, 4, "bob");
    bob.genome(std::cout);
    bob.genome(fout);

    fout.close();

    std::ifstream fin("file.txt");
    CANN::cBrain blue(fin);
    blue.genome(std::cout);

    fin.close();

    fout.open("file.txt");

    CANN::cSensor antenna(R, std::vector<unsigned>(3,3), "antenna");
    antenna.genome(std::cout);
    antenna.genome(fout);

    fout.close();
    fin.open("file.txt");
    CANN::cSensor eye(fin);
    eye.genome(std::cout);
*/
/*
    CANN::cRandomPool R;
    CANN::cBrain bob(R, 4, "bob");
    std::vector<unsigned>layout(1,2);
    CANN::cSensor nose(R, layout, "nose");
    CANN::cMover legs(R, layout, "legs");
    std::vector<CANN::cNeuron *> nose_plug;
    nose_plug.push_back(bob.at(0));
    nose_plug.push_back(bob.at(1));
    nose.bind(nose_plug);
    std::vector<CANN::cNeuron *> leg_plug;
    leg_plug.push_back(bob.at(2));
    leg_plug.push_back(bob.at(3));
    legs.bind(leg_plug);
    nose.genome(std::cout);
    legs.genome(std::cout);
    std::cout << legs;

    std::vector<double> IO(2,2);

    for (int i = 0; i < 10; i++)
    {
        std::cout << "exchange" << std::endl;
        nose.exchange(IO);
        std::cout << nose;
        std::cout << bob;
        std::cout << legs;
        std::cout << "send/flip" << std::endl;
        nose.send();
        bob.send();
        legs.send();
        nose.flip();
        bob.flip();
        legs.flip();
        legs.exchange(IO);
        std::cout << nose;
        std::cout << bob;
        std::cout << legs;
        std::cout << IO.at(0) << ' ' << IO.at(1) << std::endl;
    }
*/
    Interface::cMainControler * program = Interface::cMainControler::create();
    program->init("hello", 640, 480, 32);
    Interface::cMenuState * menu = Interface::cMenuState::create(program);
    Interface::cRenderState * render = Interface::cRenderState::create(program);
    program->push(menu);
    program->push(render);
    program->run();
    program->clean_up();

/*
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // load an image
    SDL_Surface* bmp = SDL_LoadBMP("cb.bmp");
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    // centre the bitmap on screen
    SDL_Rect dstrect;
    dstrect.x = (screen->w - bmp->w) / 2;
    dstrect.y = (screen->h - bmp->h) / 2;

    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // draw bitmap
        SDL_BlitSurface(bmp, 0, screen, &dstrect);

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(bmp);

    // all is well ;)
    printf("Exited cleanly\n");
    */
    return 0;
}
