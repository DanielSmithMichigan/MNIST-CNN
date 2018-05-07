#include <opencv2/highgui/highgui.hpp>


int __WIDTH = 28;
int __HEIGHT = 28;


// #include <opencv2/core/core.hpp>
// #include <opencv2/imgproc/imgproc.hpp>
// #include <opencv2/features2d.hpp>
// #include <opencv2/text.hpp>
// #include <opencv2/xfeatures2d/nonfree.hpp>
// #include <opencv2/calib3d/calib3d.hpp>
#include <cmath>


#include "src/TrainingImages.h"
#include "src/TrainingLabels.h"
#include "src/InputLayer.h"
#include "src/Filter.h"
#include "src/Padding.h"
#include "src/VolumeConcatenation.h"
#include "src/FullyConnected.h"
#include "src/Sigmoid.h"
#include "src/Softmax.h"
#include "src/Normalization.h"
#include "src/Relu.h"
#include <iostream>
#include <string>

int __NUM_FILTERS = 30;
int __ITERATIONS = 60000;
int __TRAINING_RUNS = 30;

using namespace std;
int main(int argc, char** argv)
{
	vector <Layer *> layers;
	TrainingImages *tImages = new TrainingImages();
	InputLayer *inputLayer = new InputLayer(__WIDTH, __HEIGHT);
	inputLayer->pixelStream = tImages;
	FullyConnected *f0 = new FullyConnected(10, inputLayer);
	Sigmoid *s0 = new Sigmoid(f0);
	FullyConnected *f1 = new FullyConnected(10, s0);
	Sigmoid *s1 = new Sigmoid(f1);
	// FullyConnected *f2 = new FullyConnected(30, s1);
	// Relu *s2 = new Relu(f2);
	// Softmax *o = new Softmax(s2);
	layers.push_back(inputLayer);
	layers.push_back(f0);
	layers.push_back(s0);
	layers.push_back(f1);
	layers.push_back(s1);
	// layers.push_back(f2);
	// layers.push_back(s2);
	// layers.push_back(o);
	TrainingLabels::instance->initialize();
	tImages->initialize();
	for (int run = 0; run < __TRAINING_RUNS; run++) {
		TrainingLabels::instance->reset();
		tImages->reset();
		int correct = 0;
		int total = 0;
		for (int i = 0; i < __ITERATIONS; i++) {
			uint8_t label = TrainingLabels::instance->getLabel();
			for(int j = 0; j < layers.size(); j++) {
				layers[j]->feedForward();
			}
			float maxPredictionAmount = INT32_MIN;
			int mostLikelyPrediction;
			for (int j = 0; j < 10; j++) {
				float target = label == j ? 1 : 0;
				float predictionAmount = layers.back()->outputVolume->get(j, 0, 0);
				if (predictionAmount > maxPredictionAmount) {
					mostLikelyPrediction = j;
					maxPredictionAmount = predictionAmount;
				}
				layers.back()->errVsOutput->set(j, 0, 0, predictionAmount - target);
			}
			if (mostLikelyPrediction == label) {
				correct++;
			}
			for(int j = layers.size() - 1; j >= 0; j--) {
				layers[j]->feedBackward();
			}
			total++;
			cout << "Total: " << total << " correct: " << correct << " accuracy: " << (float)correct / (float)total << " label: " << to_string(label) << " Prediction: " << mostLikelyPrediction << "(" << maxPredictionAmount << ")" << endl;
			// if (i >= 5000) {
			// 	cv::imshow("Img",img);
			// 	cv::waitKey(0);
			// }
		}
	}
	// Volume *inputVolume = new Volume(28, 28, 1);
	// Volume *fakeErrVsOutput = new Volume(28, 28, 1);
	// vector<Volume *> hiddenVolumes;
	// vector<Filter *> filters;
	// for (int i = 0; i < __NUM_FILTERS; i++) {
	// 	Filter *f0 = new Filter(3, 3, 1, inputVolume);
	// 	f0->errVsInput = fakeErrVsOutput;
	// 	filters.push_back(f0);
	// 	hiddenVolumes.push_back(f0->outputVolume);
	// }
	// VolumeConcatenation *v0 = new VolumeConcatenation(hiddenVolumes);
	// for (int i = 0; i < __NUM_FILTERS; i++) {
	// 	v0->errVsInputs.push_back(filters[i]->errVsOutput);
	// }
	// Relu *r0 = new Relu(v0->outputVolume);
	// r0->errVsInput = v0->errVsOutput;
	// FullyConnected *fc0 = new FullyConnected(10, r0->outputVolume);
	// fc0->errVsInput = r0->errVsOutput;
	// Sigmoid *s0 = new Sigmoid(fc0->outputVolume);
	// s0->errVsInput = fc0->errVsOutput;
	// int correct = 0;
	// int total = 0;
	// for (int i = 0; i < __ITERATIONS; i++) {
	// 	uint8_t label = TrainingLabels::instance->getLabel();
	// 	inputLayer->feedForward();
	// 	for (int j = 0; j < __NUM_FILTERS; j++) {
	// 		filters[j]->feedForward();
	// 	}
	// 	v0->feedForward();
	// 	r0->feedForward();
	// 	fc0->feedForward();
	// 	s0->feedForward();
	// 	float max = INT32_MIN;
	// 	int maxPredict;
	// 	for (int j = 0; j < 10; j++) {
	// 		float target = label == j ? 1 : -1;
	// 		float prediction = s0->outputVolume->get(j, 0, 0);
	// 		if (prediction > max) {
	// 			maxPredict = j;
	// 			max = prediction;
	// 		}
	// 		s0->errVsOutput->set(j, 0, 0, prediction - target);
	// 	}
	// 	if (maxPredict == label) {
	// 		correct++;
	// 	}
	// 	s0->feedBackward();
	// 	fc0->feedBackward();
	// 	r0->feedBackward();
	// 	v0->feedBackward();
	// 	for (int j = 0; j < __NUM_FILTERS; j++) {
	// 		filters[j]->feedBackward();
	// 	}
	// 	total++;
	// 	cout << "Total: " << total << " correct: " << correct << " accuracy: " << (float)correct / (float)total << " label: " << to_string(label) << " Prediction: " << maxPredict << endl;
	// }
 //    return 0;
}