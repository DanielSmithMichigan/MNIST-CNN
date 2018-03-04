#include "../src/InputLayer.h"
#include "../src/PixelStream.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <algorithm>

using namespace std;

class InputLayerTest : public ::testing::Test{
	private:
	public:
		virtual void SetUp();
		InputLayerTest();
		~InputLayerTest();
};