#include "NormalizationTest.h"

NormalizationTest::NormalizationTest() {
}

NormalizationTest::~NormalizationTest() {
}

void NormalizationTest::SetUp() {
}

TEST_F(NormalizationTest, FirstInput) {
	Volume *errVsInput = new Volume(1, 1, 1);
	Volume *inputVolume = new Volume(1, 1, 1);
	Normalization *normalization = new Normalization(inputVolume, 50);
	normalization->errVsInput = errVsInput;

	inputVolume->set(0, 0, 0, 5);
	normalization->feedForward();
	ASSERT_EQ(normalization->outputVolume->get(0, 0, 0), 0);
	normalization->errVsOutput->set(0,0,0,0);
	normalization->feedBackward();
	ASSERT_EQ(normalization->errVsInput->get(0,0,0), 0);
}

TEST_F(NormalizationTest, FirstWrongInput) {
	Volume *errVsInput = new Volume(1, 1, 1);
	Volume *inputVolume = new Volume(1, 1, 1);
	Normalization *normalization = new Normalization(inputVolume, 50);
	normalization->errVsInput = errVsInput;

	inputVolume->set(0, 0, 0, 3);
	normalization->feedForward();
	ASSERT_EQ(normalization->outputVolume->get(0, 0, 0), 0);
	normalization->errVsOutput->set(0,0,0,1);
	normalization->feedBackward();
	ASSERT_EQ(normalization->beta->get(0, 0, 0), -.5);
	ASSERT_EQ(normalization->gamma->get(0, 0, 0), 1);
	ASSERT_FLOAT_EQ(normalization->errVsInput->get(0, 0, 0), 0);
}

TEST_F(NormalizationTest, SecondWrongInput) {
	Volume *errVsInput = new Volume(1, 1, 1);
	Volume *inputVolume = new Volume(1, 1, 1);
	Normalization *normalization = new Normalization(inputVolume, 50);
	normalization->errVsInput = errVsInput;

	inputVolume->set(0, 0, 0, 5);
	normalization->feedForward();
	ASSERT_EQ(normalization->outputVolume->get(0, 0, 0), 0);
	normalization->errVsOutput->set(0,0,0,1);
	normalization->feedBackward();
	ASSERT_EQ(normalization->beta->get(0, 0, 0), -.5);
	ASSERT_EQ(normalization->gamma->get(0, 0, 0), 1);
	ASSERT_FLOAT_EQ(normalization->errVsInput->get(0, 0, 0), 0);

	inputVolume->set(0, 0, 0, 3);
	normalization->feedForward();
	ASSERT_FLOAT_EQ(normalization->outputVolume->get(0, 0, 0), -1 * normalization->gamma->get(0, 0, 0) + normalization->beta->get(0, 0, 0));
	normalization->errVsOutput->set(0,0,0,2);
	normalization->feedBackward();
	ASSERT_EQ(normalization->beta->get(0, 0, 0), -2);
	ASSERT_FLOAT_EQ(normalization->gamma->get(0, 0, 0), -1.5 * 2);
	ASSERT_FLOAT_EQ(normalization->errVsInput->get(0, 0, 0), 5);
}