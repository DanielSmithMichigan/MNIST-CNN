#pragma once
#include <cmath>
#include "Constants.h"
#include "Volume.h"
using namespace std;

class Layer{
    private:
    protected:
    public:
        Layer(Layer *priorLayer);
        Layer();
        ~Layer();
        Volume *errVsInput;
        Volume *errVsOutput;
        Volume *outputVolume;
        Volume *inputVolume;
        virtual void feedForward();
        virtual void feedBackward();
};