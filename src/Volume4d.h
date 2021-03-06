#pragma once
#include <iostream>
#include <vector>
#include <stdint.h>
#include <cstdlib>
#include <random>
#include <chrono>
#include <functional>
#include "RandomSeed.h"
using namespace std;

class Volume4d {
	private:
		vector<vector<vector<vector<float>>>> values;
	protected:
	public:
		Volume4d(int width, int height, int depth, int numVolumes);
		~Volume4d();
		int width;
		int height;
		int depth;
		int numVolumes;
		float get(int x, int y, int z, int i);
		void set(int x, int y, int z, int i, float value);
		void add(int x, int y, int z, int i, float value);
		void initialize(float initValue = 0);
		void initRandom(float mean, float stdDev);
};