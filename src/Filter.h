#pragma once
#include <cmath>
#include "WeightedLayer.h"
using namespace std;

class Filter : public WeightedLayer {
	private:
		int stride;
		int outputHeight;
		int outputWidth;
	protected:
	public:
		Filter(int width, int height, int stride, Layer* inputLayer);
		~Filter();
		Layer *inputLayer;
		void feedForward();
};