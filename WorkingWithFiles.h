#pragma once
#include <fstream>
#include <random>
#include "DynamicArray.h"
#include "ISorter.h"
#include <sstream> //для работы с потоками строк.
#include <iostream>
#include <string>

void WriteRandomNumbersToFile(unsigned long long quantity, const std::string& outputFileName);

//inputFileName - название файла
template <typename T>
void ReadNumbersFromFile(const std::string& inputFileName, Sequence<T>& numbers) {
    std::ifstream fileStream(inputFileName); 

    if (!fileStream.is_open()) { 
        std::cerr << "Error opening file: " << inputFileName << std::endl;
        return; 
    }

    std::string line;
    //считывается поток ввода в строку line
    //каждая итерация-это новое замеченное в line /n
    //true строка считана, False  - нет
    while (std::getline(fileStream, line)) {
        std::istringstream iss(line);
        T item;
        if (iss >> item) {
            numbers.Append(item);
        }
        else {
            std::cerr << "Error: Could not convert line to target type: " << line << std::endl;
        }
    }

    fileStream.close();
}

template <class T>
void WriteSequenceToFile(std::string& FName, Sequence<T>* numbers)
{
    std::ofstream outFile(FName);
    if (!outFile) {
        std::cerr << "Error opening the file!" << std::endl;
        return;
    }

    auto begin = numbers->ToBegin();
    auto end = numbers->ToEnd();

    while (*begin != *end)
    {
        outFile << **begin << std::endl;
        ++(*begin);
    }

    std::cout << "The numbers have been successfully written to the file " << FName << std::endl;

    outFile.close();
}

template <typename T>
void WriteSortedNumbersToFile(const std::string& inputFileName, const std::string& outputFileName, ISorter<T>& sorter, bool (*comparator)(const T&, const T&)) {
    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file: " << inputFileName << std::endl;
        return;
    }

    std::vector<T> numbers;
    T number;

    while (inputFile >> number) {
        numbers.push_back(number);
    }
    inputFile.close();

    DynamicArray<T> sequence; 
    for (const auto& num : numbers) {
        sequence.Append(num); 
    }

    sorter.Sort(sequence, comparator);

    std::ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file: " << outputFileName << std::endl;
        return;
    }

    for (int i = 0; i < sequence.GetLength(); ++i) {
        outputFile << sequence.GetElem(i) << "\n";
    }

    std::cout << "Sorted numbers have been written to file: " << outputFileName << std::endl;
    outputFile.close();
}
