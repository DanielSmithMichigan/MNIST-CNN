#include "FilterTest.h"

FilterTest::FilterTest() {
}

FilterTest::~FilterTest() {
}

void FilterTest::SetUp() {
}

// TEST_F(FilterTest, FilterWithPadding) {
// 	Layer *inputLayer = new Layer();
// 	inputLayer->outputVolume = new Volume(3, 3, 1);
// 	Padding *padding = new Padding(1, inputVolume);
// 	Filter *filter = new Filter(3, 3, 1, padding->outputVolume);
// 	filter->weights->initialize(1);
// 	inputVolume->initialize(2);
// 	padding->feedForward();
// 	filter->feedForward();
// 	ASSERT_EQ(filter->outputVolume->get(0, 0, 0), 8);
// 	ASSERT_EQ(filter->outputVolume->get(1, 0, 0), 12);
// 	ASSERT_EQ(filter->outputVolume->get(2, 0, 0), 8);
// 	ASSERT_EQ(filter->outputVolume->get(0, 1, 0), 12);
// 	ASSERT_EQ(filter->outputVolume->get(1, 1, 0), 18);
// 	ASSERT_EQ(filter->outputVolume->get(2, 1, 0), 12);
// 	ASSERT_EQ(filter->outputVolume->get(0, 2, 0), 8);
// 	ASSERT_EQ(filter->outputVolume->get(1, 2, 0), 12);
// 	ASSERT_EQ(filter->outputVolume->get(2, 2, 0), 8);
// }

TEST_F(FilterTest, WeightOfOne) {
	Layer *inputLayer = new Layer();
	inputLayer->outputVolume = new Volume(1, 1, 1);
	inputLayer->outputVolume->initialize(1);
	Filter *filter = new Filter(1, 1, 1, inputLayer);
	filter->weights->initialize(1);
	filter->feedForward();
	ASSERT_EQ(filter->outputVolume->get(0, 0, 0), 1);
}

TEST_F(FilterTest, TwoByTwoByTwo) {
	Layer *inputLayer = new Layer();
	inputLayer->outputVolume = new Volume(2, 2, 2);
	inputLayer->outputVolume->initialize(0);
	inputLayer->outputVolume->set(0, 0, 0, 1);
	inputLayer->outputVolume->set(1, 1, 0, 1);
	inputLayer->outputVolume->set(1, 0, 1, 1);
	inputLayer->outputVolume->set(1, 0, 1, 1);
	Filter *filter = new Filter(2, 2, 1, inputLayer);
	filter->weights->initialize(0);
	filter->weights->set(0, 0, 0, 1);
	filter->weights->set(1, 0, 0, 1);
	filter->weights->set(0, 1, 0, 1);
	filter->weights->set(1, 1, 0, 1);
	filter->feedForward();
	ASSERT_EQ(filter->outputVolume->get(0, 0, 0), 2);
}

TEST_F(FilterTest, OneByOneByTwoFilter) {
	Layer *inputLayer = new Layer();
	inputLayer->outputVolume = new Volume(2, 2, 2);
	inputLayer->outputVolume->initialize(0);
	inputLayer->outputVolume->set(0, 0, 0, 1);
	inputLayer->outputVolume->set(1, 1, 0, 1);
	inputLayer->outputVolume->set(1, 0, 1, 1);
	inputLayer->outputVolume->set(1, 0, 1, 1);
	Filter *filter = new Filter(1, 1, 1, inputLayer);
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
	Layer *inputLayer = new Layer();
	inputLayer->outputVolume = new Volume(1, 1, 1);
	inputLayer->outputVolume->initialize(1);
	Filter *filter = new Filter(1, 1, 1, inputLayer);
	filter->weights->initialize(0);
	filter->feedForward();
	ASSERT_EQ(filter->outputVolume->get(0, 0, 0), 0);
}

