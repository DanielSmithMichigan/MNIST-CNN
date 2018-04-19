#pragma once
#include "Constants.h"
#include "Volume.h"
#include <cmath>

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