#include "TrainingImages.h"

TrainingImages::TrainingImages() {
	
}

TrainingImages::~TrainingImages() {

}

void TrainingImages::initialize() {
	dataStream.open("../train-images-idx3-ubyte", ios::in | ios::binary);
	dataStream.ignore(16);
}

void TrainingImages::reset() {
	dataStream.clear();
	dataStream.seekg(16, ios::beg);
}

uint8_t TrainingImages::get() {
	return dataStream.get();
}