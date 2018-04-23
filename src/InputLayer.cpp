#include "InputLayer.h"

InputLayer::InputLayer(int outputWidth, int outputHeight) :
    Layer() {
	outputVolume = new Volume(outputWidth, outputHeight, 1);
}

InputLayer::~InputLayer() {

}

void InputLayer::feedForward() {
	for (int y = 0; y < outputVolume->height; y++) {
		for (int x = 0; x < outputVolume->width; x++) {
			outputVolume->set(x, y, 0, pixelStream->get());
		}
	}
}

void InputLayer::feedBackward() {
    
}