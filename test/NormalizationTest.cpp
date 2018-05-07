#include "NormalizationTest.h"

NormalizationTest::NormalizationTest() {
}

NormalizationTest::~NormalizationTest() {
}

void NormalizationTest::SetUp() {
}

TEST_F(NormalizationTest, FirstInput) {
	Layer *inputLayer = new Layer();
	inputLayer->errVsOutput = new Volume(1, 1, 1);
	inputLayer->outputVolume = new Volume(1, 1, 1);
	Normalization *normalization = new Normalization(inputLayer, 50);

	inputLayer->outputVolume->set(0, 0, 0, 5);
	normalization->feedForward();
	ASSERT_EQ(normalization->outputVolume->get(0, 0, 0), 0);
	normalization->errVsOutput->set(0,0,0,0);
	normalization->feedBackward();
	ASSERT_EQ(normalization->errVsInput->get(0,0,0), 0);
}

TEST_F(NormalizationTest, FirstWrongInput) {
	Layer *inputLayer = new Layer();
	inputLayer->errVsOutput = new Volume(1, 1, 1);
	inputLayer->outputVolume = new Volume(1, 1, 1);
	Normalization *normalization = new Normalization(inputLayer, 50);
	inputLayer->outputVolume->set(0, 0, 0, 3);
	normalization->feedForward();
	ASSERT_EQ(normalization->outputVolume->get(0, 0, 0), 0);
	normalization->errVsOutput->set(0,0,0,1);
	normalization->feedBackward();
	ASSERT_FLOAT_EQ(normalization->beta->get(0, 0, 0), -__LEARNING_RATE);
	ASSERT_FLOAT_EQ(normalization->gamma->get(0, 0, 0), 1);
	ASSERT_FLOAT_EQ(normalization->errVsInput->get(0, 0, 0), 0);
}

// TEST_F(NormalizationTest, SecondWrongInput) {
// 	Layer *inputLayer = new Layer();
// 	inputLayer->errVsOutput = new Volume(1, 1, 1);
// 	inputLayer->outputVolume = new Volume(1, 1, 1);
// 	Normalization *normalization = new Normalization(inputLayer, 50);
// 	inputLayer->outputVolume->set(0, 0, 0, 5);
// 	normalization->feedForward();
// 	ASSERT_EQ(normalization->outputVolume->get(0, 0, 0), 0);
// 	normalization->errVsOutput->set(0,0,0,1);
// 	normalization->feedBackward();
// 	ASSERT_EQ(normalization->beta->get(0, 0, 0), -__LEARNING_RATE);
// 	ASSERT_EQ(normalization->gamma->get(0, 0, 0), 1);
// 	ASSERT_FLOAT_EQ(normalization->errVsInput->get(0, 0, 0), 0);

// 	inputLayer->outputVolume->set(0, 0, 0, 3);
// 	normalization->feedForward();
// 	ASSERT_FLOAT_EQ(normalization->outputVolume->get(0, 0, 0), -1 * normalization->gamma->get(0, 0, 0) + normalization->beta->get(0, 0, 0));
// 	normalization->errVsOutput->set(0,0,0,2);
// 	normalization->feedBackward();
// 	ASSERT_EQ(normalization->beta->get(0, 0, 0), -2);
// 	ASSERT_FLOAT_EQ(normalization->gamma->get(0, 0, 0), (2 * -1) * -.5 + 1);
// 	ASSERT_FLOAT_EQ(normalization->errVsInput->get(0, 0, 0), normalization->gamma->get(0, 0, 0) * .5 * (2 * 2 - (-2 * -1) - 3));
// }