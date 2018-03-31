#pragma once
#include <iostream>
#include <vector>
#include <stdint.h>
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
};