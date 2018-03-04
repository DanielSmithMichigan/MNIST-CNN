#pragma once
#include <iostream>
#include <vector>
#include <stdint.h>
#include "TrainingImages.h"
using namespace std;

class Layer {
	private:
	protected:
	public:
		Layer(int width, int height);
		~Layer();
		float getNode(int x, int y);
		void setNode(int x, int y, float value);
		vector<float> nodes;
		int width;
		int height;
};