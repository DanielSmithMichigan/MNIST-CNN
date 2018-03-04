#include "InputLayer.h"

InputLayer::InputLayer(int width, int height) : Layer(width, height) {
	nodes.resize(width * height);
}

InputLayer::~InputLayer() {

}

void InputLayer::initialize(float value) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			setNode(x, y, value);
		}
	}
}

void InputLayer::feedImage() {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			setNode(x, y, pixelStream->get());
		}
	}
}