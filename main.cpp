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
#include <vector>

#include "include/cBrain.h"
#include "include/cNeuron.h"
#include "include/cRandomPool.h"
#include "include/cSpotCreature.h"

/*
#include "include/cBrain.h"
#include "include/cSensor.h"
#include "include/cMover.h"
#include "include/cNeuron.h"
#include "include/cRandomPool.h"
*/
/*
#include "include/cMainControler.h"
#include "include/cMenuState.h"
#include "include/cRenderState.h"

#include "include/cCreature.h"
*/
void decrease(double & number, double amount)
{
    number -= amount;
    if (number < 0.0)
    {
        number = 0.0;
    }
}

int evaluate(CANN::cSpotCreature & spotty, CANN::cRandomPool & pool)
{
    double food;
    int score = 0;
    food = pool.get_random_in(0.0, 1.0);
    
    for (int i = 0; i < 100; i++)
    {
        spotty.input(food);
        spotty.think();
        if (spotty.output() > 0.5)
        {
            //Good to move away from scarse location
            if (food < 0.5)
            {
                score++;
            }
            else
            {
                score--;
            }
            food = pool.get_random_in(0.0, 1.0);
        }
        else
        {
            //Bad to stay at scarse location
            if (food < 0.5)
            {
                score--;
            }
            else
            {
                score++;
            }
        }
        decrease(food, 0.1);
    }
    
    return score;
}

std::vector<CANN::cSpotCreature> initial_generation(CANN::cRandomPool & pool)
{
    std::vector<CANN::cSpotCreature> spots;
    for (int i = 0; i < 100; i++)
    {
        CANN::cSpotCreature spotty(pool, 5, pool.generate_ID(0));
        spots.push_back(spotty);
    }
    return spots;
}

std::vector<CANN::cSpotCreature> create_generation(CANN::cSpotCreature & father, CANN::cRandomPool & pool)
{
    std::vector<CANN::cSpotCreature> spots;
    for (int i = 0; i < 100; i++)
    {
        CANN::cSpotCreature spotty(father, pool);
        spots.push_back(spotty);
    }
    return spots;
}

int main ( int argc, char** argv )
{
    CANN::cRandomPool random(1);

    std::vector<CANN::cSpotCreature> spots;
    spots = initial_generation(random);

    CANN::cSpotCreature best(random, 4, 0);

    for (int gen = 0; gen < 1000; gen++)
    {
        int best_score = -101;
        int best_spot = -1;
        double sum = 0;
        for (int i = 0; i< 100; i++)
        {
            int score = evaluate(spots[i], random);
            sum += score;
            if (best_score < score)
            {
                best_score = score;
                best_spot = i;
            }
        }
        std::cout << "Generation: " << gen << " Best score: " << best_score << " Average: " << sum/100 << std::endl;
        best = spots[best_spot];
        spots = create_generation(best, random);
    }

    std::ofstream fout("best.gen");
    best.genome(fout);

    return 0;
}
/*
    CANN::cRandomPool random(1);
    CANN::cBrain brainiac(random, 10, "MAIN");
    CANN::cNeuron * input, * output;

    input = brainiac.at(1);
    output = brainiac.at(2);

    for (int i = 0; i < 100; i++)
    {
        if (i < 20)
            input->get(i%3);
        brainiac.send();
        brainiac.flip();
        std::cout << output->let() << std::endl;
    }

    return 0;
}
*/
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
/*
    Interface::cMainControler * program = Interface::cMainControler::create();
    program->init("hello", 640, 480, 32);
    Interface::cMenuState * menu = new Interface::cMainMenu(program);
    //Interface::cRenderState * render = Interface::cRenderState::create(program);
    program->push(menu);
    //program->push(render);
    program->run();
    program->clean_up();
*/
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
    
    return 0;
}
*/
