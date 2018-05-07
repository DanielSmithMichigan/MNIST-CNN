#pragma once
#include "Layer.h"
#include <cmath>

using namespace std;

class Softmax : public Layer{
	private:
	protected:
	public:
		Softmax(Layer *priorLayer);
		~Softmax();
		void feedForward();
		void feedBackward();
};