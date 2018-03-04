#pragma once
#include "Layer.h"

using namespace std;

class Relu : public Layer {
	private:
	protected:
	public:
		Relu(int width, int height, Layer *inputLayer);
		~Relu();
		Layer *inputLayer;
		void feedForward();
};