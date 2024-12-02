#pragma once
#include "TestSort.h"
#include "WorkingWithFiles.h"
#include "PersonExtract.h"

template <class T>
ISorter<T>* ChooseSorter() {
    std::cout << "Choose a sorting algorithm:" << std::endl;
    std::cout << "1. Bubble Sort" << std::endl;
    std::cout << "2. Shaker Sort" << std::endl;
    std::cout << "3. Insertion Sort" << std::endl;
    std::cout << "4. Quick Sort" << std::endl;
    std::cout << "5. Shell Sort" << std::endl;
    std::cout << "6. Heap Sort" << std::endl;

    int choice;
    std::cin >> choice;

    // ������� ������ �����
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
    case 1:
        return new BubbleSorter<T>(); // ���������� ����� ��������� BubbleSorter
    case 2:
        return new ShakerSort<T>(); // ���������� ����� ��������� ShakerSort
    case 3:
        return new InsertionSort<T>(); // ���������� ����� ��������� InsertionSorts
    case 4:
        return new QuickSort<T>(); // ���������� ����� ��������� QuickSort
    case 5:
        return new ShellSort<T>(); // ���������� ����� ��������� ShellSort
    case 6:
        return new HeapSort<T>(); 
    default:
        std::cerr << "Invalid choice. Defaulting to Bubble Sort." << std::endl;
        return new BubbleSorter<T>(); // ���������� BubbleSorter �� ���������
    }
}

void interfaaace();

template <typename T>
void GenerateAndSortNumbersToFile(unsigned long long quantity, std::string& tempFileName, std::string& sortedFileName, ISorter<T>& sorter, bool (*precedes)(const T&, const T&)) {
    // ��������� ��������� ����� � ��������� ����
    WriteRandomNumbersToFile(quantity, tempFileName);

    // ���������� ����� � ������ � ������ ����
    WriteSortedNumbersToFile(tempFileName, sortedFileName, sorter, precedes);
}