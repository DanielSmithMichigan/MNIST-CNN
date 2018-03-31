#include "InputLayerTest.h"

InputLayerTest::InputLayerTest() {
}

InputLayerTest::~InputLayerTest() {
}

void InputLayerTest::SetUp() {
}

class OneByOneTrainingImagesMock : public PixelStream {
	public:
		uint8_t get() {return 1;}
};

TEST_F(InputLayerTest, OneByOne) {
	InputLayer *inputLayer = new InputLayer(1, 1);
	inputLayer->pixelStream = new OneByOneTrainingImagesMock();
	inputLayer->feedForward();
	ASSERT_EQ(inputLayer->outputVolume->get(0, 0, 0), 1);
}