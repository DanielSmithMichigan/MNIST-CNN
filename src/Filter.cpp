#include "Filter.h"

Filter::Filter(int filterWidth, int filterHeight, int stride, Volume *inputVolume) :
	filterWidth(filterWidth),
	filterHeight(filterHeight),
	stride(stride),
	inputVolume(inputVolume) {
	outputWidth = ceil((float)(inputVolume->width - filterWidth + 1) / (float)stride);
	outputHeight = ceil((float)(inputVolume->height - filterHeight + 1) / (float)stride);
	outputVolume = new Volume(outputWidth, outputHeight, 1);
	errVsOutput = new Volume(outputWidth, outputHeight, 1);
	weights = new Volume(filterWidth, filterHeight, inputVolume->depth);
	weights->initialize(1);
}

Filter::~Filter() {

}

void Filter::feedForward() {
	outputVolume->initialize();
	for (int inputZ = 0; inputZ < inputVolume->depth; inputZ++) {
		for (int outputY = 0; outputY < outputVolume->height; outputY++) {
			for(int outputX = 0; outputX < outputVolume->width; outputX++) {
				for (int filterY = 0; filterY < filterHeight; filterY++) {
					for (int filterX = 0; filterX < filterWidth; filterX++) {
						float value = weights->get(filterX, filterY, inputZ) * inputVolume->get(outputX * stride + filterX, outputY * stride + filterY, inputZ);
						outputVolume->add(outputX, outputY, 0, value);
					}
				}
			}
		}
	}
}

void Filter::feedBackward() {
	errVsInput->initialize();
	for (int inputZ = 0; inputZ < inputVolume->depth; inputZ++) {
		for (int outputY = 0; outputY < outputVolume->height; outputY++) {
			for(int outputX = 0; outputX < outputVolume->width; outputX++) {
				for (int filterY = 0; filterY < filterHeight; filterY++) {
					for (int filterX = 0; filterX < filterWidth; filterX++) {
						errVsInput->add(outputX * stride + filterX, outputY * stride + filterY, inputZ, weights->get(filterX, filterY, inputZ) * errVsOutput->get(outputX, outputY, 0));
					}
				}
			}
		}
	}
	for (int inputZ = 0; inputZ < inputVolume->depth; inputZ++) {
		for (int outputY = 0; outputY < outputVolume->height; outputY++) {
			for(int outputX = 0; outputX < outputVolume->width; outputX++) {
				for (int filterY = 0; filterY < filterHeight; filterY++) {
					for (int filterX = 0; filterX < filterWidth; filterX++) {
						weights->add(filterX, filterY, inputZ, errVsOutput->get(outputX, outputY, 0) * inputVolume->get(outputX * stride + filterX, outputY * stride + filterY, inputZ) * -__LEARNING_RATE);
					}
				}
			}
		}
	}
}