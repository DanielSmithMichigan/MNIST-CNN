#pragma once
#include "Volume.h"
#include <vector>
#include <cmath>

using namespace std;

class VolumeConcatenation {
	private:
		int outputWidth;
		int outputHeight;
		int outputDepth;
	protected:
	public:
		VolumeConcatenation(vector<Volume*> inputVolume);
		~VolumeConcatenation();
		Volume *outputVolume;
		Volume *errVsOutput;
		vector<Volume*> inputVolumes;
		vector<Volume*> errVsInputs;
		void feedForward();
		void feedBackward();
};