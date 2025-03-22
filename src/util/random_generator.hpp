#ifndef RANDOM_GENERATOR_HPP_
#define RANDOM_GENERATOR_HPP_

#include <random>

namespace Slots {
    class RandomGenerator {
    public:
        RandomGenerator(const RandomGenerator& rg) = delete;
        void operator=(const RandomGenerator& rg)  = delete;

    public:
        static RandomGenerator& get_instance();
        std::mt19937& get_engine();

    private:
        RandomGenerator();

        std::random_device m_rd;
        std::mt19937 m_gen;
    };
} // namespace Slots

#endif // RANDOM_GENERATOR_HPP_
