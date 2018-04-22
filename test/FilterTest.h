#include "../src/Filter.h"
#include "../src/Padding.h"
#include "../src/InputLayer.h"
#include "../src/PixelStream.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <algorithm>

using namespace std;

class FilterTest : public ::testing::Test{
	private:
	public:
		virtual void SetUp();
		FilterTest();
		~FilterTest();
};