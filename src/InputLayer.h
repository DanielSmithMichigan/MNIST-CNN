#pragma once
#include <iostream>
#include <vector>
#include <stdint.h>
#include "TrainingImages.h"
#include "Layer.h"
using namespace std;

class InputLayer : public Layer {
	private:
	protected:
	public:
		PixelStream *pixelStream;
		InputLayer(int width, int height);
		~InputLayer();
		void initialize(float value);
		void feedImage();
};