TEST_F(FilterTest, Convolve) {
	Layer *inputLayer = new Layer();
	inputLayer->outputVolume = new Volume(2, 2, 1);
	inputLayer->outputVolume->initialize(1);
	Filter *filter = new Filter(1, 1, 1, inputLayer);
	filter->weights->initialize(1);
	filter->feedForward();
	ASSERT_EQ(filter->outputVolume->get(0, 0, 0), 1);
	ASSERT_EQ(filter->outputVolume->get(1, 0, 0), 1);
	ASSERT_EQ(filter->outputVolume->get(0, 1, 0), 1);
	ASSERT_EQ(filter->outputVolume->get(1, 1, 0), 1);
}

TEST_F(FilterTest, StrokeTwo) {
	Layer *inputLayer = new Layer();
	inputLayer->outputVolume = new Volume(2, 2, 1);
	inputLayer->outputVolume->initialize(1);
	Filter *filter = new Filter(1, 1, 2, inputLayer);
	filter->weights->initialize(1);
	filter->feedForward();
	ASSERT_EQ(filter->outputVolume->get(0, 0, 0), 1);
}

TEST_F(FilterTest, ThreeByThreeInput) {
	Layer *inputLayer = new Layer();
	inputLayer->outputVolume = new Volume(3, 3, 1);
	inputLayer->outputVolume->initialize(1);
	Filter *filter = new Filter(1, 1, 2, inputLayer);
	filter->weights->initialize(1);
	filter->feedForward();
	ASSERT_EQ(filter->outputVolume->get(0, 0, 0), 1);
	ASSERT_EQ(filter->outputVolume->get(1, 0, 0), 1);
	ASSERT_EQ(filter->outputVolume->get(0, 1, 0), 1);
	ASSERT_EQ(filter->outputVolume->get(1, 1, 0), 1);
}

TEST_F(FilterTest, ThreeByThreeInputTwoByTwoFilter) {
	Layer *inputLayer = new Layer();
	inputLayer->outputVolume = new Volume(3, 3, 1);
	inputLayer->outputVolume->initialize(1);
	Filter *filter = new Filter(2, 2, 1, inputLayer);
	filter->weights->initialize(1);
	filter->feedForward();
	ASSERT_EQ(filter->outputVolume->get(0, 0, 0), 4);
	ASSERT_EQ(filter->outputVolume->get(1, 0, 0), 4);
	ASSERT_EQ(filter->outputVolume->get(0, 1, 0), 4);
	ASSERT_EQ(filter->outputVolume->get(1, 1, 0), 4);
}

