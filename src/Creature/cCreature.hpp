#ifndef CCREATURE_H_INCLUDED
#define CCREATURE_H_INCLUDED

#include "Interface/cRenderObject.hpp"
#include "Interface/cMainControler.hpp"

#include "Parts/cBrain.hpp"
#include "Parts/cMover.hpp"
#include "Parts/cSensor.hpp"
#include "Parts/cBridge.hpp"

#include <vector>
#include <queue>

namespace Creature
{


    class cCreature : public Interface::cRenderObject
    {
        private:
			friend class cActivity;

            //The parts of an animal. Doah.
            cBrain  * brain;
            cMover  * mover;
            std::vector<cPeripheral *> sensors_n_bridges;
            //std::queue<cActivity *> todo;


        	class cActivity
        	{
				protected:
					cCreature	* owner;
				public:
					virtual void resolve() = 0;
        	};

        public:
            //cCreature(Interface::cMainControler *);
            void process();
            //Should have all the methods as render object here
    };
};

#endif // CCREATURE_H_INCLUDED
