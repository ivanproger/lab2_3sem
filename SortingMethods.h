#pragma once
#include "ISorter.h"
#include "Sequence.h"

template <class T>
class BubbleSorter : public ISorter<T> {
public:
    void Sort(Sequence<T>& sequence, bool (*precedes)(const T& first, const T& second)) override {
        int n = sequence.GetLength(); // Получаем длину последовательности
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (!precedes(sequence.GetElem(j), sequence.GetElem(j + 1))) {
                    // Если порядок нарушен, меняем элементы местами
                    T temp = sequence.GetElem(j);
                    sequence.Set(j, sequence.GetElem(j + 1));
                    sequence.Set(j + 1, temp);
                }
            }
        }
    }
};

template <class T>
class ShakerSort : public ISorter<T> {
public:
    void Sort(Sequence<T>& sequence, bool (*precedes)(const T& first, const T& second)) override {
        int len = sequence.GetLength();
        if (len <= 1) return; // Проверка для пустого списка или списка одного элемента

        bool swapped = true;
        int left = 0;
        int right = len - 1;

        while (swapped) {
            swapped = false;

            // Движение вправо
            for (int i = left; i < right; i++) {
                if (!precedes(sequence.GetElem(i), sequence.GetElem(i + 1))) {
                    sequence.Swap(sequence.GetElem(i), sequence.GetElem(i + 1)); // Меняем местами
                    swapped = true;
                }
            }
            right--; // Уменьшаем правую границу

            // Движение влево
            for (int i = right; i > left; i--) {
                if (!precedes(sequence.GetElem(i - 1), sequence.GetElem(i))) {
                    sequence.Swap(sequence.GetElem(i), sequence.GetElem(i - 1)); // Меняем местами
                    swapped = true;
                }
            }
            left++; // Увеличиваем левую границу
        }
    }
};

//
template <typename T>
class InsertionSort : public ISorter<T> {
public:
    void Sort(Sequence<T>& sequence, bool (*precedes)(const T& first, const T& second)) override {
        int len = sequence.GetLength(); // Получаем длину последовательности
        if (len <= 1) return;           // Проверка для пустой или короткой последовательности

        for (int i = 1; i < len; i++) {
            T key = sequence.GetElem(i);    // Извлекаем текущий элемент
            int j = i - 1;

            // Перемещаем элементы, которые нарушают порядок, заданный компаратором
            while (j >= 0 && !precedes(sequence.GetElem(j), key)) {
                sequence.Set(j + 1, sequence.GetElem(j)); // Сдвигаем элемент вправо
                j--;
            }
            sequence.Set(j + 1, key); // Вставляем ключ на правильное место
        }
    }
};

template <typename T>
class HeapSort : public ISorter<T> {
public:
    void Sort(Sequence<T>& sequence, bool (*precedes)(const T& first, const T& second)) override {
        int len = sequence.GetLength();
        if (len <= 1) return; // Проверка для пустого списка или списка одного элемента

        // Построение кучи (max heap)
        for (int i = len / 2 - 1; i >= 0; i--) {
            Heapify(sequence, len, i, precedes);
        }

        // Извлечение элементов из кучи
        for (int i = len - 1; i > 0; i--) {
            sequence.Swap(sequence.GetElem(0), sequence.GetElem(i)); // Перемещение корня в конец
            Heapify(sequence, i, 0, precedes); // Восстановление кучи
        }
    }

private:
    void Heapify(Sequence<T>& sequence, int n, int i, bool (*precedes)(const T& first, const T& second)) {
        int largest = i; // Инициализация наибольшего как корень
        int left = 2 * i + 1; // Левый потомок
        int right = 2 * i + 2; // Правый потомок

        // Если левый потомок больше корня
        if (left < n && !precedes(sequence.GetElem(left), sequence.GetElem(largest))) {
            largest = left;
        }

        // Если правый потомок больше, чем наибольший на данный момент
        if (right < n && !precedes(sequence.GetElem(right), sequence.GetElem(largest))) {
            largest = right;
        }

        // Если наибольший элемент не корень
        if (largest != i) {
            sequence.Swap(sequence.GetElem(i), sequence.GetElem(largest)); // Меняем местами
            Heapify(sequence, n, largest, precedes); // Рекурсивно восстанавливаем кучу
        }
    }
};

//быстрая сортировка Ломуто
template <typename T>
class QuickSort : public ISorter<T> {
public:
    void Sort(Sequence<T>& sequence, bool (*precedes)(const T& first, const T& second)) override {
        if (sequence.GetLength() <= 1) {
            return; // Ничего не делаем для пустой или слишком короткой последовательности
        }

        // Вызов рекурсивного быстрого сортировки
        QuickSortRecursive(sequence, 0, sequence.GetLength() - 1, precedes);
    }

private:
    void QuickSortRecursive(Sequence<T>& sequence, int start, int end, bool (*precedes)(const T& first, const T& second)) {
        if (start >= end) return;

        // Разделение и рекурсивная сортировка
        int pivotIndex = Partition(sequence, start, end, precedes);
        QuickSortRecursive(sequence, start, pivotIndex - 1, precedes);
        QuickSortRecursive(sequence, pivotIndex + 1, end, precedes);
    }

    //что будет если pivot const ссылка
    int Partition(Sequence<T>& sequence, int start, int end, bool (*precedes)(const T& first, const T& second)) {
        T pivot = sequence.GetElem(end); 
        int partitionIndex = start;

        for (int i = start; i < end; i++) {
            if (precedes(sequence.GetElem(i), pivot)) {
                sequence.Swap(sequence.GetElem(i), sequence.GetElem(partitionIndex)); // Swap работает с индексами
                partitionIndex++;
            }
        }
        sequence.Swap(sequence.GetElem(partitionIndex), sequence.GetElem(end));
        return partitionIndex;
    }
};

template <typename T>
class ShellSort : public ISorter<T>
{
public:
    void Sort(Sequence<T>& sequence, bool (*precedes)(const T& first, const T& second)) override
    {
        int n = sequence.GetLength();
        if (n <= 1) return; // Проверка для пустого списка или списка одного элемента

        // Начинаем с большого шага и уменьшаем его
        for (int gap = n / 2; gap > 0; gap /= 2)
        {
            // Выполняем сортировку по вставкам для текущего шага
            for (int i = gap; i < n; i++)
            {
                T temp = sequence.GetElem(i);
                int j = i;

                // Сравниваем элементы с шагом gap, используя компаратор
                while (j >= gap && !precedes(sequence.GetElem(j - gap), temp))
                {
                    sequence.Set(j, sequence.GetElem(j - gap)); // Сдвигаем элементы
                    j -= gap;
                }
                // Вставляем элемент на его место
                sequence.Set(j, temp);
            }
        }
    }
};