#include "src/TrainingImages.h"
#include "src/TrainingLabels.h"
#include "src/InputLayer.h"
#include "src/Filter.h"
#include "src/Padding.h"
#include "src/VolumeConcatenation.h"
#include "src/FullyConnected.h"
#include "src/Sigmoid.h"
#include "src/Relu.h"
#include <iostream>
#include <string>
// #include <opencv2/core/core.hpp>
// #include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
// #include <opencv2/features2d.hpp>
// #include <opencv2/text.hpp>
// #include <opencv2/xfeatures2d/nonfree.hpp>
// #include <opencv2/calib3d/calib3d.hpp>

int __WIDTH = 28;
int __HEIGHT = 28;
int __NUM_FILTERS = 30;
int __ITERATIONS = 60000;

using namespace std;
int main(int argc, char** argv)
{
	cv::Mat img(__WIDTH, __HEIGHT, CV_8UC1);
	TrainingImages *tImages = new TrainingImages();
	tImages->initialize();
	TrainingLabels::instance->initialize();
	InputLayer *inputLayer = new InputLayer(__WIDTH, __HEIGHT);
	inputLayer->pixelStream = tImages;
	Volume *fakeErrVsOutput = new Volume(28, 28, 1);
	vector<Volume *> hiddenVolumes;
	vector<Filter *> filters;
	for (int i = 0; i < __NUM_FILTERS; i++) {
		Filter *f0 = new Filter(3, 3, 1, inputLayer->outputVolume);
		f0->errVsInput = fakeErrVsOutput;
		filters.push_back(f0);
		hiddenVolumes.push_back(f0->outputVolume);
	}
	VolumeConcatenation *v0 = new VolumeConcatenation(hiddenVolumes);
	for (int i = 0; i < __NUM_FILTERS; i++) {
		v0->errVsInputs.push_back(filters[i]->errVsOutput);
	}
	Relu *r0 = new Relu(v0->outputVolume);
	r0->errVsInput = v0->errVsOutput;
	FullyConnected *fc0 = new FullyConnected(10, r0->outputVolume);
	fc0->errVsInput = r0->errVsOutput;
	Sigmoid *s0 = new Sigmoid(fc0->outputVolume);
	s0->errVsInput = fc0->errVsOutput;
	int correct = 0;
	int total = 0;
	for (int i = 0; i < __ITERATIONS; i++) {
		uint8_t label = TrainingLabels::instance->getLabel();
		inputLayer->feedForward();
		for (int j = 0; j < __NUM_FILTERS; j++) {
			filters[j]->feedForward();
		}
		v0->feedForward();
		r0->feedForward();
		fc0->feedForward();
		s0->feedForward();
		float max = INT32_MIN;
		int maxPredict;
		for (int j = 0; j < 10; j++) {
			float target = label == j ? 1 : -1;
			float prediction = s0->outputVolume->get(j, 0, 0);
			if (prediction > max) {
				maxPredict = j;
				max = prediction;
			}
			s0->errVsOutput->set(j, 0, 0, prediction - target);
		}
		if (maxPredict == label) {
			correct++;
		}
		s0->feedBackward();
		fc0->feedBackward();
		r0->feedBackward();
		v0->feedBackward();
		for (int j = 0; j < __NUM_FILTERS; j++) {
			filters[j]->feedBackward();
		}
		total++;
		cout << "Total: " << total << " correct: " << correct << " accuracy: " << (float)correct / (float)total << " label: " << to_string(label) << " Prediction: " << maxPredict << endl;
	}
    return 0;
}