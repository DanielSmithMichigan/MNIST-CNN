#include "Normalization.h"

Normalization::Normalization(Layer *priorLayer, int windowSize) :
	windowSize(windowSize),
	Layer(priorLayer) {
	outputVolume = new Volume(inputVolume->width, inputVolume->height, inputVolume->depth);
	errVsOutput = new Volume(inputVolume->width, inputVolume->height, inputVolume->depth);
	gamma = new Volume(inputVolume->width, inputVolume->height, inputVolume->depth);
	gamma->initialize(1);
	beta = new Volume(inputVolume->width, inputVolume->height, inputVolume->depth);
	beta->initialize(0);
	values = new RollingVolume(inputVolume->width, inputVolume->height, inputVolume->depth, windowSize);
	rollingErrVsOutput = new RollingVolume(inputVolume->width, inputVolume->height, inputVolume->depth, windowSize);
	xhatCache = new Volume(inputVolume->width, inputVolume->height, inputVolume->depth);
	xhatDy = new RollingVolume(inputVolume->width, inputVolume->height, inputVolume->depth, windowSize);
}

Normalization::~Normalization() {

}

void Normalization::feedForward() {
	for (int z = 0; z < inputVolume->depth; z++) {
		for (int y = 0; y < inputVolume->height; y++) {
			for (int x = 0; x < inputVolume->width; x++) {
				float val = inputVolume->get(x, y, z);
				values->push(x, y, z, val);
				float mean = values->getMean(x, y, z);
				float variance = values->getVariance(x, y, z, mean);
				float xhat = (val - mean) / sqrt(variance + __FLT_EPSILON__);
				xhatCache->set(x, y, z, xhat);
				float output = gamma->get(x, y, z) * xhat + beta->get(x, y, z);
				outputVolume->set(x, y, z, output);
			}
		}
	}
}

void Normalization::feedBackward() {
	for (int z = 0; z < inputVolume->depth; z++) {
		for (int y = 0; y < inputVolume->height; y++) {
			for (int x = 0; x < inputVolume->width; x++) {
				rollingErrVsOutput->push(x, y, z, errVsOutput->get(x, y, z));
				float sumErrVsOutput = rollingErrVsOutput->getSum(x, y, z);
				float dy = errVsOutput->get(x, y, z);
				float dxhat = dy * gamma->get(x, y, z);
				float xhat = xhatCache->get(x, y, z);
				xhatDy->push(x, y, z, xhat * dy);
				float dGamma = xhatDy->getSum(x, y, z);
				float dBeta = sumErrVsOutput;

				float mean = values->getMean(x, y, z);
				float variance = values->getVariance(x, y, z, mean);
				float rootVar = sqrt(variance + __FLT_EPSILON__);

				float dx = gamma->get(x, y, z) / values->getSize() / rootVar * (values->getSize() * dy - dGamma * xhat - dBeta);
				beta->add(x, y, z, -__LEARNING_RATE * dBeta);
				gamma->add(x, y, z, -__LEARNING_RATE * dGamma);
				errVsInput->set(x, y, z, dx);
			}
		}
	}
}