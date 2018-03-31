#include "FilterTest.h"

FilterTest::FilterTest() {
}

FilterTest::~FilterTest() {
}

void FilterTest::SetUp() {
}

class OneByOneTrainingImagesMock : public PixelStream {
	public:
		uint8_t get() {return 1;}
};

// int filterWidth, int filterHeight, int inputDepth, int stride, Volume *inputVolume, int inputIndex

TEST_F(FilterTest, WeightOfOne) {
	InputLayer *inputLayer = new InputLayer(1, 1);
	inputLayer->pixelStream = new OneByOneTrainingImagesMock();
	Filter *filter = new Filter(1, 1, 1, inputLayer->outputVolume, 0);
	inputLayer->feedForward();
	filter->feedForward();
	ASSERT_EQ(filter->outputVolume->get(0, 0, 0), 1);
}

TEST_F(FilterTest, TwoByTwoByTwo) {
	Volume *inputVolume = new Volume(2, 2, 2);
	inputVolume->set(0, 0, 0, 1);
	inputVolume->set(1, 1, 0, 1);
	inputVolume->set(1, 0, 1, 1);
	inputVolume->set(1, 0, 1, 1);
	Filter *filter = new Filter(2, 2, 1, inputVolume, 0);
	filter->weights->initialize(0);
	filter->weights->set(0, 0, 0, 1);
	filter->weights->set(1, 0, 0, 1);
	filter->weights->set(0, 1, 0, 1);
	filter->weights->set(1, 1, 0, 1);
	filter->feedForward();
	ASSERT_EQ(filter->outputVolume->get(0, 0, 0), 2);
}

TEST_F(FilterTest, OneByOneByTwoFilter) {
	Volume *inputVolume = new Volume(2, 2, 2);
	inputVolume->set(0, 0, 0, 1);
	inputVolume->set(1, 1, 0, 1);
	inputVolume->set(1, 0, 1, 1);
	inputVolume->set(1, 0, 1, 1);
	Filter *filter = new Filter(1, 1, 1, inputVolume, 0);
	filter->weights->initialize(0);
	filter->weights->set(0, 0, 0, 1);
	filter->weights->set(0, 0, 1, 0);
	filter->feedForward();
	ASSERT_EQ(filter->outputVolume->get(0, 0, 0), 1);
	ASSERT_EQ(filter->outputVolume->get(1, 0, 0), 0);
	ASSERT_EQ(filter->outputVolume->get(0, 1, 0), 0);
	ASSERT_EQ(filter->outputVolume->get(1, 1, 0), 1);
	ASSERT_NEAR(filter->outputVolume->get(0, 0, 1), 0, 0.00001);
	ASSERT_NEAR(filter->outputVolume->get(1, 0, 1), 0, 0.00001);
	ASSERT_NEAR(filter->outputVolume->get(0, 1, 1), 0, 0.00001);
	ASSERT_NEAR(filter->outputVolume->get(1, 1, 1), 0, 0.00001);
}

TEST_F(FilterTest, WeightOfZero) {
	InputLayer *inputLayer = new InputLayer(1, 1);
	inputLayer->pixelStream = new OneByOneTrainingImagesMock();
	Filter *filter = new Filter(1, 1, 1, inputLayer->outputVolume, 0);
	inputLayer->feedForward();
	filter->weights->initialize(0);
	filter->feedForward();
	ASSERT_EQ(filter->outputVolume->get(0, 0, 0), 0);
}

TEST_F(FilterTest, Convolve) {
	InputLayer *inputLayer = new InputLayer(2, 2);
	inputLayer->pixelStream = new OneByOneTrainingImagesMock();
	Filter *filter = new Filter(1, 1, 1, inputLayer->outputVolume, 0);
	inputLayer->feedForward();
	filter->feedForward();
	ASSERT_EQ(filter->outputVolume->get(0, 0, 0), 1);
	ASSERT_EQ(filter->outputVolume->get(1, 0, 0), 1);
	ASSERT_EQ(filter->outputVolume->get(0, 1, 0), 1);
	ASSERT_EQ(filter->outputVolume->get(1, 1, 0), 1);
}

