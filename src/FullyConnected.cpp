#include "FullyConnected.h"

FullyConnected::FullyConnected(int nodeCount, Layer *priorLayer) :
	nodeCount(nodeCount),
	Layer(priorLayer) {
	outputVolume = new Volume(nodeCount, 1, 1);
	errVsOutput = new Volume(nodeCount, 1, 1);
	weights = new Volume4d(inputVolume->width, inputVolume->height, inputVolume->depth, nodeCount);
	float stdev = 4 * sqrt(6.0f / (((float)priorLayer->outputVolume->width * (float)priorLayer->outputVolume->height * (float)priorLayer->outputVolume->depth) + (float)nodeCount));
	weights->initRandom(0, stdev);
	biases = new Volume(nodeCount, 1, 1);
	biases->initialize(0);
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
		outputVolume->add(i, 0, 0, biases->get(i, 0, 0));
	}
}

void FullyConnected::feedBackward() {
	errVsInput->initialize();
	for (int i = 0; i < nodeCount; i++) {
		for (int z = 0; z < inputVolume->depth; z++) {
			for (int y = 0; y < inputVolume->height; y++) {
				for (int x = 0; x < inputVolume->width; x++) {
					errVsInput->add(x, y, z, errVsOutput->get(i, 0, 0) * weights->get(x, y, z, i));
					// if (i == 5
					// 	and x == 10
					// 	and y == 10
					// 	and inputVolume->get(x, y, z) > 0) {
					// 	cout << "@@@@@@@@@@@@@@@@" << endl;
					// 	cout << "WEIGHT: " << weights->get(x, y, z, i) << endl;
					// 	cout << "ERR OUTPUT: " << errVsOutput->get(i, 0, 0) << endl;
					// 	cout << "INPUT: " << inputVolume->get(x, y, z) << endl;
					// 	cout << "OUTPUT: " << outputVolume->get(i, 0, 0) << endl;
					// }
					weights->add(x, y, z, i, errVsOutput->get(i, 0, 0) * inputVolume->get(x, y, z) * -__LEARNING_RATE);
					// if (i == 5
					// 	and x == 10
					// 	and y == 10
					// 	and inputVolume->get(x, y, z) > 0) {
					// 	cout << "AFTER: " << weights->get(x, y, z, i) << endl;
					// }
				}
			}
		}
		biases->add(i, 0, 0, -__LEARNING_RATE * errVsOutput->get(i, 0, 0));
	}
}