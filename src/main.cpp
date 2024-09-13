#include <Yutils/ArgParser.hpp>

#include "MySort/TestPattern/DataConfig.hpp"
#include "MySort/TestPattern/TestPatterns.hpp"

std::size_t yutils::testPatterns::NUM_OF_ELEM_TO_GENERATE = 1000;

int main(int argc, char* argv[])
{
    mysort::globalLogger->set_pattern("[%n] [%^%l%$] %v");

    yutils::ArgParser argParser(argv[0]);
    argParser.addOption("-n", "Number of elements", "int", "1000");
    argParser.parse(argc, argv);
    yutils::testPatterns::NUM_OF_ELEM_TO_GENERATE = argParser.get<std::size_t>("-n");

    yutils::testPatterns::generateData();
    yutils::testPatterns::stdSort().test();
    yutils::testPatterns::stdStableSort().test();
    yutils::testPatterns::BubbleSort().test();
    yutils::testPatterns::BubbleSort_Stop().test();
    yutils::testPatterns::BubbleSort_NarrowBoundary().test();
    yutils::testPatterns::InsertionSort().test();
    yutils::testPatterns::SelectionSort().test();
    yutils::testPatterns::HeapSort().test();
    yutils::testPatterns::MergeSort().test();
    yutils::testPatterns::MergeSort_Natural().test();
    yutils::testPatterns::QuickSort_Lomuto().test();
    yutils::testPatterns::QuickSort_Lomuto_TailRecOpt().test();
    yutils::testPatterns::QuickSort_Lomuto_Rand().test();
    yutils::testPatterns::QuickSort_Lomuto_Rand_Duplicated().test();
    yutils::testPatterns::QuickSort_Lomuto_Rand_Duplicated_Insertion().test();
    yutils::testPatterns::QuickSort_Hoare().test();
    yutils::testPatterns::QuickSort_Hoare_rand().test();
    yutils::testPatterns::QuickSort_Hoare_insertion().test();
    yutils::testPatterns::PdqSort().test();
}