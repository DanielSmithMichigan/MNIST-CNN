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

void TrainingLabels::reset() {
	dataStream.clear();
	dataStream.seekg(8, ios::beg);
}

uint8_t TrainingLabels::getLabel() {
	return dataStream.get();
}