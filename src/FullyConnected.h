#pragma once
#include <cmath>
#include "Constants.h"
#include "Volume4d.h"
#include "Volume.h"
using namespace std;

class FullyConnected{
	private:
		int nodeCount;
	protected:
	public:
		FullyConnected(int nodeCount, Volume *inputVolume);
		~FullyConnected();
		void feedForward();
		void feedBackward();
		Volume4d *weights;
		vector<float> biases;
		Volume *outputVolume;
		Volume *errVsOutput;
		Volume *inputVolume;
		Volume *errVsInput;
};