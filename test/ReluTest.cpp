// #include "ReluTest.h"

// ReluTest::ReluTest() {
// }

// ReluTest::~ReluTest() {
// }

// void ReluTest::SetUp() {
// }

// TEST_F(ReluTest, Above0) {
// 	Volume *inputVolume = new Volume(1, 1, 1);
// 	inputVolume->set(0, 0, 0, 1);
// 	Relu *relu = new Relu(inputVolume);
// 	relu->feedForward();
// 	ASSERT_EQ(relu->outputVolume->get(0, 0, 0), 1);
// }

// TEST_F(ReluTest, Below0) {
// 	Volume *inputVolume = new Volume(1, 1, 1);
// 	inputVolume->set(0, 0, 0, -1);
// 	Relu *relu = new Relu(inputVolume);
// 	relu->feedForward();
// 	ASSERT_FLOAT_EQ(relu->outputVolume->get(0, 0, 0), -0.01);
// }

// TEST_F(ReluTest, Both) {
// 	Volume *inputVolume = new Volume(2, 2, 1);
// 	inputVolume->set(0, 0, 0, -1);
// 	inputVolume->set(1, 0, 0, -1);
// 	inputVolume->set(0, 1, 0, 1);
// 	inputVolume->set(1, 1, 0, 0);
// 	Relu *relu = new Relu(inputVolume);
// 	relu->feedForward();
// 	ASSERT_FLOAT_EQ(relu->outputVolume->get(0, 0, 0), -0.01);
// 	ASSERT_FLOAT_EQ(relu->outputVolume->get(1, 0, 0), -0.01);
// 	ASSERT_EQ(relu->outputVolume->get(0, 1, 0), 1);
// 	ASSERT_EQ(relu->outputVolume->get(1, 1, 0), 0);
// }

// TEST_F(ReluTest, BackpropogationOne) {
// 	Volume *errVsInput = new Volume(1, 1, 1);
// 	Volume *inputVolume = new Volume(1, 1, 1);
// 	inputVolume->set(0, 0, 0, 1);
// 	Relu *relu = new Relu(inputVolume);
// 	relu->errVsInput = errVsInput;
// 	relu->feedForward();
// 	relu->errVsOutput->set(0,0,0,1);
// 	relu->feedBackward();
// 	ASSERT_FLOAT_EQ(relu->outputVolume->get(0, 0, 0), 1);
// 	ASSERT_FLOAT_EQ(relu->errVsInput->get(0,0,0), 1);
// }

// TEST_F(ReluTest, BackpropogationZero) {
// 	Volume *errVsInput = new Volume(1, 1, 1);
// 	Volume *inputVolume = new Volume(1, 1, 1);
// 	inputVolume->set(0, 0, 0, 0);
// 	Relu *relu = new Relu(inputVolume);
// 	relu->errVsInput = errVsInput;
// 	relu->feedForward();
// 	relu->errVsOutput->set(0,0,0,1);
// 	relu->feedBackward();
// 	ASSERT_FLOAT_EQ(relu->outputVolume->get(0, 0, 0),0);
// 	ASSERT_FLOAT_EQ(relu->errVsInput->get(0,0,0), 1);
// }

// TEST_F(ReluTest, BackpropogationNegOne) {
// 	Volume *errVsInput = new Volume(1, 1, 1);
// 	Volume *inputVolume = new Volume(1, 1, 1);
// 	inputVolume->set(0, 0, 0, -1);
// 	Relu *relu = new Relu(inputVolume);
// 	relu->errVsInput = errVsInput;
// 	relu->feedForward();
// 	relu->errVsOutput->set(0,0,0,1);
// 	relu->feedBackward();
// 	ASSERT_FLOAT_EQ(relu->outputVolume->get(0, 0, 0),-.01);
// 	ASSERT_FLOAT_EQ(relu->errVsInput->get(0,0,0),-.01);
// }

// TEST_F(ReluTest, BackpropogationTwoByTwo) {
// 	Volume *errVsInput = new Volume(2,2,1);
// 	Volume *inputVolume = new Volume(2,2,1);
// 	inputVolume->set(0, 0, 0, -1);
// 	inputVolume->set(1, 0, 0, 0);
// 	inputVolume->set(0, 1, 0, 1);
// 	inputVolume->set(1, 1, 0, -1);
// 	Relu *relu = new Relu(inputVolume);
// 	relu->errVsInput = errVsInput;
// 	relu->feedForward();
// 	ASSERT_FLOAT_EQ(relu->outputVolume->get(0, 0, 0),-.01);
// 	ASSERT_FLOAT_EQ(relu->outputVolume->get(1, 0, 0),0);
// 	ASSERT_FLOAT_EQ(relu->outputVolume->get(0, 1, 0),1);
// 	ASSERT_FLOAT_EQ(relu->outputVolume->get(1, 1, 0),-.01);
// 	relu->errVsOutput->set(0,0,0,1);
// 	relu->errVsOutput->set(1,0,0,2);
// 	relu->errVsOutput->set(0,1,0,3);
// 	relu->errVsOutput->set(1,1,0,4);
// 	relu->feedBackward();
// 	ASSERT_FLOAT_EQ(relu->errVsInput->get(0,0,0),-.01);
// 	ASSERT_FLOAT_EQ(relu->errVsInput->get(1,0,0),2);
// 	ASSERT_FLOAT_EQ(relu->errVsInput->get(0,1,0),3);
// 	ASSERT_FLOAT_EQ(relu->errVsInput->get(1,1,0),-.04);
// }