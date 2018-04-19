#include "VolumeConcatenation.h"

VolumeConcatenation::VolumeConcatenation(vector<Volume*> inputVolumes) 
	: inputVolumes(inputVolumes) {
	outputWidth = inputVolumes[0]->width;
	outputHeight = inputVolumes[0]->height;
	outputDepth = 0;
	for (int i = 0; i < inputVolumes.size(); i++) {
		outputDepth += inputVolumes[i]->depth;
	}
	outputVolume = new Volume(outputWidth, outputHeight, outputDepth);
	errVsOutput = new Volume(outputWidth, outputHeight, outputDepth);
}

VolumeConcatenation::~VolumeConcatenation() {

}

void VolumeConcatenation::feedForward() {
	int currentDepth = 0;
	for (int i = 0; i < inputVolumes.size(); i++) {
		for (int z = 0; z < inputVolumes[i]->depth; z++) {
			for (int x = 0; x < outputWidth; x++) {
				for (int y = 0; y < outputHeight; y++) {
					outputVolume->set(x, y, currentDepth, inputVolumes[i]->get(x, y, z));
				}
			}
			currentDepth++;
		}
	}
}

void VolumeConcatenation::feedBackward() {
	int currentDepth = 0;
	for (int i = 0; i < inputVolumes.size(); i++) {
		for (int z = 0; z < inputVolumes[i]->depth; z++) {
			for (int x = 0; x < outputWidth; x++) {
				for (int y = 0; y < outputHeight; y++) {
					errVsInputs[i]->set(x, y, z, errVsOutput->get(x, y, currentDepth));
				}
			}
			currentDepth++;
		}
	}
}