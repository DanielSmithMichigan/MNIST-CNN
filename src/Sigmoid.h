#pragma once
#include "Layer.h"
#include <cmath>

using namespace std;

class Sigmoid : public Layer{
	private:
	protected:
	public:
		Sigmoid(Layer *priorLayer);
		~Sigmoid();
		void feedForward();
		void feedBackward();
};