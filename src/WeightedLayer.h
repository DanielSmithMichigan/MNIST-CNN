#pragma once
#include "Layer.h"
using namespace std;

class WeightedLayer : public Layer {
	private:
		int stride;
		int outputHeight;
		int outputWidth;
	protected:
	public:
		WeightedLayer(int width, int height);
		~WeightedLayer();
		bool useRandomWeights = true;
		vector<float> weights;
		float getWeight(int x, int y);
		void setWeight(int x, int y, float value);
		void initializeWeights(float value = 1);
};