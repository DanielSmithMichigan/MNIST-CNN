#pragma once
#include "Layer.h"

using namespace std;

class Relu : public Layer {
	private:
	protected:
	public:
		Relu(Layer *priorLayer);
		~Relu();
		void feedForward();
		void feedBackward();
};