#pragma once
#include "Volume.h"
#include <cmath>
#define eConstant 2.71828182

using namespace std;

class Sigmoid {
	private:
	protected:
	public:
		Sigmoid(Volume *inputVolume);
		~Sigmoid();
		Volume *outputVolume;
		Volume *errVsOutput;
		Volume *inputVolume;
		Volume *errVsInput;
		void feedForward();
		void feedBackward();
};