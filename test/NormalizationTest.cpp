#include "NormalizationTest.h"

NormalizationTest::NormalizationTest() {
}

NormalizationTest::~NormalizationTest() {
}

void NormalizationTest::SetUp() {
}

TEST_F(NormalizationTest, FirstInput) {
	Layer *input = new Layer(1, 1);
	input->nodes.resize(1);
	input->setNode(0, 0, 1);
	Normalization *normalization = new Normalization(1, 1, input);
	normalization->feedForward();
	ASSERT_EQ(normalization->getNode(0, 0), 0);
}

TEST_F(NormalizationTest, TwoEqualInputs) {
	Layer *input = new Layer(1, 1);
	input->nodes.resize(1);
	input->setNode(0, 0, 1);
	Normalization *normalization = new Normalization(1, 1, input);
	normalization->feedForward();
	normalization->feedForward();
	ASSERT_EQ(normalization->getNode(0, 0), 0);
}

TEST_F(NormalizationTest, ZeroOneZeroOne) {
	Layer *input = new Layer(1, 1);
	input->nodes.resize(1);
	Normalization *normalization = new Normalization(1, 1, input);
	input->setNode(0, 0, 0);
	normalization->feedForward();
	input->setNode(0, 0, 1);
	normalization->feedForward();
	input->setNode(0, 0, 0);
	normalization->feedForward();
	ASSERT_NEAR(normalization->getNode(0, 0), -0.707, 0.001);
}