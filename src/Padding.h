#pragma once
#include "Layer.h"
using namespace std;

class Padding : public Layer {
	private:
		int padding;
	protected:
	public:
		Padding(int padding, Layer *priorLayer);
		~Padding();
		void feedForward();
		void feedBackward();
};