#ifndef CCREATURE_H_INCLUDED
#define CCREATURE_H_INCLUDED

#include "../include/cRenderObject.h"

#include "include/cBrain.h"
#include "include/cMover.h"
#include "include/cSensor.h"
#include "include/cBridge.h"

#include <vector>

namespace CANN
{
    class cCreature : public Interface::cRenderObject
    {
        private:
            //The parts of an animal. Doah.
            cBrain  * brain;
            cMover  * mover;
            vector<cPeripheral *> sensors_n_bridges;
            queue<cActivity *> todo;
        public:
            //Should have all the methods as render object here
    };
};

#endif // CCREATURE_H_INCLUDED
