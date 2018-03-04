#include "ReluTest.h"

ReluTest::ReluTest() {
}

ReluTest::~ReluTest() {
}

void ReluTest::SetUp() {
}

TEST_F(ReluTest, Above0) {
	Layer *input = new Layer(1, 1);
	input->nodes.resize(1);
	input->setNode(0, 0, 1);
	Relu *relu = new Relu(1, 1, input);
	relu->feedForward();
	ASSERT_EQ(relu->getNode(0, 0), 1);
}

TEST_F(ReluTest, Below0) {
	Layer *input = new Layer(1, 1);
	input->nodes.resize(1);
	input->setNode(0, 0, -1);
	Relu *relu = new Relu(1, 1, input);
	relu->feedForward();
	ASSERT_EQ(relu->getNode(0, 0), 0);
}

TEST_F(ReluTest, Both) {
	Layer *input = new Layer(2, 2);
	input->nodes.resize(4);
	input->setNode(0, 0, -1);
	input->setNode(1, 0, -1);
	input->setNode(0, 1, 1);
	input->setNode(1, 1, 0);
	Relu *relu = new Relu(2, 2, input);
	relu->feedForward();
	ASSERT_EQ(relu->getNode(0, 0), 0);
	ASSERT_EQ(relu->getNode(1, 0), 0);
	ASSERT_EQ(relu->getNode(0, 1), 1);
	ASSERT_EQ(relu->getNode(1, 1), 0);
}