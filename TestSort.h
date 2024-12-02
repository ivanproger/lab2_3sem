#pragma once
#include "SortingMethods.h" // Assuming this contains the definitions of sorters
#include "LinkedList.h"     // Assuming this contains the definition of LinkedList class
#include "DynamicArray.h" 
#include <chrono>           // For measuring sorting time
#include <iostream>
#include <cassert>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <memory> 
#include "Person.h"
#include "Compare.h"

enum ArrayFillType {
    RANDOM = 1,
    SORTED = 2,
    REVERSE_SORTED = 3
};

// Function to create a random array
template <class T>
T* CreateRandomArray(int size, T minValue, T maxValue) {
    // Initialization of random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Creating a dynamic array
    T* array = new T[size];

    for (int i = 0; i < size; ++i) {
        // Generating a random number in the range [minValue, maxValue]
        array[i] = minValue + static_cast<T>(std::rand()) / (static_cast<T>(RAND_MAX) / (maxValue - minValue + 1));
    }

    return array; // Returning the created array
}

template <class T>
double TestSortPerformance(ISorter<T>* sorter, T size, T minValue, T maxValue, ArrayFillType fillType) {
    T* array1 = new T[size]; // Создаем массив динамически

    // Заполнение массива в зависимости от значения fillType
    if (fillType == RANDOM) {
        // Генерация случайных значений
        array1 = CreateRandomArray(size, minValue, maxValue);
    }
    else if (fillType == SORTED) {
        // Заполнение отсортированными значениями
        for (T i = 0; i < size; ++i) {
            array1[i] = minValue + (maxValue - minValue) * i / (size - 1); // Генерируем отсортированные значения
        }
    }
    else if (fillType == REVERSE_SORTED) {
        // Заполнение обратно отсортированными значениями
        for (T i = 0; i < size; ++i) {
            array1[i] = maxValue - (maxValue - minValue) * i / (size - 1); // Генерируем обратно отсортированные значения
        }
    }
    else {
        std::cerr << "Invalid fillType value. Must be 1 (RANDOM), 2 (SORTED), or 3 (REVERSE_SORTED)." << std::endl;
        delete[] array1; // Освобождаем память
        return -1; // Неверное значение fillType
    }

    // Создание динамического массива
    DynamicArray<T> sequence1(array1, size); // Используйте другой конструктор для LinkedList, если необходимо

    auto start = std::chrono::high_resolution_clock::now();
    sorter->Sort(sequence1, AscendingInt); // Передаем указатель на последовательность
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;

    delete[] array1; // Освобождаем память массива
    return duration.count();
}

// Function for testing sorting performance
template <class T>
void TestSortPerformanceForSorting(ISorter<T>* sorter, T size, T minValue, T maxValue) {
    T* array1 = CreateRandomArray(size, minValue, maxValue);

    // Creating an array
    LinkedList<T> sequence1(array1, size); // Use another constructor for LinkedList if necessary


    auto start = std::chrono::high_resolution_clock::now();
    sorter->Sort(sequence1, AscendingInt); // Passing a pointer to the sequence
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Sorting " << size << " elements took " << duration.count() << " ms." << std::endl;

    delete[] array1; // Freeing the array memory
}

template <typename T>
void VerifTest(ISorter<T>* sorter, T* array2, const T* SortedArray, std::size_t size) {
    DynamicArray<T> array1(array2, size); // Use T instead of int
    sorter->Sort(array1, AscendingInt); // Sort the original array

    for (std::size_t i = 0; i < size; i++) {
        assert(array1[i] == SortedArray[i]); // Check sorted array
    }
}

template <typename T>
void FunctionalBubbleSortTest(T testCases[][2][5], std::size_t numTests) {
    for (std::size_t i = 0; i < numTests; i++) {
        T* array = testCases[i][0]; // Unsorted array
        const T* sortedArray = testCases[i][1]; // Sorted array
        T copyArray[5]; // Create a copy for sorting
        std::copy(array, array + 5, copyArray); // Copy the original array to the new array
        VerifTest(new BubbleSorter<T>(), copyArray, sortedArray, 5); // Call VerifTest
    }
}

// Function to perform all tests
template <typename T>
void FunctionalShakerSortTest(T testCases[][2][5], std::size_t numTests) {
    for (std::size_t i = 0; i < numTests; i++) {
        T* array = testCases[i][0]; // Unsorted array
        const T* sortedArray = testCases[i][1]; // Sorted array
        T copyArray[5]; // Create a copy for sorting
        std::copy(array, array + 5, copyArray); // Copy the original array to the new array
        VerifTest(new BubbleSorter<T>(), copyArray, sortedArray, 5); // Call VerifTest
    }
}

// Function to perform all tests
template <typename T>
void FunctionalInsertionSortTest(T testCases[][2][5], std::size_t numTests) {
    for (std::size_t i = 0; i < numTests; i++) {
        T* array = testCases[i][0]; // Unsorted array
        const T* sortedArray = testCases[i][1]; // Sorted array
        T copyArray[5]; // Create a copy for sorting
        std::copy(array, array + 5, copyArray); // Copy the original array to the new array
        VerifTest(new BubbleSorter<T>(), copyArray, sortedArray, 5); // Call VerifTest
    }
}

// Function to perform all tests
template <typename T>
void FunctionalHeapSortTest(T testCases[][2][5], std::size_t numTests) {
    for (std::size_t i = 0; i < numTests; i++) {
        T* array = testCases[i][0]; // Unsorted array
        const T* sortedArray = testCases[i][1]; // Sorted array
        T copyArray[5]; // Create a copy for sorting
        std::copy(array, array + 5, copyArray); // Copy the original array to the new array
        VerifTest(new BubbleSorter<T>(), copyArray, sortedArray, 5); // Call VerifTest
    }
}

// Function to perform all tests
template <typename T>
void FunctionalQuickSortTest(T testCases[][2][5], std::size_t numTests) {
    for (std::size_t i = 0; i < numTests; i++) {
        T* array = testCases[i][0]; // Unsorted array
        const T* sortedArray = testCases[i][1]; // Sorted array
        T copyArray[5]; // Create a copy for sorting
        std::copy(array, array + 5, copyArray); // Copy the original array to the new array
        VerifTest(new BubbleSorter<T>(), copyArray, sortedArray, 5); // Call VerifTest
    }
}

// Function to perform all tests
template <typename T>
void FunctionalShellSortTest(T testCases[][2][5], std::size_t numTests) {
    for (std::size_t i = 0; i < numTests; i++) {
        T* array = testCases[i][0]; // Unsorted array
        const T* sortedArray = testCases[i][1]; // Sorted array
        T copyArray[5]; // Create a copy for sorting
        std::copy(array, array + 5, copyArray); // Copy the original array to the new array
        VerifTest(new BubbleSorter<T>(), copyArray, sortedArray, 5); // Call VerifTest
    }
}
void AllSortFunctionalForSortingTest();

