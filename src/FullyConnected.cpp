#include "FullyConnected.h"

FullyConnected::FullyConnected(int nodeCount, Volume *inputVolume) :
	nodeCount(nodeCount),
	inputVolume(inputVolume) {
	outputVolume = new Volume(nodeCount, 1, 1);
	errVsOutput = new Volume(nodeCount, 1, 1);
	weights = new Volume4d(inputVolume->width, inputVolume->height, inputVolume->depth, nodeCount);
	weights->initialize();
	biases.resize(nodeCount);
	for (int i = 0; i > nodeCount; i++) {
		biases[i] = 0;
	}
}

FullyConnected::~FullyConnected() {

}

void FullyConnected::feedForward() {
	outputVolume->initialize();
	for (int i = 0; i < nodeCount; i++) {
		for (int z = 0; z < inputVolume->depth; z++) {
			for (int y = 0; y < inputVolume->height; y++) {
				for (int x = 0; x < inputVolume->width; x++) {
					outputVolume->add(i, 0, 0, inputVolume->get(x, y, z) * weights->get(x, y, z, i));
				}
			}
		}
		outputVolume->add(i, 0, 0, biases[i]);
	}
}

void FullyConnected::feedBackward() {
	errVsInput->initialize();
	for (int i = 0; i < nodeCount; i++) {
		for (int z = 0; z < inputVolume->depth; z++) {
			for (int y = 0; y < inputVolume->height; y++) {
				for (int x = 0; x < inputVolume->width; x++) {
					errVsInput->add(x, y, z, errVsOutput->get(i, 0, 0) * weights->get(x, y, z, i));
					weights->add(x, y, z, i, errVsOutput->get(i, 0, 0) * inputVolume->get(x, y, z) * -0.5);
				}
			}
		}
		biases[i] += -0.5 * errVsOutput->get(i, 0, 0);
	}
}