# Config Test Pattern

Everything about the test patterns can be easily customized.

## 1. Customizing Test Patterns
### 1.1. How are Test Patterns Defined?

One sorting algorithm corresponds to one test pattern, and all test patterns are derived from virtual class `BaseTestPattern` in [BaseTestPattern.hpp](../include/MySort/TestPattern/BaseTestPattern.hpp) . All derived test patterns are written in [TestPatterns.hpp](../include/MySort/TestPattern/TestPatterns.hpp) by default.

Like what we have done in [main.cpp](../src/main.cpp), `testPatterns::generateData()` must be invoked before instantiating any test pattern. This function will generate the original and the sorted data and store them in two static members `BaseTestPattern::_originalData` and `BaseTestPattern::_sortedData` respectively.

When a test pattern is created, the constructor of `BaseTestPattern` will first check if static member `_originalData` and `_sortedData` exists; And then copy `_originalData` to member `BaseTestPattern::m_testData`. All test patterns have the same static member `_originalData` and `_sortedData`, but each test pattern has its own member `m_testData`.

`BaseTestPattern::test()` is the main logic of a test pattern. It counts the running time of a pure virtual function `BaseTestPattern::sort_impl()`, outputing the time it spent, and comparing `m_testData` with `_sortedData` to check if the sorting is correct.

### 1.2. Define a New Test Pattern

After implementing a sorting algorithm, you can define its test pattern by inheriting `BaseTestPattern` in [TestPatterns.hpp](../include/MySort/TestPattern/TestPatterns.hpp) .

Let's take `testPattern::QuickSort_Lomuto` as an example:

```cpp
class QuickSort_Lomuto : public BaseTestPattern
{
public:
    explicit QuickSort_Lomuto() : BaseTestPattern("[Quick Sort] --Lomuto")
    {
    }

private:
    virtual void sort_impl()
    {
        mysort::quickSort_Lomuto(m_testData.begin(), m_testData.end());
    }
};
```

There are only 2 things you need to do:

1. Define a constructor with a string parameter, which is the name of the test pattern. The name will be printed to the console after the test is done.
2. Implement the pure virtual function `sort_impl()`. This function should call the sorting algorithm you implemented whose target is to sort `m_testData`.

You can also change the behavior of `BaseTestPattern::test()` and `BaseTestPattern::sort_impl()` to colloect more information or do more things.

As long as your test pattern is defined, you can start bemchmarking in [main.cpp](../src/main.cpp) like this:

```cpp
testPatterns::QuickSort_Lomuto().test();
```

Which creates a `QuickSort_Lomuto` instance and runs the test.

### 1.3. Example: Print the Original and the Sorted Data After Sorting

## 2. Customizing Data Configurations

Go to [DataConfig.hpp](../include/MySort/TestPattern/DataConfig.hpp) and change the values of the constants.

