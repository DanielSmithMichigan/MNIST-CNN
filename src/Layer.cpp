#include "Layer.h"

Layer::Layer (Layer *priorLayer) :
    errVsInput(priorLayer->errVsOutput),
    inputVolume(priorLayer->outputVolume) {
}

Layer::Layer () {}

Layer::~Layer() {

}

void Layer::feedForward() {}
void Layer::feedBackward() {}