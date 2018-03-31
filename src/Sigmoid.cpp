#include "Sigmoid.h"

Sigmoid::Sigmoid(Volume* inputVolume) : 
	inputVolume(inputVolume) {
	outputVolume = new Volume(inputVolume->width, inputVolume->height, inputVolume->depth);
	errVsOutput = new Volume(inputVolume->width, inputVolume->height, inputVolume->depth);
}

Sigmoid::~Sigmoid() {

}

void Sigmoid::feedForward() {
	for (int x = 0; x < inputVolume->width; x++) {
		for (int y = 0; y < inputVolume->height; y++) {
			for (int z = 0; z < inputVolume->depth; z++) {
				outputVolume->set(x, y, z, 1 / (1 + pow(eConstant, -inputVolume->get(x, y, z))));
			}
		}
	}
}

void Sigmoid::feedBackward() {
	for (int x = 0; x < inputVolume->width; x++) {
		for (int y = 0; y < inputVolume->height; y++) {
			for (int z = 0; z < inputVolume->depth; z++) {
				float outputVal = outputVolume->get(x, y, z);
				errVsInput->set(x, y, z, errVsOutput->get(x, y, z) * outputVal * (1 - outputVal));
			}
		}
	}
}