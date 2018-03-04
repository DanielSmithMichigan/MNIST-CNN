#include "TrainingImages.h"

TrainingImages::TrainingImages() {
	
}

TrainingImages::~TrainingImages() {

}

void TrainingImages::initialize() {
	dataStream.open("../train-images-idx3-ubyte", ios::in | ios::binary);
	dataStream.ignore(16);
}

uint8_t TrainingImages::get() {
	return dataStream.get();
}