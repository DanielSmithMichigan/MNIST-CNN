#include "TrainingLabels.h"

TrainingLabels *TrainingLabels::instance = new TrainingLabels();

TrainingLabels::TrainingLabels() {

}

TrainingLabels::~TrainingLabels() {

}

void TrainingLabels::initialize() {
	dataStream.open("../train-labels-idx1-ubyte", ios::in | ios::binary);
	dataStream.ignore(8);
}

uint8_t TrainingLabels::getLabel() {
	return dataStream.get();
}