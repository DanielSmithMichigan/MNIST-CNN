#include "ReluTest.h"

ReluTest::ReluTest() {
}

ReluTest::~ReluTest() {
}

void ReluTest::SetUp() {
}

TEST_F(ReluTest, Above0) {
	Volume *inputVolume = new Volume(1, 1, 1);
	inputVolume->set(0, 0, 0, 1);
	Relu *relu = new Relu(inputVolume);
	relu->feedForward();
	ASSERT_EQ(relu->outputVolume->get(0, 0, 0), 1);
}

TEST_F(ReluTest, Below0) {
	Volume *inputVolume = new Volume(1, 1, 1);
	inputVolume->set(0, 0, 0, -1);
	Relu *relu = new Relu(inputVolume);
	relu->feedForward();
	ASSERT_FLOAT_EQ(relu->outputVolume->get(0, 0, 0), -0.01);
}

TEST_F(ReluTest, Both) {
	Volume *inputVolume = new Volume(2, 2, 1);
	inputVolume->set(0, 0, 0, -1);
	inputVolume->set(1, 0, 0, -1);
	inputVolume->set(0, 1, 0, 1);
	inputVolume->set(1, 1, 0, 0);
	Relu *relu = new Relu(inputVolume);
	relu->feedForward();
	ASSERT_FLOAT_EQ(relu->outputVolume->get(0, 0, 0), -0.01);
	ASSERT_FLOAT_EQ(relu->outputVolume->get(1, 0, 0), -0.01);
	ASSERT_EQ(relu->outputVolume->get(0, 1, 0), 1);
	ASSERT_EQ(relu->outputVolume->get(1, 1, 0), 0);
}