#include "RandomSeed.h"

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine RandomSeed::generator(seed);

RandomSeed::RandomSeed() {
}

RandomSeed::~RandomSeed() {

}