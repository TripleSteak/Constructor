#include "randomengine.h"

std::default_random_engine RandomEngine::engine;

void RandomEngine::setSeed(unsigned int seed) {
    engine.seed(seed);
}

std::default_random_engine& RandomEngine::getEngine() {
    return engine;
}
