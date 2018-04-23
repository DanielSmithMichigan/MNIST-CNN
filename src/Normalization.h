#pragma once
#include <list>
#include <vector>
#include <cmath>
#include "Layer.h"
#include "RollingVolume.h"

using namespace std;

class Normalization : public Layer {
	private:
		int windowSize;
		RollingVolume *values;
		RollingVolume *rollingErrVsOutput;
		Volume *xhatCache;
		RollingVolume *xhatDy;
		Volume *dxhat;
		void addToEntry(list<float> &entry, float val);
		float getMean(list<float> &entry);
		float getVariance(list<float> &entry, float mean);
	protected:
	public:
		Normalization(int windowSize, Layer *priorLayer);
		~Normalization();
		Volume *gamma;
		Volume *beta;
		void feedForward();
		void feedBackward();
};