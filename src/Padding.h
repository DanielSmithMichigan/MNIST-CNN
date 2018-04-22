#pragma once
#include <cmath>
#include "Constants.h"
#include "Volume.h"
using namespace std;

class Padding{
	private:
		int padding;
	protected:
	public:
		Padding(int padding, Volume *inputVolume);
		~Padding();
		Volume *errVsInput;
		Volume *errVsOutput;
		Volume *outputVolume;
		Volume *inputVolume;
		void feedForward();
		void feedBackward();
};