TEST_F(FilterTest, WebExample) {
	Layer *inputLayer = new Layer();
	inputLayer->outputVolume = new Volume(7, 7, 1);
	inputLayer->outputVolume->initialize(0);
	Filter *filter = new Filter(3, 3, 2, inputLayer);
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

TEST_F(FilterTest, SimplestBackpropogation) {
	Layer *inputLayer = new Layer();
	inputLayer->errVsOutput = new Volume(1, 1, 1);
	inputLayer->outputVolume = new Volume(1, 1, 1);
	inputLayer->outputVolume->initialize(1);
	Filter *filter = new Filter(1, 1, 1, inputLayer);
	filter->weights->initialize(1);
	filter->feedForward();
	ASSERT_EQ(filter->outputVolume->get(0, 0, 0), 1);
	filter->errVsOutput->set(0,0,0,1);
	filter->feedBackward();
	ASSERT_FLOAT_EQ(filter->errVsInput->get(0,0,0), 1);
	ASSERT_FLOAT_EQ(filter->weights->get(0,0,0), 1 - __LEARNING_RATE);
}

TEST_F(FilterTest, SimplestBackpropogationWeightZero) {
	Layer *inputLayer = new Layer();
	inputLayer->errVsOutput = new Volume(1, 1, 1);
	inputLayer->outputVolume = new Volume(1, 1, 1);
	inputLayer->outputVolume->initialize(1);
	Filter *filter = new Filter(1, 1, 1, inputLayer);
	filter->weights->initialize(0);
	filter->feedForward();
	ASSERT_FLOAT_EQ(filter->outputVolume->get(0, 0, 0), 0);
	filter->errVsOutput->set(0,0,0,1);
	filter->feedBackward();
	ASSERT_FLOAT_EQ(filter->errVsInput->get(0,0,0), 0);
	ASSERT_FLOAT_EQ(filter->weights->get(0,0,0), -__LEARNING_RATE);
}

TEST_F(FilterTest, SimplestBackpropogationWeightZero_Two) {
	Layer *inputLayer = new Layer();
	inputLayer->errVsOutput = new Volume(1, 1, 1);
	inputLayer->outputVolume = new Volume(1, 1, 1);
	inputLayer->outputVolume->initialize(1);
	Filter *filter = new Filter(1, 1, 1, inputLayer);
	filter->weights->initialize(0);
	filter->feedForward();
	ASSERT_FLOAT_EQ(filter->outputVolume->get(0, 0, 0), 0);
	filter->errVsOutput->set(0,0,0,.25);
	filter->feedBackward();
	ASSERT_FLOAT_EQ(filter->errVsInput->get(0,0,0), 0);
	ASSERT_FLOAT_EQ(filter->weights->get(0,0,0), -__LEARNING_RATE * .25);
}

TEST_F(FilterTest, BackpropogationConvolve) {
	Layer *inputLayer = new Layer();
	inputLayer->errVsOutput = new Volume(2, 2, 2);
	inputLayer->outputVolume = new Volume(2, 2, 2);
	inputLayer->outputVolume->set(0,0,0,1);
	inputLayer->outputVolume->set(1,0,0,2);
	inputLayer->outputVolume->set(0,1,0,3);
	inputLayer->outputVolume->set(1,1,0,4);
	inputLayer->outputVolume->set(0,0,1,5);
	inputLayer->outputVolume->set(1,0,1,6);
	inputLayer->outputVolume->set(0,1,1,7);
	inputLayer->outputVolume->set(1,1,1,8);
	Volume *errVsInput = new Volume(2, 2, 2);
	Filter *filter = new Filter(1, 1, 1, inputLayer);
	filter->errVsInput = errVsInput;
	filter->weights->initialize(1);
	filter->feedForward();
	ASSERT_EQ(filter->outputVolume->get(0, 0, 0), 6);
	ASSERT_EQ(filter->outputVolume->get(1, 0, 0), 8);
	ASSERT_EQ(filter->outputVolume->get(0, 1, 0), 10);
	ASSERT_EQ(filter->outputVolume->get(1, 1, 0), 12);
	filter->errVsOutput->set(0, 0, 0, 1);
	filter->errVsOutput->set(1, 0, 0, 2);
	filter->errVsOutput->set(0, 1, 0, 3);
	filter->errVsOutput->set(1, 1, 0, 4);
	filter->feedBackward();
	ASSERT_EQ(filter->errVsInput->get(0,0,0), 1);
	ASSERT_EQ(filter->errVsInput->get(1,0,0), 2);
	ASSERT_EQ(filter->errVsInput->get(0,1,0), 3);
	ASSERT_EQ(filter->errVsInput->get(1,1,0), 4);
	ASSERT_EQ(filter->errVsInput->get(0,0,1), 1);
	ASSERT_EQ(filter->errVsInput->get(1,0,1), 2);
	ASSERT_EQ(filter->errVsInput->get(0,1,1), 3);
	ASSERT_EQ(filter->errVsInput->get(1,1,1), 4);
}

TEST_F(FilterTest, BackpropogationConvolve_Two) {
	Layer *inputLayer = new Layer();
	inputLayer->errVsOutput = new Volume(2, 2, 2);
	inputLayer->outputVolume = new Volume(2, 2, 2);
	inputLayer->outputVolume->set(0,0,0,1);
	inputLayer->outputVolume->set(1,0,0,2);
	inputLayer->outputVolume->set(0,1,0,3);
	inputLayer->outputVolume->set(1,1,0,4);
	inputLayer->outputVolume->set(0,0,1,5);
	inputLayer->outputVolume->set(1,0,1,6);
	inputLayer->outputVolume->set(0,1,1,7);
	inputLayer->outputVolume->set(1,1,1,8);
	Volume *errVsInput = new Volume(2, 2, 2);
	Filter *filter = new Filter(2, 2, 1, inputLayer);
	filter->errVsInput = errVsInput;
	filter->weights->set(0, 0, 0, 1);
	filter->weights->set(1, 0, 0, 2);
	filter->weights->set(0, 1, 0, 3);
	filter->weights->set(1, 1, 0, 4);
	filter->weights->set(0, 0, 1, 1);
	filter->weights->set(1, 0, 1, 2);
	filter->weights->set(0, 1, 1, 3);
	filter->weights->set(1, 1, 1, 4);
	filter->feedForward();
	ASSERT_FLOAT_EQ(filter->outputVolume->get(0, 0, 0), 1 + 4 + 9 + 16 + 5 + 12 + 21 + 32);
	filter->errVsOutput->set(0, 0, 0, 5);
	filter->feedBackward();
	ASSERT_FLOAT_EQ(filter->errVsInput->get(0,0,0), 5);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(1,0,0), 10);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(0,1,0), 15);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(1,1,0), 20);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(0,0,1), 5);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(1,0,1), 10);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(0,1,1), 15);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(1,1,1), 20);
	ASSERT_FLOAT_EQ(filter->weights->get(0,0,0), 1 * 5 * -__LEARNING_RATE + 1);
	ASSERT_FLOAT_EQ(filter->weights->get(1,0,0), 2 * 5 * -__LEARNING_RATE + 2);
	ASSERT_FLOAT_EQ(filter->weights->get(0,1,0), 3 * 5 * -__LEARNING_RATE + 3);
	ASSERT_FLOAT_EQ(filter->weights->get(1,1,0), 4 * 5 * -__LEARNING_RATE + 4);
	ASSERT_FLOAT_EQ(filter->weights->get(0,0,1), 5 * 5 * -__LEARNING_RATE + 1);
	ASSERT_FLOAT_EQ(filter->weights->get(1,0,1), 6 * 5 * -__LEARNING_RATE + 2);
	ASSERT_FLOAT_EQ(filter->weights->get(0,1,1), 7 * 5 * -__LEARNING_RATE + 3);
	ASSERT_FLOAT_EQ(filter->weights->get(1,1,1), 8 * 5 * -__LEARNING_RATE + 4);
}

