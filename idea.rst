=========
IDEA
=========

This is the rough idea of cyclic artificial neural network.

As in standard models of ANN's the structure is straight: input layer->hidden layers->output layer. As this model offers a fair amount of learning capabilities, it lacks 'runtime memory', as the layers have no knowledge of previous state.

This model dwells on an idea that neurons should form cyclic links within collections. As number of virtual neurons is comparatively small, self links are introduced.

Input is introduced to a finite set of neurons I. The signals cycle the network N for a known amount of time. Afterwards output is taken from another finite set of neurons O.

Here I,O in N, while I != O, with possibility of overlapping neurons.

Network is fully described by set of threshold values T, and matrix of connection penalties P.

----

| For example, a network of four neurons:
|
| A        B
|
|
| C        D
|
| The input is given to A and C. Then sending step is executed. Signals are passed to all neurons (including themselves). When the signals are accumulated, neurons might become 'active', if a threshold value is exceeded. Only active neurons send signals during next sending step.
