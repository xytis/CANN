#ifndef CBRIDGE_H_INCLUDED
#define CBRIDGE_H_INCLUDED

namespace CANN
{
    class cBridge : public cPeripheral
    {
        //WOW, now this one should not be a neural network at all.
        //It should merely let an exchange of signals between cBrain's
        //Even if it apears to be a network of its own.
    };
};

#endif // CBRIDGE_H_INCLUDED
