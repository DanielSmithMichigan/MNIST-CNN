#include "Volume4d.h"

Volume4d::Volume4d(int width, int height, int depth, int numVolumes) 
	: width(width),
	  height(height),
	  depth(depth),
	  numVolumes(numVolumes) {
	values.resize(width);
	for (int x = 0; x < width; x++) {
		values[x].resize(height);
		for (int y = 0; y < height; y++) {
			values[x][y].resize(depth);
			for (int z = 0; z < depth; z++) {
				values[x][y][z].resize(numVolumes);
			}
		}
	}
	initialize();
}

Volume4d::~Volume4d() {

}

float Volume4d::get(int x, int y, int z, int i) {
	return values[x][y][z][i];
}

void Volume4d::set(int x, int y, int z, int i, float value) {
	values[x][y][z][i] = value;
}

void Volume4d::add(int x, int y, int z, int i, float value) {
	values[x][y][z][i] += value;
}

void Volume4d::initialize(float initValue) {
	for (int i = 0; i < numVolumes; i++) {
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				for (int z = 0; z < depth; z++) {
					values[x][y][z][i] = initValue;
				}
			}
		}
	}
}

void Volume4d::initRandom(float moan, float stdDev) {
	auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
	auto real_rand = std::bind(std::uniform_real_distribution<double>(0,1), mt19937(seed));
	for (int i = 0; i < numVolumes; i++) {
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				for (int z = 0; z < depth; z++) {
					values[x][y][z][i] = real_rand();
				}
			}
		}
	}
}