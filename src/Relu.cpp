#include "Relu.h"

Relu::Relu(Volume* inputVolume) : inputVolume(inputVolume) {
	outputVolume = new Volume(inputVolume->width, inputVolume->height, inputVolume->depth);
}

Relu::~Relu() {

}

void Relu::feedForward() {
	for (int z = 0; z < inputVolume->depth; z++) {
		for (int y = 0; y < inputVolume->width; y++) {
			for (int x = 0; x < inputVolume->height; x++) {
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
		for (int y = 0; y < inputVolume->width; y++) {
			for (int x = 0; x < inputVolume->height; x++) {
				float val = inputVolume->get(x, y, z);
				if (val < 0) {
					val = 0;
				}
				outputVolume->set(x, y, z, val);
			}
		}
	}
}