#pragma once
#include "Layer.h"
using namespace std;

class Filter : public Layer {
	private:
		int stride;
		int filterWidth;
		int filterHeight;
		int outputWidth;
		int outputHeight;
		int outputDepth;
	protected:
	public:
		Filter(int filterWidth, int filterHeight, int stride, Layer *priorLayer);
		~Filter();
		Volume *weights;
		void feedForward();
		void feedBackward();
};