#include "../src/FullyConnected.h"
#include "../src/Sigmoid.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <algorithm>

using namespace std;

class IntegrationTest : public ::testing::Test{
	private:
	public:
		virtual void SetUp();
		IntegrationTest();
		~IntegrationTest();
};