TEST_F(FilterTest, StrokeTwo) {
	InputLayer *inputLayer = new InputLayer(2, 2);
	inputLayer->pixelStream = new OneByOneTrainingImagesMock();
	Filter *filter = new Filter(1, 1, 2, inputLayer->outputVolume, 0);
	inputLayer->feedForward();
	filter->feedForward();
	ASSERT_EQ(filter->outputVolume->get(0, 0, 0), 1);
}

TEST_F(FilterTest, ThreeByThreeInput) {
	InputLayer *inputLayer = new InputLayer(3, 3);
	inputLayer->pixelStream = new OneByOneTrainingImagesMock();
	Filter *filter = new Filter(1, 1, 2, inputLayer->outputVolume, 0);
	inputLayer->feedForward();
	filter->feedForward();
	ASSERT_EQ(filter->outputVolume->get(0, 0, 0), 1);
	ASSERT_EQ(filter->outputVolume->get(1, 0, 0), 1);
	ASSERT_EQ(filter->outputVolume->get(0, 1, 0), 1);
	ASSERT_EQ(filter->outputVolume->get(1, 1, 0), 1);
}

TEST_F(FilterTest, ThreeByThreeInputTwoByTwoFilter) {
	InputLayer *inputLayer = new InputLayer(3, 3);
	inputLayer->pixelStream = new OneByOneTrainingImagesMock();
	Filter *filter = new Filter(2, 2, 1, inputLayer->outputVolume, 0);
	inputLayer->feedForward();
	filter->feedForward();
	ASSERT_EQ(filter->outputVolume->get(0, 0, 0), 4);
	ASSERT_EQ(filter->outputVolume->get(1, 0, 0), 4);
	ASSERT_EQ(filter->outputVolume->get(0, 1, 0), 4);
	ASSERT_EQ(filter->outputVolume->get(1, 1, 0), 4);
}

TEST_F(FilterTest, WebExample) {
	InputLayer *inputLayer = new InputLayer(7, 7);
	Filter *filter = new Filter(3, 3, 2, inputLayer->outputVolume, 0);
	inputLayer->outputVolume->set(2, 1, 0, 2);
	inputLayer->outputVolume->set(3, 1, 0, 1);
	inputLayer->outputVolume->set(4, 1, 0, 2);
	inputLayer->outputVolume->set(5, 1, 0, 1);
	inputLayer->outputVolume->set(1, 2, 0, 1);
	inputLayer->outputVolume->set(4, 2, 0, 1);
	inputLayer->outputVolume->set(5, 2, 0, 1);
	inputLayer->outputVolume->set(2, 3, 0, 2);
	inputLayer->outputVolume->set(3, 3, 0, 1);
	inputLayer->outputVolume->set(4, 3, 0, 2);
	inputLayer->outputVolume->set(5, 3, 0, 2);
	inputLayer->outputVolume->set(3, 4, 0, 1);
	inputLayer->outputVolume->set(1, 5, 0, 1);
	inputLayer->outputVolume->set(3, 5, 0, 2);
	inputLayer->outputVolume->set(4, 5, 0, 2);
	filter->weights->initialize(0);
	filter->weights->set(0, 0, 0, -1);
	filter->weights->set(2, 0, 0, -1);
	filter->weights->set(0, 1, 0, 1);
	filter->weights->set(1, 1, 0, 1);
	filter->weights->set(2, 1, 0, -1);
	filter->weights->set(0, 2, 0, 1);
	filter->feedForward();
	ASSERT_EQ(filter->outputVolume->get(0, 0, 0), -2);
	ASSERT_EQ(filter->outputVolume->get(1, 0, 0), 2 + 1 + -2);
	ASSERT_EQ(filter->outputVolume->get(2, 0, 0), 2 + 1 + 1);
	ASSERT_EQ(filter->outputVolume->get(0, 1, 0), -2);
	ASSERT_EQ(filter->outputVolume->get(1, 1, 0), -1 + 2 + 1 + -2);
	ASSERT_EQ(filter->outputVolume->get(2, 1, 0), -1 + 2 + 2);
	ASSERT_EQ(filter->outputVolume->get(0, 2, 0), 1);
	ASSERT_EQ(filter->outputVolume->get(1, 2, 0), 2 + -2);
	ASSERT_EQ(filter->outputVolume->get(2, 2, 0), 2);
}