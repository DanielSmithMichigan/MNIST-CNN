#include "Normalization.h"

Normalization::Normalization(int width, int height, Layer *inputLayer) : inputLayer(inputLayer), Layer(width, height) {
	nodes.resize(width * height);
	inputs.resize(width * height);
}

Normalization::~Normalization() {

}

void Normalization::feedForward() {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float val = inputLayer->getNode(x, y);
			list<float> &entry = inputs[y * width + x];
			addToEntry(entry, val);
			float mean = getMean(entry);
			float variance = getVariance(entry, mean);
			float nodeOutput = (val - mean) / sqrt(variance + __FLT_EPSILON__);
			setNode(x, y, nodeOutput);
		}
	}
}

void Normalization::addToEntry(list<float> &entry, float val) {
	entry.push_back(val);
	if (entry.size() > __MAX_ENTRY_SIZE) {
		entry.pop_front();
	}
}

float Normalization::getMean(list<float> &entry) {
	float sum = 0;
	for (std::list<float>::iterator it=entry.begin(); it != entry.end(); ++it) {
		sum += *it;
	}
	return sum / entry.size();
}

float Normalization::getVariance(list<float> &entry, float mean) {
	float sum = 0;
	for (std::list<float>::iterator it=entry.begin(); it != entry.end(); ++it) {
		sum += pow(*it - mean, 2);
	}
	return sum / entry.size();
}