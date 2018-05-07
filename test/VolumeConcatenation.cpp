// #include "VolumeConcatenation.h"

// VolumeConcatenationTest::VolumeConcatenationTest() {
// }

// VolumeConcatenationTest::~VolumeConcatenationTest() {
// }

// void VolumeConcatenationTest::SetUp() {
// }

// TEST_F(VolumeConcatenationTest, OneVolume) {
// 	Volume *inputVolume = new Volume(1, 1, 1);
// 	inputVolume->set(0, 0, 0, 1);
// 	vector<Volume *> inputVolumes;
// 	inputVolumes.push_back(inputVolume);
// 	VolumeConcatenation *v0 = new VolumeConcatenation(inputVolumes);
// 	Volume *errVsInput = new Volume(1, 1, 1);
// 	vector<Volume *> errVsInputs;
// 	errVsInputs.push_back(errVsInput);
// 	v0->errVsInputs = errVsInputs;
// 	v0->feedForward();
// 	ASSERT_EQ(v0->outputVolume->get(0, 0, 0), 1);
// 	v0->errVsOutput->set(0,0,0, 1);
// 	v0->feedBackward();
// 	ASSERT_EQ(v0->errVsInputs[0]->get(0,0,0), 1);
// }

// TEST_F(VolumeConcatenationTest, MultiVolume) {
// 	Volume *i0 = new Volume(2, 2, 2);
// 	i0->set(0, 0, 0, 1);
// 	i0->set(1, 0, 0, 2);
// 	i0->set(0, 1, 0, 3);
// 	i0->set(1, 1, 0, 4);
// 	i0->set(0, 0, 1, 5);
// 	i0->set(1, 0, 1, 6);
// 	i0->set(0, 1, 1, 7);
// 	i0->set(1, 1, 1, 8);
// 	Volume *i1 = new Volume(2, 2, 2);
// 	i1->set(0, 0, 0, 8);
// 	i1->set(1, 0, 0, 7);
// 	i1->set(0, 1, 0, 6);
// 	i1->set(1, 1, 0, 5);
// 	i1->set(0, 0, 1, 4);
// 	i1->set(1, 0, 1, 3);
// 	i1->set(0, 1, 1, 2);
// 	i1->set(1, 1, 1, 1);
// 	vector<Volume *> inputVolumes;
// 	inputVolumes.push_back(i0);
// 	inputVolumes.push_back(i1);
// 	VolumeConcatenation *v0 = new VolumeConcatenation(inputVolumes);
// 	Volume *errVsInputv1 = new Volume(2, 2, 2);
// 	Volume *errVsInputv2 = new Volume(2, 2, 2);
// 	vector<Volume *> errVsInputs;
// 	errVsInputs.push_back(errVsInputv1);
// 	errVsInputs.push_back(errVsInputv2);
// 	v0->errVsInputs = errVsInputs;
// 	v0->feedForward();
// 	ASSERT_EQ(v0->outputVolume->get(0, 0, 0), 1);
// 	ASSERT_EQ(v0->outputVolume->get(1, 0, 0), 2);
// 	ASSERT_EQ(v0->outputVolume->get(0, 1, 0), 3);
// 	ASSERT_EQ(v0->outputVolume->get(1, 1, 0), 4);
// 	ASSERT_EQ(v0->outputVolume->get(0, 0, 1), 5);
// 	ASSERT_EQ(v0->outputVolume->get(1, 0, 1), 6);
// 	ASSERT_EQ(v0->outputVolume->get(0, 1, 1), 7);
// 	ASSERT_EQ(v0->outputVolume->get(1, 1, 1), 8);
// 	ASSERT_EQ(v0->outputVolume->get(0, 0, 2), 8);
// 	ASSERT_EQ(v0->outputVolume->get(1, 0, 2), 7);
// 	ASSERT_EQ(v0->outputVolume->get(0, 1, 2), 6);
// 	ASSERT_EQ(v0->outputVolume->get(1, 1, 2), 5);
// 	ASSERT_EQ(v0->outputVolume->get(0, 0, 3), 4);
// 	ASSERT_EQ(v0->outputVolume->get(1, 0, 3), 3);
// 	ASSERT_EQ(v0->outputVolume->get(0, 1, 3), 2);
// 	ASSERT_EQ(v0->outputVolume->get(1, 1, 3), 1);
// 	v0->errVsOutput->set(0, 0, 0, 1);
// 	v0->errVsOutput->set(1, 0, 0, 2);
// 	v0->errVsOutput->set(0, 1, 0, 3);
// 	v0->errVsOutput->set(1, 1, 0, 4);
// 	v0->errVsOutput->set(0, 0, 1, 5);
// 	v0->errVsOutput->set(1, 0, 1, 6);
// 	v0->errVsOutput->set(0, 1, 1, 7);
// 	v0->errVsOutput->set(1, 1, 1, 8);
// 	v0->errVsOutput->set(0, 0, 2, 8);
// 	v0->errVsOutput->set(1, 0, 2, 7);
// 	v0->errVsOutput->set(0, 1, 2, 6);
// 	v0->errVsOutput->set(1, 1, 2, 5);
// 	v0->errVsOutput->set(0, 0, 3, 4);
// 	v0->errVsOutput->set(1, 0, 3, 3);
// 	v0->errVsOutput->set(0, 1, 3, 2);
// 	v0->errVsOutput->set(1, 1, 3, 1);
// 	v0->feedBackward();
// 	ASSERT_EQ(v0->errVsInputs[0]->get(0, 0, 0), 1);
// 	ASSERT_EQ(v0->errVsInputs[0]->get(1, 0, 0), 2);
// 	ASSERT_EQ(v0->errVsInputs[0]->get(0, 1, 0), 3);
// 	ASSERT_EQ(v0->errVsInputs[0]->get(1, 1, 0), 4);
// 	ASSERT_EQ(v0->errVsInputs[0]->get(0, 0, 1), 5);
// 	ASSERT_EQ(v0->errVsInputs[0]->get(1, 0, 1), 6);
// 	ASSERT_EQ(v0->errVsInputs[0]->get(0, 1, 1), 7);
// 	ASSERT_EQ(v0->errVsInputs[0]->get(1, 1, 1), 8);
// 	ASSERT_EQ(v0->errVsInputs[1]->get(0, 0, 0), 8);
// 	ASSERT_EQ(v0->errVsInputs[1]->get(1, 0, 0), 7);
// 	ASSERT_EQ(v0->errVsInputs[1]->get(0, 1, 0), 6);
// 	ASSERT_EQ(v0->errVsInputs[1]->get(1, 1, 0), 5);
// 	ASSERT_EQ(v0->errVsInputs[1]->get(0, 0, 1), 4);
// 	ASSERT_EQ(v0->errVsInputs[1]->get(1, 0, 1), 3);
// 	ASSERT_EQ(v0->errVsInputs[1]->get(0, 1, 1), 2);
// 	ASSERT_EQ(v0->errVsInputs[1]->get(1, 1, 1), 1);
// }