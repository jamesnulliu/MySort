#include <Yutils/ArgParser.hpp>
#include <forward_list>

#include "MySort/TestPattern/DataConfig.hpp"
#include "MySort/TestPattern/TestPatterns.hpp"

std::size_t testPatterns::NUM_OF_ELEM_TO_GENERATE = 1000;
testPatterns::GenMethod testPatterns::GENERATE_METHOD = testPatterns::GenMethod::NORMAL_DIST;

template <>
inline std::optional<testPatterns::GenMethod> yutils::convertStrArg(std::string strVal,
                                                                    std::string type)
{
    if (strVal == "normal_dist") {
        return testPatterns::GenMethod::NORMAL_DIST;
    } else if (strVal == "uniform_dist") {
        return testPatterns::GenMethod::UNIFORM_DIST;
    } else if (strVal == "ordered") {
        return testPatterns::GenMethod::ORDERED;
    } else if (strVal == "reverse_ordered") {
        return testPatterns::GenMethod::REVERSE_ORDERED;
    } else if (strVal == "same") {
        return testPatterns::GenMethod::SAME;
    } else if (strVal == "other") {
        return testPatterns::GenMethod::OTHER;
    } else {
        return std::nullopt;
    }
}

int main(int argc, char* argv[])
{
    yutils::ArgParser argParser;
    argParser.addOption("-n", "Number of elements", "int", "1000");
    argParser.addOption("-g", "Generate method", "testPatterns::GenMethod", "normal_dist");
    argParser.parse(argc, argv);
    testPatterns::NUM_OF_ELEM_TO_GENERATE = argParser.get<std::size_t>("-n").value_or(1000);
    testPatterns::GENERATE_METHOD =
        argParser.get<testPatterns::GenMethod>("-g").value_or(testPatterns::GenMethod::NORMAL_DIST);

    testPatterns::generateData();
    testPatterns::BubbleSort().test();
    testPatterns::BubbleSort_Stop().test();
    testPatterns::BubbleSort_NarrowBoundary().test();
    testPatterns::InsertionSort().test();
    testPatterns::SelectionSort().test();
    testPatterns::MergeSort().test();
    testPatterns::MergeSort_Natural().test();
    testPatterns::QuickSort_Lomuto().test();
    testPatterns::QuickSort_Lomuto_TailRecOpt().test();
    testPatterns::QuickSort_Lomuto_Rand().test();
    testPatterns::QuickSort_Lomuto_Rand_Duplicated().test();
    testPatterns::QuickSort_Lomuto_Rand_Duplicated_Insertion().test();
    testPatterns::QuickSort_Hoare().test();
    testPatterns::QuickSort_Hoare_rand().test();
    testPatterns::QuickSort_Hoare_insertion().test();
    testPatterns::HeapSort().test();
    testPatterns::PdqSort().test();
}