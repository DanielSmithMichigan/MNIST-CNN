#pragma once
#include "PixelStream.h"
#include <fstream>

using namespace std;

class TrainingImages : public PixelStream {
	private:
		ifstream dataStream;
	protected:
	public:
		TrainingImages();
		~TrainingImages();
		void initialize();
		void reset();
		uint8_t get();
};