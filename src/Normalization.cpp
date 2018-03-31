#include "Normalization.h"

Normalization::Normalization(Volume *inputVolume, int windowSize) :
	inputVolume(inputVolume),
	windowSize(windowSize) {
	outputVolume = new Volume(inputVolume->width, inputVolume->height, inputVolume->depth);
	entries.resize(inputVolume->width);
	for (int x = 0; x < inputVolume->width; x++) {
		entries[x].resize(inputVolume->height);
		for (int y = 0; y < inputVolume->height; y++) {
			entries[x][y].resize(inputVolume->depth);
		}
	}
}

Normalization::~Normalization() {

}

void Normalization::feedForward() {
	for (int z = 0; z < inputVolume->depth; z++) {
		for (int y = 0; y < inputVolume->height; y++) {
			for (int x = 0; x < inputVolume->width; x++) {
				float val = inputVolume->get(x, y, z);
				list<float> &entry = entries[x][y][z];
				addToEntry(entry, val);
				float mean = getMean(entry);
				float variance = getVariance(entry, mean);
				float nodeOutput = (val - mean) / sqrt(variance + __FLT_EPSILON__);
				outputVolume->set(x, y, z, nodeOutput);
			}
		}
	}
}

void Normalization::addToEntry(list<float> &entry, float val) {
	entry.push_back(val);
	if (entry.size() > windowSize) {
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