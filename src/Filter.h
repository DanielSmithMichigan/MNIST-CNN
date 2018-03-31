#pragma once
#include <cmath>
#include "Constants.h"
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
	protected:
	public:
		Filter(int filterWidth, int filterHeight, int stride, Volume *inputVolume);
		~Filter();
		Volume *errVsInput;
		Volume *errVsOutput;
		Volume *outputVolume;
		Volume *inputVolume;
		Volume *weights;
		void feedForward();
		void feedBackward();
};