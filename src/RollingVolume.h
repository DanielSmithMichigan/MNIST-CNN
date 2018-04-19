#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <stdint.h>
using namespace std;

class RollingVolume {
	private:
		vector<vector<vector<list<float>>>> values;
	protected:
	public:
		RollingVolume(int width, int height, int depth, int windowSize);
		~RollingVolume();
		int width;
		int height;
		int depth;
		int windowSize;
		int currentSize;
		float getLast(int x, int y, int z);
		float getMean(int x, int y, int z);
		float getVariance(int x, int y, int z, float mean);
		float getSum(int x, int y, int z);
		void push(int x, int y, int z, float value);
		int getSize();
};