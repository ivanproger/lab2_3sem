#pragma once
#include "LinkedList.h"
#include "DynamicArray.h"
#include "WorkingWithFiles.h"

void WriteRandomNumbersToFile(unsigned long long quantity, const std::string& outputFileName)
{
    std::ofstream fileStream(outputFileName);

    if (!fileStream.is_open()) {
        std::cerr << "Unable to open file: " << outputFileName << std::endl;
        return;
    }

    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dist(0, 10000);

    for (unsigned long long index = 0; index < quantity; ++index) {
        unsigned long long randomValue = dist(gen); 
        fileStream << randomValue << "\n";
    }

    std::cout << "Generated " << quantity << " random numbers in file: " << outputFileName << std::endl;

    fileStream.close();
}

void WriteSequenceToFile(std::string& FName, Sequence<int>* numbers)
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

