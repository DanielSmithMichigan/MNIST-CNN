#pragma once
#include "Volume.h"

using namespace std;

class Relu {
	private:
	protected:
	public:
		Relu(Volume *inputVolume);
		~Relu();
		Volume *outputVolume;
		Volume *inputVolume;
		void feedForward();
		void feedBackward();
};