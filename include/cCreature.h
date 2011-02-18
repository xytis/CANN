#ifndef CCREATURE_H_INCLUDED
#define CCREATURE_H_INCLUDED

#include "../include/cRenderObject.h"
#include "../include/cMainControler.h"

#include "../include/cBrain.h"
#include "../include/cMover.h"
#include "../include/cSensor.h"
#include "../include/cBridge.h"

#include <vector>
#include <queue>

namespace CANN
{
    class cCreature : public Interface::cRenderObject
    {
        private:
            //The parts of an animal. Doah.
            cBrain  * brain;
            cMover  * mover;
            std::vector<cPeripheral *> sensors_n_bridges;
            std::queue<cActivity *> todo;
        public:
            cCreature(Interface::cMainControler *);
            void process();
            //Should have all the methods as render object here
    };
};

#endif // CCREATURE_H_INCLUDED
