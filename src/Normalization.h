#pragma once
#include <list>
#include <vector>
#include <cmath>
#include "Layer.h"

using namespace std;

class Normalization : public Layer {
	private:
		vector<list<float>> inputs;
	protected:
	public:
		Normalization(int width, int height, Layer *inputLayer);
		~Normalization();
		Layer *inputLayer;
		void feedForward();
		void addToEntry(list<float> &entry, float val);
		float getMean(list<float> &entry);
		float getVariance(list<float> &entry, float mean);
		int __MAX_ENTRY_SIZE = 50;
};