#include <forward_list>
#include <Yutils/ArgParser.hpp>

#include "MySort/TestPattern/TestPatterns.hpp"
#include "MySort/TestPattern/DataConfig.hpp"

std::size_t testPatterns::NUM_OF_ELEM_TO_GENERATE = 1000;

int main(int argc, char* argv[]) {
    yutils::ArgParser argParser;
    argParser.addOption("-n", "Number of elements", "int", "1000");
    argParser.parse(argc, argv);
    testPatterns::NUM_OF_ELEM_TO_GENERATE = argParser.get<std::size_t>("-n").value_or(1000);


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
    //system("pause");
}