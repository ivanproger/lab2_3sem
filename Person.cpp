#include "Person.h"

//������� ��������� � ���� � ����� �� �����
//*������� �� ������ ��������� Extract
//������� ���������
//����� excel
//������������� ���������� int& numPeople �� id 2)�������� ������� �� ������� ������

//1) ������� ��������� �������������� �������� 2)numPeople ������ 3)�������������� �������(Person.cpp) ������ ������� �������� �� 1��������*
//4)�������� ������ � ������� 
void WritePeopleToFile(std::ofstream& outputFile, LinkedList<Person>& people) {
    for (int i = 0; i < people.GetLength(); ++i) {
        const Person& person = people.GetElem(i);
        outputFile << person.id << " "
            << person.FirstName << " "
            << person.LastName << " "
            << person.BirthYear << " "
            << person.Height << " "
            << person.Weight << "\n";
    }
}

void GenerateRandomPersonData(LinkedList<Person>& people, LinkedList<Extract<double>>& weights, int numToGenerate) {
    int numPeople = 0; // Initialize numPeople within the function
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> birthYearDist(1900, 2024);
    std::uniform_real_distribution<> weightDist(1.0, 100.0);
    std::uniform_real_distribution<> heightDist(1.0, 200.0);

    std::vector<std::string> firstNames = { "Ivan", "Andrey", "Petr", "Sergey" };
    std::vector<std::string> lastNames = { "Smith", "Jones", "Doe", "Brown" };

    for (int i = 0; i < numToGenerate; ++i) {
        int id = numPeople + 1;
        int birthYear = birthYearDist(gen);
        double weight = weightDist(gen);
        double height = heightDist(gen);

        std::string firstName = firstNames[gen() % firstNames.size()];
        std::string lastName = lastNames[gen() % lastNames.size()];

        // Create a new Person and append it to the list
        Person newPerson(id, firstName, lastName, birthYear, height, weight);
        people.Append(newPerson); // Assuming Append method is defined in LinkedList
        weights.Append(Extract<double>(numPeople, weight));
        numPeople++;
    }
}

