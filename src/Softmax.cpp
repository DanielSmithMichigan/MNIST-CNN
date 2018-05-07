#include "Softmax.h"

Softmax::Softmax(Layer *priorLayer) : 
	Layer(priorLayer) {
	outputVolume = new Volume(inputVolume->width, inputVolume->height, inputVolume->depth);
	errVsOutput = new Volume(inputVolume->width, inputVolume->height, inputVolume->depth);
}

Softmax::~Softmax() {

}

void Softmax::feedForward() {
	float sum = 0;
	for (int x = 0; x < inputVolume->width; x++) {
		for (int y = 0; y < inputVolume->height; y++) {
			for (int z = 0; z < inputVolume->depth; z++) {
				sum += pow(eConstant, inputVolume->get(x, y, z));
			}
		}
	}
	for (int x = 0; x < inputVolume->width; x++) {
		for (int y = 0; y < inputVolume->height; y++) {
			for (int z = 0; z < inputVolume->depth; z++) {
				outputVolume->set(x, y, z, pow(eConstant, inputVolume->get(x, y, z)) / sum);
			}
		}
	}
}

void Softmax::feedBackward() {
	for (int x = 0; x < inputVolume->width; x++) {
		for (int y = 0; y < inputVolume->height; y++) {
			for (int z = 0; z < inputVolume->depth; z++) {
				errVsInput->set(x, y, z, errVsOutput->get(x, y, z));
			}
		}
	}
}