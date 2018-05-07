#include "VolumeConcatenation.h"

VolumeConcatenation::VolumeConcatenation(vector<Layer*> priorLayers) 
	: Layer() {
	outputWidth = priorLayers[0]->inputVolume->width;
	outputHeight = priorLayers[0]->inputVolume->height;
	outputDepth = 0;
	for (int i = 0; i < inputVolumes.size(); i++) {
		outputDepth += priorLayers[i]->inputVolume->depth;
	}
	outputVolume = new Volume(outputWidth, outputHeight, outputDepth);
	errVsOutput = new Volume(outputWidth, outputHeight, outputDepth);
}

VolumeConcatenation::~VolumeConcatenation() {

}

void VolumeConcatenation::feedForward() {
	int currentDepth = 0;
	for (int i = 0; i < priorLayers.size(); i++) {
		for (int z = 0; z < priorLayers[i]->inputVolume->depth; z++) {
			for (int x = 0; x < outputWidth; x++) {
				for (int y = 0; y < outputHeight; y++) {
					outputVolume->set(x, y, currentDepth, priorLayers[i]->inputVolume->get(x, y, z));
				}
			}
			currentDepth++;
		}
	}
}

void VolumeConcatenation::feedBackward() {
	int currentDepth = 0;
	for (int i = 0; i < priorLayers.size(); i++) {
		for (int z = 0; z < priorLayers[i]->inputVolume->depth; z++) {
			for (int x = 0; x < outputWidth; x++) {
				for (int y = 0; y < outputHeight; y++) {
					priorLayers[i]->errVsOutput->set(x, y, z, errVsOutput->get(x, y, currentDepth));
				}
			}
			currentDepth++;
		}
	}
}