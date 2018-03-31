#include "NormalizationTest.h"

NormalizationTest::NormalizationTest() {
}

NormalizationTest::~NormalizationTest() {
}

void NormalizationTest::SetUp() {
}

TEST_F(NormalizationTest, FirstInput) {
	Volume *inputVolume = new Volume(1, 1, 1);
	inputVolume->set(0, 0, 0, 1);
	Normalization *normalization = new Normalization(inputVolume, 50);
	normalization->feedForward();
	ASSERT_EQ(normalization->outputVolume->get(0, 0, 0), 0);
}

TEST_F(NormalizationTest, TwoEqualInputs) {
	Volume *inputVolume = new Volume(1, 1, 1);
	inputVolume->set(0, 0, 0, 1);
	Normalization *normalization = new Normalization(inputVolume, 50);
	normalization->feedForward();
	normalization->feedForward();
	ASSERT_EQ(normalization->outputVolume->get(0, 0, 0), 0);
}

TEST_F(NormalizationTest, ZeroOneZeroOne) {
	Volume *inputVolume = new Volume(1, 1, 1);
	Normalization *normalization = new Normalization(inputVolume, 50);
	inputVolume->set(0, 0, 0, 0);
	normalization->feedForward();
	inputVolume->set(0, 0, 0, 1);
	normalization->feedForward();
	inputVolume->set(0, 0, 0, 0);
	normalization->feedForward();
	ASSERT_NEAR(normalization->outputVolume->get(0, 0, 0), -0.707, 0.001);
}

TEST_F(NormalizationTest, MaxEntrySize) {
	Volume *inputVolume = new Volume(1, 1, 1);
	Normalization *normalization = new Normalization(inputVolume, 1);
	inputVolume->set(0, 0, 0, 0);
	normalization->feedForward();
	inputVolume->set(0, 0, 0, 1);
	normalization->feedForward();
	inputVolume->set(0, 0, 0, 0);
	normalization->feedForward();
	ASSERT_EQ(normalization->outputVolume->get(0, 0, 0), 0);
}