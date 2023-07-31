#ifndef RANDOMENGINE_H
#define RANDOMENGINE_H

#include <random>

class RandomEngine final {
  private:
    static std::default_random_engine engine;

  public:
    static void setSeed(unsigned int seed);

    static std::default_random_engine& getEngine();
};

#endif
