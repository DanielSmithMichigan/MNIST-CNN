#include "../src/Normalization.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <algorithm>

using namespace std;

class NormalizationTest : public ::testing::Test{
	private:
	public:
		virtual void SetUp();
		NormalizationTest();
		~NormalizationTest();
};