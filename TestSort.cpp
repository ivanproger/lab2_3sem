#pragma once
#include "TestSort.h"


void AllSortFunctionalForSortingTest() {
    const int tests_num = 5;
    const int ell_in_test_num = 5;

    // Array organize: [Test1,Test2,Test3...] Test1 = [Array,SortedArray]...
    //1 group of tests
    int testCases[tests_num][2][ell_in_test_num] = {
        {{5, 3, 4, 2, 1}, {1, 2, 3, 4, 5}}, 
        {{10, 7, 8, 9, 1}, {1, 7, 8, 9, 10}}, 
        {{-3, 1, 2, 5, 4}, {-3, 1, 2, 4, 5}},
        {{-3,-3,-1,-3,-3}, {-3,-3,-3,-3,-1}},
        {{3,3,2,1,1}, {1,1,2,3,3}}
    };

    FunctionalBubbleSortTest<int>(testCases, tests_num); // Pass the test cases and number of tests
    FunctionalShakerSortTest<int>(testCases, tests_num);
    FunctionalHeapSortTest<int>(testCases, tests_num);
    FunctionalQuickSortTest<int>(testCases, tests_num);
    FunctionalShellSortTest<int>(testCases, tests_num);
}