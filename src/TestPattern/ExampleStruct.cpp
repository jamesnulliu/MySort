#include "MySort/TestPattern/ExampleStruct.hpp"

namespace yutils
{
using ExampleStruct = testPatterns::ExampleStruct;

std::random_device RandUniform<ExampleStruct>::_rd{};
thread_local std::default_random_engine RandUniform<ExampleStruct>::m_engine{_rd()};
std::uniform_real_distribution<double>* RandUniform<ExampleStruct>::m_distribution{nullptr};

std::random_device RandNormal<ExampleStruct>::_rd{};
thread_local std::default_random_engine RandNormal<ExampleStruct>::m_engine{_rd()};
std::normal_distribution<double>* RandNormal<ExampleStruct>::m_distribution{nullptr};
}  // namespace yutils