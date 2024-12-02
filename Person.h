#pragma once

#include <chrono>
#include <fstream>
#include <sstream>  

#include <string>
#include <ctime>
#include <cstdlib>
#include <random>
#include <limits>
#include <iostream>

#include "DynamicArray.h"
#include "SortingMethods.h"
#include "TestSort.h"
#include "ISorter.h"
#include "WorkingWithFiles.h"
#include "PersonExtract.h"
#include "Compare.h"

using namespace std;
struct Person {
    int id;
    std::string LastName;
    std::string FirstName;
    int BirthYear;
    double Height;
    double Weight;

    Person() : id(0), LastName(""), FirstName(""), BirthYear(0), Height(0.0), Weight(0.0) {}

    Person(int identifier, const std::string& ln, const std::string& fn, int by, double h, double w)
        : id(identifier), LastName(ln), FirstName(fn), BirthYear(by), Height(h), Weight(w) {}

    // ... (other parts of the Person struct remain the same) ...
};
void GenerateAndSaveRandomPersonDataInFile(const std::string& filename, int numToGenerate);
void DisplayPersonsInfo(LinkedList<Extract<double>>& weights, LinkedList<Person>& people);
void GenerateRandomPersonData(LinkedList<Person>& people, LinkedList<Extract<double>>& weights, int numToGenerate);
void SortRandomPersonDataWeight(ISorter<Extract<double>>& sorter, bool (*precedes)(const Extract<double>&, const Extract<double>&));
void PersonExtractSortWeight(ISorter<Extract<double>>& sorter, bool (*precedes)(const Extract<double>&, const Extract<double>&));
void SortPersonDataAndSaveToFile(ISorter<Extract<double>>& sorter, const std::string& inputFilename, const std::string& outputFilename);
bool ExtractPersonFromStream(std::stringstream& ss, Person& person);
bool LoadPeopleData(const std::string& inputFilename, LinkedList<Person>& people, LinkedList<Extract<double>>& weights);
void SaveSortedDataToFile(const std::string& outputFilename, LinkedList<Person>& people, LinkedList<Extract<double>>& weights);
void WritePeopleToFile(std::ofstream& outputFile, LinkedList<Person>& people);