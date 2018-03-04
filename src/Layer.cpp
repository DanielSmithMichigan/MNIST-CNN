#include "Layer.h"

Layer::Layer(int width, int height) : width(width), height(height) {
}

Layer::~Layer() {

}

float Layer::getNode(int x, int y) {
	return nodes[y * width + x];
}

void Layer::setNode(int x, int y, float value) {
	nodes[y * width + x] = value;
}