#pragma once
#include "Lab2.h"

void interfaaace()
{
    std::cout << "Welcome to the Console UI!" << std::endl;
    std::cout << "Choose an option:" << std::endl;
    std::cout << "1. Test manually" << std::endl;
    std::cout << "2. Output information for load testing" << std::endl;
    std::cout << "3. Output information for load testing for every sorts on sort,reverse sort,random data" << std::endl;
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        while (true) {
            std::cout << "|||" << std::endl;
            std::cout << "What would you like to work with? (numbers/Person)" << std::endl;
            std::string dataType;
            std::getline(std::cin, dataType);
            if (dataType == "numbers") {
                std::cout << "Choose an option:" << std::endl;
                std::cout << "1. Generate numbers and sort" << std::endl;
                std::cout << "2. Generate numbers to file and sort" << std::endl;
                std::cout << "3. Write numbers and sort" << std::endl;
                int numberChoice;
                std::cin >> numberChoice;
                switch (numberChoice) {
                case 1: {
                    int size;
                    cout << "enter size of list:" << endl;
                    cin >> size;
                    int minValue = 1;
                    int maxValue = 100;
                    int* randomIntArray = CreateRandomArray(size, minValue, maxValue);
                    std::cout << "Random integer array:" << std::endl;
                    for (int i = 0; i < size; ++i) {
                        std::cout << randomIntArray[i] << (i == size - 1 ? "" : " ");
                    }
                    std::cout << std::endl;

                    // Correct initialization of the DynamicArray using the correct constructor
                    DynamicArray<int> seq(randomIntArray, size);
                    ISorter<int>* sorter = ChooseSorter<int>();
                    sorter->Sort(seq, AscendingInt);

                    std::cout << "Sort array:" << std::endl;
                    for (int i = 0; i < size; ++i) {
                        std::cout << seq.GetElem(i) << (i == size - 1 ? "" : " ");
                    }
                    delete[] randomIntArray;
                    break;
                }
                case 2: {
                    int quantity = 100; // ���������� ��������� �����
                    std::string tempFileName = "RandomNumbers.txt"; // ��������� ����
                    std::string sortedFileName = "RandomSortNumbers.txt"; // ���� ��� ��������������� �����
                    ISorter<int>* sorter = ChooseSorter<int>(); // ������ ������������
                    GenerateAndSortNumbersToFile(quantity, tempFileName, sortedFileName, *sorter, AscendingInt);
                    delete sorter; // ����������� ������
                }
                case 3: {
                    int input;

                    std::cout << "Enter the count of numbers you want to sort:" << std::endl;
                    std::cin >> input;

                    if (input <= 0) {
                        std::cerr << "Count must be a positive integer." << std::endl;

                    }

                    int* numbers = new int[input]; // ���������� ������������ ������
                    std::cout << "Please enter " << input << " numbers (type -1 to finish early):" << std::endl;

                    int count = 0; // ������� ��������� �����
                    for (int i = 0; i < input; ++i) {
                        int number;
                        std::cin >> number;
                        if (number == -1) break; // ���������� �����
                        numbers[count++] = number; // ��������� ����� � ������
                    }

                    // �������� �� ������� ��������� �����
                    if (count == 0) {
                        std::cerr << "No numbers were entered." << std::endl;
                    }
                    DynamicArray<int> NumbersSeq(numbers, count);
                    ISorter<int>* sorter = ChooseSorter<int>();
                    sorter->Sort(NumbersSeq, AscendingInt);

                    std::cout << "Sorted numbers:" << std::endl;
                    for (int i = 0; i < count; ++i) {
                        std::cout << NumbersSeq.GetElem(i) << " ";
                    }
                    std::cout << std::endl;

                    delete[] numbers; // ������������ ������
                    delete sorter; // ������������ ������
                }
                default: {
                    cout << "enter correct number" << endl;
                }
                }// switch ������� ��������� �� ������ �������()
            }
            else if (dataType == "Person") {
                std::cout << "Choose an option:" << std::endl;
                std::cout << "1. Generate random Person data and sort by weight" << std::endl;
                std::cout << "2. Input Person data and sort by weight" << std::endl;
                std::cout << "3. Generate Person data in a file and sort it into another file" << std::endl;
                std::cout << "Type 'end' to exit." << std::endl;

                std::string choice;
                std::getline(std::cin, choice);

                if (choice == "1") {

                    ISorter<Extract<double>>* sorter = ChooseSorter<Extract<double>>();
                    SortRandomPersonDataWeight(*sorter, PrecedesDouble);
                    delete sorter;
                }
                else if (choice == "2") {

                    ISorter<Extract<double>>* sorter = ChooseSorter<Extract<double>>();
                    PersonExtractSortWeight(*sorter, PrecedesDouble);
                    delete sorter;
                }
                else if (choice == "3") {
                    std::string inputFilename = "RandomPersonData.txt";
                    std::string outputFilename = "SortedPersonData.txt";
                    int numPeople;
                    std::cout << "How many random people to generate? ";
                    std::cin >> numPeople;

                    GenerateAndSaveRandomPersonDataInFile(inputFilename, numPeople);
                    // ����� ������������
                    ISorter<Extract<double>>* sorter = ChooseSorter<Extract<double>>();
                    SortPersonDataAndSaveToFile(*sorter, inputFilename, outputFilename);
                    delete sorter; // ������������ ������
                }
                else if (choice == "end") {
                    break; // ����� �� ���������
                }
                else {
                    std::cout << "Invalid choice. Please try again." << std::endl;
                }
            }
            else if (dataType == "end") {
                break;
            }
            else {
                std::cout << "Invalid choice. Please try again." << std::endl;
                continue;
            }
        }
    }
    else if (choice == 2) {
        std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed the RNG once
        const int count_sorts = 6;
        // ������� ������ ���������� �� ������������
        ISorter<int>* sorts[count_sorts];
        sorts[0] = new BubbleSorter<int>();
        sorts[1] = new ShakerSort<int>();
        sorts[2] = new InsertionSort<int>();
        sorts[3] = new HeapSort<int>();
        sorts[4] = new QuickSort<int>();
        sorts[5] = new ShellSort<int>();

        const int sizeCount = 10; // ���������� ��������
        int sizes[sizeCount]; // ������ ��� �������� ��������
        double times[count_sorts][sizeCount]; // ������ ��� ������� ��� 6 �������������

        int k = 0;
        for (int size = 1000; size <= 10000; size += 1000) {
            sizes[k] = size;
            for (int i = 0; i < count_sorts; ++i) {
                times[i][k] = TestSortPerformance(sorts[i], size, 1, 1000,RANDOM);
            }
            k++;
        }

        // ����� ����������� � ������ �������
        std::cout << "Data,BubbleSort,ShakerSort,InsertionSort,HeapSort,QuickSort,ShellSort\n";

        // ������������� ������ ������
        std::cout << std::fixed; // ������������� ���������� ������ ����� �������

        // ����� �����
        for (int j = 0; j < sizeCount; ++j) {
            std::cout << sizes[j]; // ����� �������
            for (int i = 0; i < count_sorts; ++i) {
                std::cout << "," << times[i][j]; // ����� ����������
            }
            std::cout << std::endl;
        }

        // ������������ ������
        for (int i = 0; i < count_sorts; ++i) {
            delete sorts[i];  // ����������� ������ ��� ������� ������������
        }

    }
    else if(choice==3){
        std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed the RNG once

        ISorter<int>* sorter = ChooseSorter<int>();

        const int minSize = 500000;
        const int maxSize = 1000000;
        const int step = 100000;

        std::cout << "Size,Sorted,Reverse Sorted,Random" << std::endl;

        for (int size = minSize; size <= maxSize; size += step) {
            double sortedTime = TestSortPerformance(sorter, size, 1, 1000, SORTED); 
            double unsortedTime = TestSortPerformance(sorter, size, 1, 1000,REVERSE_SORTED); 
            double randomTime = TestSortPerformance(sorter, size, 1, 1000, RANDOM); 

            std::cout << size << "," << sortedTime << "," << unsortedTime << "," << randomTime << std::endl;
        }

        delete sorter; 
    }
    else {
        cout << "incorrect input" << endl;
    }
}
