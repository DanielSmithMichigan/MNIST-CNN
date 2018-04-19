#pragma once
#include <list>
#include <vector>
#include <cmath>
#include "Volume.h"
#include "RollingVolume.h"
#include "Constants.h"

using namespace std;

class Normalization {
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
		Normalization(Volume *inputVolume, int windowSize);
		~Normalization();
		Volume *inputVolume;
		Volume *outputVolume;
		Volume *errVsOutput;
		Volume *errVsInput;
		Volume *gamma;
		Volume *beta;
		void feedForward();
		void feedBackward();
};