#include "IntegrationTest.h"

IntegrationTest::IntegrationTest() {
}

IntegrationTest::~IntegrationTest() {
}

void IntegrationTest::SetUp() {
}

TEST_F(IntegrationTest, WebExample) {
	Volume *inputVolume = new Volume(2, 1, 1);
	FullyConnected *f0 = new FullyConnected(2, inputVolume);
	f0->weights->set(0,0,0,0,.15);
	f0->weights->set(1,0,0,0,.2);
	f0->weights->set(0,0,0,1,.25);
	f0->weights->set(1,0,0,1,.3);
	f0->biases[0] = .35;
	f0->biases[1] = .35;
	Sigmoid *s0 = new Sigmoid(f0->outputVolume);
	FullyConnected *f1 = new FullyConnected(2, s0->outputVolume);
	f1->weights->set(0,0,0,0,.4);
	f1->weights->set(1,0,0,0,.45);
	f1->weights->set(0,0,0,1,.5);
	f1->weights->set(1,0,0,1,.55);
	f1->biases[0] = .6;
	f1->biases[1] = .6;
	Sigmoid *s1 = new Sigmoid(f1->outputVolume);
	f0->errVsInput = new Volume(inputVolume->width, inputVolume->height, inputVolume->depth);
	s0->errVsInput = f0->errVsOutput; 
	f1->errVsInput = s0->errVsOutput;
	s1->errVsInput = f1->errVsOutput;
	inputVolume->set(0,0,0,.05);
	inputVolume->set(1,0,0,.10);
	f0->feedForward();
	s0->feedForward();
	f1->feedForward();
	s1->feedForward();
	ASSERT_FLOAT_EQ(s0->outputVolume->get(0,0,0), 0.59327);
	ASSERT_FLOAT_EQ(s0->outputVolume->get(1,0,0), 0.59688437);
	ASSERT_FLOAT_EQ(s1->outputVolume->get(0,0,0), 0.75136507);
	ASSERT_FLOAT_EQ(s1->outputVolume->get(1,0,0), 0.77292848);
	s1->errVsOutput->set(0,0,0,s1->outputVolume->get(0,0,0) - 0.01);
	s1->errVsOutput->set(1,0,0,s1->outputVolume->get(1,0,0) - 0.99);
	s1->feedBackward();
	f1->feedBackward();
	s0->feedBackward();
	f0->feedBackward();
	ASSERT_FLOAT_EQ(f1->weights->get(0,0,0,0), 0.35891649);
	ASSERT_FLOAT_EQ(f1->weights->get(1,0,0,0), 0.40866616);
	ASSERT_FLOAT_EQ(f1->biases[0], .6 - .5 * 0.13849856185);
	ASSERT_FLOAT_EQ(f1->biases[1], .6 - 0.217071535 * 0.17551005299 * -.5);
	ASSERT_FLOAT_EQ(f0->weights->get(0,0,0,0), .149780716);
}