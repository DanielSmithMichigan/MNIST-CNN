#pragma once
#include <cmath>
#include "Volume.h"
using namespace std;

class Filter{
	private:
		int stride;
		int filterWidth;
		int filterHeight;
		int outputWidth;
		int outputHeight;
		int outputDepth;
		int inputIndex;
	protected:
	public:
		Filter(int filterWidth, int filterHeight, int stride, Volume *inputVolume, int inputIndex);
		~Filter();
		Volume *errVsInput;
		Volume *errVsOutput;
		Volume *outputVolume;
		Volume *inputVolume;
		Volume *weights;
		void feedForward();
		void feedBackward();
};