TEST_F(FilterTest, BackpropogationConvolve_Multi) {
	Layer *inputLayer = new Layer();
	inputLayer->errVsOutput = new Volume(3, 3, 2);
	inputLayer->outputVolume = new Volume(3, 3, 2);
	inputLayer->outputVolume->set(0,0,0,1);
	inputLayer->outputVolume->set(1,0,0,2);
	inputLayer->outputVolume->set(2,0,0,3);
	inputLayer->outputVolume->set(0,1,0,4);
	inputLayer->outputVolume->set(1,1,0,5);
	inputLayer->outputVolume->set(2,1,0,6);
	inputLayer->outputVolume->set(0,2,0,7);
	inputLayer->outputVolume->set(1,2,0,8);
	inputLayer->outputVolume->set(2,2,0,9);
	inputLayer->outputVolume->set(0,0,1,10);
	inputLayer->outputVolume->set(1,0,1,11);
	inputLayer->outputVolume->set(2,0,1,12);
	inputLayer->outputVolume->set(0,1,1,13);
	inputLayer->outputVolume->set(1,1,1,14);
	inputLayer->outputVolume->set(2,1,1,15);
	inputLayer->outputVolume->set(0,2,1,16);
	inputLayer->outputVolume->set(1,2,1,17);
	inputLayer->outputVolume->set(2,2,1,18);
	Volume *errVsInput = new Volume(3, 3, 2);
	Filter *filter = new Filter(2, 2, 1, inputLayer);
	filter->errVsInput = errVsInput;
	filter->weights->set(0, 0, 0, 1);
	filter->weights->set(1, 0, 0, 2);
	filter->weights->set(0, 1, 0, 3);
	filter->weights->set(1, 1, 0, 4);
	filter->weights->set(0, 0, 1, 5);
	filter->weights->set(1, 0, 1, 6);
	filter->weights->set(0, 1, 1, 7);
	filter->weights->set(1, 1, 1, 8);
	filter->feedForward();
	ASSERT_FLOAT_EQ(filter->outputVolume->get(0, 0, 0), 1 + 4 + 12 + 20 + 50 + 66 + 13 * 7 + 14 * 8);
	ASSERT_FLOAT_EQ(filter->outputVolume->get(1, 0, 0), 1 * 2 + 2 * 3 + 3 * 5 + 4 * 6 + 5 * 11 + 6 * 12 + 7 * 14 + 8 * 15);
	ASSERT_FLOAT_EQ(filter->outputVolume->get(0, 1, 0), 1 * 4 + 2 * 5 + 3 * 7 + 4 * 8 + 5 * 13 + 6 * 14 + 7 * 16 + 8 * 17);
	ASSERT_FLOAT_EQ(filter->outputVolume->get(1, 1, 0), 1 * 5 + 2 * 6 + 3 * 8 + 4 * 9 + 5 * 14 + 6 * 15 + 7 * 17 + 8 * 18);
	filter->errVsOutput->set(0, 0, 0, 1);
	filter->errVsOutput->set(1, 0, 0, 2);
	filter->errVsOutput->set(0, 1, 0, 3);
	filter->errVsOutput->set(1, 1, 0, 4);
	filter->feedBackward();
	ASSERT_FLOAT_EQ(filter->errVsInput->get(0,0,0), 1);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(1,0,0), 1 * 2 + 2 * 1);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(2,0,0), 2 * 2);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(0,1,0), 3 * 1 + 1 * 3);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(1,1,0), 1 * 4 + 2 * 3 + 3 * 2 + 4 * 1);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(2,1,0), 2 * 4 + 4 * 2);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(0,2,0), 3 * 3);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(1,2,0), 3 * 4 + 4 * 3);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(2,2,0), 4 * 4);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(0,0,1), 1 * 5);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(1,0,1), 1 * 6 + 2 * 5);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(2,0,1), 2 * 6);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(0,1,1), 1 * 7 + 3 * 5);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(1,1,1), 1 * 8 + 2 * 7 + 3 * 6 + 4 * 5);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(2,1,1), 2 * 8 + 4 * 6);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(0,2,1), 3 * 7);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(1,2,1), 3 * 8 + 4 * 7);
	ASSERT_FLOAT_EQ(filter->errVsInput->get(2,2,1), 4 * 8);
	ASSERT_FLOAT_EQ(filter->weights->get(0,0,0), (1 * 1 + 2 * 2 + 4 * 3 + 5 * 4) * -__LEARNING_RATE + 1);
	ASSERT_FLOAT_EQ(filter->weights->get(1,0,0), (2 * 1 + 3 * 2 + 5 * 3 + 6 * 4) * -__LEARNING_RATE + 2);
	ASSERT_FLOAT_EQ(filter->weights->get(0,1,0), (4 * 1 + 5 * 2 + 7 * 3 + 8 * 4) * -__LEARNING_RATE + 3);
	ASSERT_FLOAT_EQ(filter->weights->get(1,1,0), (5 * 1 + 6 * 2 + 8 * 3 + 9 * 4) * -__LEARNING_RATE + 4);
	ASSERT_FLOAT_EQ(filter->weights->get(0,0,1), (10 * 1 + 11 * 2 + 13 * 3 + 14 * 4) * -__LEARNING_RATE + 5);
	ASSERT_FLOAT_EQ(filter->weights->get(1,0,1), (11 * 1 + 12 * 2 + 14 * 3 + 15 * 4) * -__LEARNING_RATE + 6);
	ASSERT_FLOAT_EQ(filter->weights->get(0,1,1), (13 * 1 + 14 * 2 + 16 * 3 + 17 * 4) * -__LEARNING_RATE + 7);
	ASSERT_FLOAT_EQ(filter->weights->get(1,1,1), (14 * 1 + 15 * 2 + 17 * 3 + 18 * 4) * -__LEARNING_RATE + 8);
}