#pragma once
#include <fstream>

using namespace std;

class TrainingLabels {
	private:
		ifstream dataStream;
	protected:
	public:
		TrainingLabels();
		~TrainingLabels();
		static TrainingLabels *instance;
		void initialize();
		uint8_t getLabel();
};