#include "Person.h"

//сделать генерацию в файл и вывод из файла
//*сделать по разным признакам Extract
//Поднять интерфейс
//вывод excel
//переименовать переменные int& numPeople на id 2)подумать сделать ли счётчик внутри

//1) добавил обработку непредвиденных значений 2)numPeople внутри 3)декомпозировал функции(Person.cpp) каждая функция отвечает за 1действие*
//4)исправил работу с файлами 
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
    LinkedList<Person> people; // Список для хранения сгенерированных людей
    LinkedList<Extract<double>> weights; // Список для хранения весов

    // Генерация случайных данных
    GenerateRandomPersonData(people, weights, numToGenerate);

    // Сохранение данных в файл
    std::ofstream outputFile(filename);
    if (outputFile.is_open()) {
        WritePeopleToFile(outputFile, people); // Используем новую функцию для записи данных
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
        person = Person(id, firstName, lastName, by, height, weight); // Успешно извлечено
        return true;
    }
    else {
        return false; // Ошибка при извлечении
    }
}

void DisplayPersonsInfo(LinkedList<Extract<double>>& weights, LinkedList<Person>& people) {
    std::cout << "\nSorted Persons by Weight:\n";
    int numToGenerate = weights.GetLength(); // Получаем количество весов
    for (int i = 0; i < numToGenerate; ++i) {
        const Extract<double>& w = weights.GetElem(i);
        const Person& person = people.GetElem(w.index); // Получаем человека по индексу из веса
        std::cout << "ID: " << person.id
            << ", Name: " << person.FirstName << " " << person.LastName
            << ", Birth Year: " << person.BirthYear
            << ", Height: " << person.Height
            << ", Weight: " << person.Weight << std::endl;
    }
}

// Function to generate random data and sort by weight
// Функция для генерации случайных данных и сортировки по весу
void SortRandomPersonDataWeight(ISorter<Extract<double>>& sorter, bool (*precedes)(const Extract<double>&, const Extract<double>&)) {
    LinkedList<Person> people; // Используем LinkedList<Person> для хранения сгенерированных людей
    LinkedList<Extract<double>> weights;

    int numToGenerate;
    std::cout << "How many random people to generate? ";
    std::cin >> numToGenerate;

    // Обработка ошибок для numToGenerate
    if (numToGenerate <= 0) {
        std::cerr << "Invalid number of people to generate. Must be greater than 0." << std::endl;
        return;
    }

    GenerateRandomPersonData(people, weights, numToGenerate);
    sorter.Sort(weights, precedes);
    std::cout << "\nSorted Persons by Weight:\n";
    DisplayPersonsInfo(weights, people); // Вызов новой функции для вывода информации о людях
}

void PersonExtractSortWeight(ISorter<Extract<double>>& sorter, bool (*precedes)(const Extract<double>&, const Extract<double>&)) {
    int numPeople = 0;
    LinkedList<Extract<double>> weights;
    LinkedList<Person> people; // Добавляем список людей

    std::string inputLine;

    while (true) {
        std::cout << "Enter Person " << numPeople + 1 << " details (id, FirstName, LastName, BirthYear, Height, Weight), or 'end' to finish: ";
        std::getline(std::cin, inputLine);
        if (inputLine == "end") break;

        std::stringstream ss(inputLine);
        Person person; // Создаем объект Person для хранения данных
        if (ExtractPersonFromStream(ss, person)) { // Используем новую функцию
            people.Append(person); // Сохраняем человека
            weights.Append(Extract<double>(numPeople, person.Weight));
            numPeople++;
        }
        else {
            std::cerr << "Invalid input format. Please try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // Сортировка весов
    sorter.Sort(weights, precedes);
    DisplayPersonsInfo(weights, people); // Используем новую функцию для вывода информации о людях
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
        Person person; // Создаем объект Person для хранения данных
        if (ExtractPersonFromStream(ss, person)) { // Используем новую функцию
            people.Append(person);
            weights.Append(Extract<double>(person.id - 1, person.Weight)); // Сохраняем индекс и вес
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

    DisplayPersonsInfo(weights, people); // Используем новую функцию для вывода информации о людях
}

void SortPersonDataAndSaveToFile(ISorter<Extract<double>>& sorter, const std::string& inputFilename, const std::string& outputFilename) {
    LinkedList<Person> people;
    LinkedList<Extract<double>> weights;

    if (!LoadPeopleData(inputFilename, people, weights)) {
        return; // Если загрузка не удалась, выходим
    }
    sorter.Sort(weights, PrecedesDouble);
    SaveSortedDataToFile(outputFilename, people, weights);
}