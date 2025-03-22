#include "random_generator.hpp"

namespace Slots {
    RandomGenerator::RandomGenerator() :
        m_rd { },
        m_gen { m_rd() }
    { }

    RandomGenerator& RandomGenerator::get_instance() {
        static RandomGenerator instance;

        return instance;
    }

    std::mt19937& RandomGenerator::get_engine() {
        return m_gen;
    }
} // namespace Slots
