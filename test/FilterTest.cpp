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

TEST_F(FilterTest, WeightOfOne) {
	InputLayer *inputLayer = new InputLayer(1, 1);
	inputLayer->pixelStream = new OneByOneTrainingImagesMock();
	Filter *filter = new Filter(1, 1, 1, inputLayer);
	inputLayer->feedImage();
	filter->initializeWeights();
	filter->feedForward();
	ASSERT_EQ(filter->getNode(0, 0), 1);
	ASSERT_EQ(filter->nodes.size(), 1);
}

TEST_F(FilterTest, WeightOfZero) {
	InputLayer *inputLayer = new InputLayer(1, 1);
	inputLayer->pixelStream = new OneByOneTrainingImagesMock();
	Filter *filter = new Filter(1, 1, 1, inputLayer);
	inputLayer->feedImage();
	filter->initializeWeights(0);
	filter->feedForward();
	ASSERT_EQ(filter->getNode(0, 0), 0);
	ASSERT_EQ(filter->nodes.size(), 1);
}

TEST_F(FilterTest, Convolve) {
	InputLayer *inputLayer = new InputLayer(2, 2);
	inputLayer->pixelStream = new OneByOneTrainingImagesMock();
	Filter *filter = new Filter(1, 1, 1, inputLayer);
	inputLayer->feedImage();
	filter->initializeWeights();
	filter->feedForward();
	ASSERT_EQ(filter->nodes.size(), 4);
	ASSERT_EQ(filter->getNode(0, 0), 1);
	ASSERT_EQ(filter->getNode(1, 0), 1);
	ASSERT_EQ(filter->getNode(0, 1), 1);
	ASSERT_EQ(filter->getNode(1, 1), 1);
}

TEST_F(FilterTest, StrokeTwo) {
	InputLayer *inputLayer = new InputLayer(2, 2);
	inputLayer->pixelStream = new OneByOneTrainingImagesMock();
	Filter *filter = new Filter(1, 1, 2, inputLayer);
	inputLayer->feedImage();
	filter->initializeWeights();
	filter->feedForward();
	ASSERT_EQ(filter->nodes.size(), 1);
	ASSERT_EQ(filter->getNode(0, 0), 1);
}

TEST_F(FilterTest, ThreeByThreeInput) {
	InputLayer *inputLayer = new InputLayer(3, 3);
	inputLayer->pixelStream = new OneByOneTrainingImagesMock();
	Filter *filter = new Filter(1, 1, 2, inputLayer);
	inputLayer->feedImage();
	filter->initializeWeights();
	filter->feedForward();
	ASSERT_EQ(filter->nodes.size(), 4);
	ASSERT_EQ(filter->getNode(0, 0), 1);
	ASSERT_EQ(filter->getNode(1, 0), 1);
	ASSERT_EQ(filter->getNode(0, 1), 1);
	ASSERT_EQ(filter->getNode(1, 1), 1);
}

TEST_F(FilterTest, ThreeByThreeInputTwoByTwoFilter) {
	InputLayer *inputLayer = new InputLayer(3, 3);
	inputLayer->pixelStream = new OneByOneTrainingImagesMock();
	Filter *filter = new Filter(2, 2, 1, inputLayer);
	inputLayer->feedImage();
	filter->initializeWeights();
	filter->feedForward();
	ASSERT_EQ(filter->nodes.size(), 4);
	ASSERT_EQ(filter->getNode(0, 0), 4);
	ASSERT_EQ(filter->getNode(1, 0), 4);
	ASSERT_EQ(filter->getNode(0, 1), 4);
	ASSERT_EQ(filter->getNode(1, 1), 4);
}

TEST_F(FilterTest, WebExample) {
	InputLayer *inputLayer = new InputLayer(7, 7);
	inputLayer->pixelStream = new OneByOneTrainingImagesMock();
	Filter *filter = new Filter(3, 3, 2, inputLayer);
	inputLayer->initialize(0);
	inputLayer->setNode(2, 1, 2);
	inputLayer->setNode(3, 1, 1);
	inputLayer->setNode(4, 1, 2);
	inputLayer->setNode(5, 1, 1);
	inputLayer->setNode(1, 2, 1);
	inputLayer->setNode(4, 2, 1);
	inputLayer->setNode(5, 2, 1);
	inputLayer->setNode(2, 3, 2);
	inputLayer->setNode(3, 3, 1);
	inputLayer->setNode(4, 3, 2);
	inputLayer->setNode(5, 3, 2);
	inputLayer->setNode(3, 4, 1);
	inputLayer->setNode(1, 5, 1);
	inputLayer->setNode(3, 5, 2);
	inputLayer->setNode(4, 5, 2);
	filter->initializeWeights(0);
	filter->setWeight(0, 0, -1);
	filter->setWeight(2, 0, -1);
	filter->setWeight(0, 1, 1);
	filter->setWeight(1, 1, 1);
	filter->setWeight(2, 1, -1);
	filter->setWeight(0, 2, 1);
	filter->feedForward();
	ASSERT_EQ(filter->nodes.size(), 9);
	ASSERT_EQ(filter->getNode(0, 0), -2);
	ASSERT_EQ(filter->getNode(1, 0), 2 + 1 + -2);
	ASSERT_EQ(filter->getNode(2, 0), 2 + 1 + 1);
	ASSERT_EQ(filter->getNode(0, 1), -2);
	ASSERT_EQ(filter->getNode(1, 1), -1 + 2 + 1 + -2);
	ASSERT_EQ(filter->getNode(2, 1), -1 + 2 + 2);
	ASSERT_EQ(filter->getNode(0, 2), 1);
	ASSERT_EQ(filter->getNode(1, 2), 2 + -2);
	ASSERT_EQ(filter->getNode(2, 2), 2);
}