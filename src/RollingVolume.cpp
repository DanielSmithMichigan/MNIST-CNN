#include "RollingVolume.h"

RollingVolume::RollingVolume(int width, int height, int depth, int windowSize) 
	: width(width),
	  height(height),
	  depth(depth),
	  windowSize(windowSize) {
  	currentSize = 0;
	values.resize(width);
	for (int x = 0; x < width; x++) {
		values[x].resize(height);
		for (int y = 0; y < height; y++) {
			values[x][y].resize(depth);
		}
	}
}

RollingVolume::~RollingVolume() {

}

float RollingVolume::getLast(int x, int y, int z) {
	return values[x][y][z].back();
}

void RollingVolume::push(int x, int y, int z, float value) {
	list<float> &entry = values[x][y][z];
	entry.push_back(value);
	if (entry.size() > windowSize) {
		currentSize = windowSize;
		entry.pop_front();
	} else {
		currentSize++;
	}
}

float RollingVolume::getSum(int x, int y, int z) {
	float sum = 0;
	list<float> &entry = values[x][y][z];
	for (std::list<float>::iterator it=entry.begin(); it != entry.end(); ++it) {
		sum += *it;
	}
	return sum;
}

float RollingVolume::getMean(int x, int y, int z) {
	list<float> &entry = values[x][y][z];
	return getSum(x, y, z) / entry.size();
}

float RollingVolume::getVariance(int x, int y, int z, float mean) {
	float sum = 0;
	list<float> &entry = values[x][y][z];
	for (std::list<float>::iterator it=entry.begin(); it != entry.end(); ++it) {
		sum += pow(*it - mean, 2);
	}
	return sum / getSize();
}

int RollingVolume::getSize() {
	return currentSize;
}