#include "WeightedLayer.h"

WeightedLayer::WeightedLayer(int width, int height)
	: Layer(width, height) {
	weights.resize(width * height);
}

WeightedLayer::~WeightedLayer() {

}

float WeightedLayer::getWeight(int x, int y) {
	return weights[y * width + x];
}

void WeightedLayer::setWeight(int x, int y, float value) {
	weights[y * width + x] = value;
}

void WeightedLayer::initializeWeights(float value) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			setWeight(x, y, value);
		}
	}
}