void GenerateAndSaveRandomPersonDataInFile(const std::string& filename, int numToGenerate) {
    LinkedList<Person> people; // ������ ��� �������� ��������������� �����
    LinkedList<Extract<double>> weights; // ������ ��� �������� �����

    // ��������� ��������� ������
    GenerateRandomPersonData(people, weights, numToGenerate);

    // ���������� ������ � ����
    std::ofstream outputFile(filename);
    if (outputFile.is_open()) {
        WritePeopleToFile(outputFile, people); // ���������� ����� ������� ��� ������ ������
        outputFile.close();
        std::cout << "Generated person data saved to file: " << filename << std::endl;
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

bool ExtractPersonFromStream(std::stringstream& ss, Person& person) {
    int id, by;
    std::string firstName, lastName;
    double height, weight;

    if (ss >> id >> firstName >> lastName >> by >> height >> weight) {
        person = Person(id, firstName, lastName, by, height, weight); // ������� ���������
        return true;
    }
    else {
        return false; // ������ ��� ����������
    }
}

void DisplayPersonsInfo(LinkedList<Extract<double>>& weights, LinkedList<Person>& people) {
    std::cout << "\nSorted Persons by Weight:\n";
    int numToGenerate = weights.GetLength(); // �������� ���������� �����
    for (int i = 0; i < numToGenerate; ++i) {
        const Extract<double>& w = weights.GetElem(i);
        const Person& person = people.GetElem(w.index); // �������� �������� �� ������� �� ����
        std::cout << "ID: " << person.id
            << ", Name: " << person.FirstName << " " << person.LastName
            << ", Birth Year: " << person.BirthYear
            << ", Height: " << person.Height
            << ", Weight: " << person.Weight << std::endl;
    }
}

// Function to generate random data and sort by weight
// ������� ��� ��������� ��������� ������ � ���������� �� ����
void SortRandomPersonDataWeight(ISorter<Extract<double>>& sorter, bool (*precedes)(const Extract<double>&, const Extract<double>&)) {
    LinkedList<Person> people; // ���������� LinkedList<Person> ��� �������� ��������������� �����
    LinkedList<Extract<double>> weights;

    int numToGenerate;
    std::cout << "How many random people to generate? ";
    std::cin >> numToGenerate;

    // ��������� ������ ��� numToGenerate
    if (numToGenerate <= 0) {
        std::cerr << "Invalid number of people to generate. Must be greater than 0." << std::endl;
        return;
    }

    GenerateRandomPersonData(people, weights, numToGenerate);
    sorter.Sort(weights, precedes);
    std::cout << "\nSorted Persons by Weight:\n";
    DisplayPersonsInfo(weights, people); // ����� ����� ������� ��� ������ ���������� � �����
}

void PersonExtractSortWeight(ISorter<Extract<double>>& sorter, bool (*precedes)(const Extract<double>&, const Extract<double>&)) {
    int numPeople = 0;
    LinkedList<Extract<double>> weights;
    LinkedList<Person> people; // ��������� ������ �����

    std::string inputLine;

    while (true) {
        std::cout << "Enter Person " << numPeople + 1 << " details (id, FirstName, LastName, BirthYear, Height, Weight), or 'end' to finish: ";
        std::getline(std::cin, inputLine);
        if (inputLine == "end") break;

        std::stringstream ss(inputLine);
        Person person; // ������� ������ Person ��� �������� ������
        if (ExtractPersonFromStream(ss, person)) { // ���������� ����� �������
            people.Append(person); // ��������� ��������
            weights.Append(Extract<double>(numPeople, person.Weight));
            numPeople++;
        }
        else {
            std::cerr << "Invalid input format. Please try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // ���������� �����
    sorter.Sort(weights, precedes);
    DisplayPersonsInfo(weights, people); // ���������� ����� ������� ��� ������ ���������� � �����
}

bool LoadPeopleData(const std::string& inputFilename, LinkedList<Person>& people, LinkedList<Extract<double>>& weights) {
    std::ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file: " << inputFilename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        Person person; // ������� ������ Person ��� �������� ������
        if (ExtractPersonFromStream(ss, person)) { // ���������� ����� �������
            people.Append(person);
            weights.Append(Extract<double>(person.id - 1, person.Weight)); // ��������� ������ � ���
        }
        else {
            std::cerr << "Invalid input format in file: " << inputFilename << std::endl;
        }
    }
    inputFile.close();
    return true;
}

void SaveSortedDataToFile(const std::string& outputFilename, LinkedList<Person>& people, LinkedList<Extract<double>>& weights) {
    std::ofstream outputFile(outputFilename);
    if (outputFile.is_open()) {
        for (int i = 0; i < weights.GetLength(); ++i) {
            const Extract<double>& weight = weights.GetElem(i);
            const Person& person = people.GetElem(weight.index);
            outputFile << person.id << " " << person.FirstName << " " << person.LastName << " "
                << person.BirthYear << " " << person.Height << " " << person.Weight << "\n";
        }
        outputFile.close();
        std::cout << "Sorted person data saved to file: " << outputFilename << std::endl;
    }
    else {
        std::cerr << "Unable to open file: " << outputFilename << std::endl;
    }

    DisplayPersonsInfo(weights, people); // ���������� ����� ������� ��� ������ ���������� � �����
}

void SortPersonDataAndSaveToFile(ISorter<Extract<double>>& sorter, const std::string& inputFilename, const std::string& outputFilename) {
    LinkedList<Person> people;
    LinkedList<Extract<double>> weights;

    if (!LoadPeopleData(inputFilename, people, weights)) {
        return; // ���� �������� �� �������, �������
    }
    sorter.Sort(weights, PrecedesDouble);
    SaveSortedDataToFile(outputFilename, people, weights);
}