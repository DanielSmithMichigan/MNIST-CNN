#pragma once
#include "Volume.h"
#include <vector>
#include <cmath>

using namespace std;

class VolumeConcatenation : public Layer {
	private:
		int outputWidth;
		int outputHeight;
		int outputDepth;
		vector <Volume *> priorLayers;
	protected:
	public:
		VolumeConcatenation(vector<Layer*> priorLayers);
		~VolumeConcatenation();
		vector<Volume*> inputVolumes;
		vector<Volume*> errVsInputs;
		void feedForward();
		void feedBackward();
};