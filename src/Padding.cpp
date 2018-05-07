#include "Padding.h"

Padding::Padding(int padding, Layer *priorLayer) :
	padding(padding),
	Layer(priorLayer)
{
	outputVolume = new Volume(inputVolume->width + padding + padding, inputVolume->height + padding + padding, 1);
	outputVolume->initialize(0);
	errVsOutput = new Volume(outputVolume->width, outputVolume->height, 1);
}

Padding::~Padding() {

}

void Padding::feedForward() {
	for(int x = 0; x < inputVolume->width; x++) {
		for(int y = 0; y < inputVolume->height; y++) {
			for (int z = 0; z < inputVolume->depth; z++) {
				outputVolume->set(x + padding, y + padding, z, inputVolume->get(x, y, z));
			}
		}
	}
}

void Padding::feedBackward() {
	for(int x = 0; x < inputVolume->width; x++) {
		for(int y = 0; y < inputVolume->height; y++) {
			for (int z = 0; z < inputVolume->depth; z++) {
				errVsInput->set(x, y, z, errVsOutput->get(x + padding, y + padding, z));
			}
		}
	}
}