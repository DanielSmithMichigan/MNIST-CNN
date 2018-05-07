#include "Volume.h"

Volume::Volume(int width, int height, int depth) 
	: width(width),
	  height(height),
	  depth(depth) {
	values.resize(width);
	for (int x = 0; x < width; x++) {
		values[x].resize(height);
		for (int y = 0; y < height; y++) {
			values[x][y].resize(depth);
		}
	}
	initialize();
}

Volume::Volume(vector<vector<vector<float>>> v) :
	values(v),
	width(v.size()),
	height(v[0].size()),
	depth(v[0][0].size()) {

}

Volume::~Volume() {

}

float Volume::get(int x, int y, int z) {
	return values[x][y][z];
}

void Volume::set(int x, int y, int z, float value) {
	values[x][y][z] = value;
}

void Volume::add(int x, int y, int z, float value) {
	values[x][y][z] += value;
}

void Volume::initialize(float initValue) {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			for (int z = 0; z < depth; z++) {
				values[x][y][z] = initValue;
			}
		}
	}
}

void Volume::initRandom(float mean, float stdDev) {
	uniform_real_distribution<float> distribution(-stdDev, stdDev);
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			for (int z = 0; z < depth; z++) {
				values[x][y][z] = distribution(RandomSeed::generator);
			}
		}
	}
}