#include "../src/Relu.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <algorithm>

using namespace std;

class ReluTest : public ::testing::Test{
	private:
	public:
		virtual void SetUp();
		ReluTest();
		~ReluTest();
};