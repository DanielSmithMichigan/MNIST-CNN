#pragma once
#include <list>
#include <vector>
#include <cmath>
#include "Volume.h"

using namespace std;

class Normalization {
	private:
		int windowSize;
		vector<vector<vector<list <float>>>> entries;
		void addToEntry(list<float> &entry, float val);
		float getMean(list<float> &entry);
		float getVariance(list<float> &entry, float mean);
	protected:
	public:
		Normalization(Volume *inputVolume, int windowSize);
		~Normalization();
		Volume *inputVolume;
		Volume *outputVolume;
		void feedForward();
};