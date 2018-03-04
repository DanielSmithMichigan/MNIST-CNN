#include "Filter.h"

Filter::Filter(int width, int height, int stride, Layer *inputLayer)
	: inputLayer(inputLayer),
	stride(stride),
	WeightedLayer(width, height) {
	outputWidth = ceil((float)(inputLayer->width - width + 1) / (float)stride);
	outputHeight = ceil((float)(inputLayer->height - height + 1) / (float)stride);
	nodes.resize(outputWidth * outputHeight);
}

Filter::~Filter() {

}

void Filter::feedForward() {
	for (int outputY = 0; outputY < outputHeight; outputY++) {
		for(int outputX = 0; outputX < outputWidth; outputX++) {
			int nodeOffset = outputY * outputWidth + outputX;
			nodes[nodeOffset] = 0;
			for (int filterY = 0; filterY < height; filterY++) {
				for (int filterX = 0; filterX < width; filterX++) {
					nodes[nodeOffset] += getWeight(filterX, filterY) * inputLayer->getNode(outputX * stride + filterX, outputY * stride + filterY);
				}
			}
		}
	}
}