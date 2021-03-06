#include "Relu.h"

Relu::Relu(Layer *priorLayer) : Layer(priorLayer) {
	outputVolume = new Volume(inputVolume->width, inputVolume->height, inputVolume->depth);
	errVsOutput = new Volume(inputVolume->width, inputVolume->height, inputVolume->depth);
}

Relu::~Relu() {

}

void Relu::feedForward() {
	for (int z = 0; z < inputVolume->depth; z++) {
		for (int y = 0; y < inputVolume->height; y++) {
			for (int x = 0; x < inputVolume->width; x++) {
				float val = inputVolume->get(x, y, z);
				if (val < 0) {
					val *= .01;
				}
				outputVolume->set(x, y, z, val);
			}
		}
	}
}

void Relu::feedBackward() {
	for (int z = 0; z < inputVolume->depth; z++) {
		for (int y = 0; y < inputVolume->height; y++) {
			for (int x = 0; x < inputVolume->width; x++) {
				float inputVal = inputVolume->get(x, y, z);
				float backpropVal;
				if (inputVal < 0) {
					backpropVal = -0.01;
				} else {
					backpropVal = 1;
				}
				errVsInput->set(x, y, z, backpropVal * errVsOutput->get(x, y, z));
			}
		}
	}
}