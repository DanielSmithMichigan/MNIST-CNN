#pragma once
#include <iostream>
#include <vector>
#include <stdint.h>
#include <cstdlib>
#include <random>
#include <chrono>
using namespace std;

class Volume {
	private:
		vector<vector<vector<float>>> values;
	protected:
	public:
		Volume(int width, int height, int depth);
		~Volume();
		int width;
		int height;
		int depth;
		float get(int x, int y, int z);
		void set(int x, int y, int z, float value);
		void add(int x, int y, int z, float value);
		void initialize(float initValue = 0);
		void initRandom(float moan, float stdDev);
};