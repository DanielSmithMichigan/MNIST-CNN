#pragma once
#include <cmath>
#include "Constants.h"
#include "Volume.h"
using namespace std;

class RandomSeed{
    private:
    protected:
    public:
        RandomSeed();
        ~RandomSeed();
        static default_random_engine generator;
};