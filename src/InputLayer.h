#pragma once
#include <iostream>
#include <vector>
#include <stdint.h>
#include "TrainingImages.h"
#include "Volume.h"
using namespace std;

class InputLayer{
	private:
	protected:
	public:
		Volume *outputVolume;
		PixelStream *pixelStream;
		InputLayer(int outputWidth, int outputHeight);
		~InputLayer();
		void feedForward();
};