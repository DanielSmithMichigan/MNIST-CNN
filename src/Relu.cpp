#include "Relu.h"

Relu::Relu(int width, int height, Layer *inputLayer) : inputLayer(inputLayer), Layer(width, height) {
	nodes.resize(width * height);
}

Relu::~Relu() {

}

void Relu::feedForward() {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < height; x++) {
			float val = inputLayer->getNode(x, y);
			if (val < 0) {
				val = 0;
			}
			setNode(x, y, val);
		}
	}
}