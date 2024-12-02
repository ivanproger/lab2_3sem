#pragma once
#include "ISorter.h"
#include "Sequence.h"

template <class T>
class BubbleSorter : public ISorter<T> {
public:
    void Sort(Sequence<T>& sequence, bool (*precedes)(const T& first, const T& second)) override {
        int n = sequence.GetLength(); // �������� ����� ������������������
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (!precedes(sequence.GetElem(j), sequence.GetElem(j + 1))) {
                    // ���� ������� �������, ������ �������� �������
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
        if (len <= 1) return; // �������� ��� ������� ������ ��� ������ ������ ��������

        bool swapped = true;
        int left = 0;
        int right = len - 1;

        while (swapped) {
            swapped = false;

            // �������� ������
            for (int i = left; i < right; i++) {
                if (!precedes(sequence.GetElem(i), sequence.GetElem(i + 1))) {
                    sequence.Swap(sequence.GetElem(i), sequence.GetElem(i + 1)); // ������ �������
                    swapped = true;
                }
            }
            right--; // ��������� ������ �������

            // �������� �����
            for (int i = right; i > left; i--) {
                if (!precedes(sequence.GetElem(i - 1), sequence.GetElem(i))) {
                    sequence.Swap(sequence.GetElem(i), sequence.GetElem(i - 1)); // ������ �������
                    swapped = true;
                }
            }
            left++; // ����������� ����� �������
        }
    }
};

//
template <typename T>
class InsertionSort : public ISorter<T> {
public:
    void Sort(Sequence<T>& sequence, bool (*precedes)(const T& first, const T& second)) override {
        int len = sequence.GetLength(); // �������� ����� ������������������
        if (len <= 1) return;           // �������� ��� ������ ��� �������� ������������������

        for (int i = 1; i < len; i++) {
            T key = sequence.GetElem(i);    // ��������� ������� �������
            int j = i - 1;

            // ���������� ��������, ������� �������� �������, �������� ������������
            while (j >= 0 && !precedes(sequence.GetElem(j), key)) {
                sequence.Set(j + 1, sequence.GetElem(j)); // �������� ������� ������
                j--;
            }
            sequence.Set(j + 1, key); // ��������� ���� �� ���������� �����
        }
    }
};

template <typename T>
class HeapSort : public ISorter<T> {
public:
    void Sort(Sequence<T>& sequence, bool (*precedes)(const T& first, const T& second)) override {
        int len = sequence.GetLength();
        if (len <= 1) return; // �������� ��� ������� ������ ��� ������ ������ ��������

        // ���������� ���� (max heap)
        for (int i = len / 2 - 1; i >= 0; i--) {
            Heapify(sequence, len, i, precedes);
        }

        // ���������� ��������� �� ����
        for (int i = len - 1; i > 0; i--) {
            sequence.Swap(sequence.GetElem(0), sequence.GetElem(i)); // ����������� ����� � �����
            Heapify(sequence, i, 0, precedes); // �������������� ����
        }
    }

private:
    void Heapify(Sequence<T>& sequence, int n, int i, bool (*precedes)(const T& first, const T& second)) {
        int largest = i; // ������������� ����������� ��� ������
        int left = 2 * i + 1; // ����� �������
        int right = 2 * i + 2; // ������ �������

        // ���� ����� ������� ������ �����
        if (left < n && !precedes(sequence.GetElem(left), sequence.GetElem(largest))) {
            largest = left;
        }

        // ���� ������ ������� ������, ��� ���������� �� ������ ������
        if (right < n && !precedes(sequence.GetElem(right), sequence.GetElem(largest))) {
            largest = right;
        }

        // ���� ���������� ������� �� ������
        if (largest != i) {
            sequence.Swap(sequence.GetElem(i), sequence.GetElem(largest)); // ������ �������
            Heapify(sequence, n, largest, precedes); // ���������� ��������������� ����
        }
    }
};

//������� ���������� ������
template <typename T>
class QuickSort : public ISorter<T> {
public:
    void Sort(Sequence<T>& sequence, bool (*precedes)(const T& first, const T& second)) override {
        if (sequence.GetLength() <= 1) {
            return; // ������ �� ������ ��� ������ ��� ������� �������� ������������������
        }

        // ����� ������������ �������� ����������
        QuickSortRecursive(sequence, 0, sequence.GetLength() - 1, precedes);
    }

private:
    void QuickSortRecursive(Sequence<T>& sequence, int start, int end, bool (*precedes)(const T& first, const T& second)) {
        if (start >= end) return;

        // ���������� � ����������� ����������
        int pivotIndex = Partition(sequence, start, end, precedes);
        QuickSortRecursive(sequence, start, pivotIndex - 1, precedes);
        QuickSortRecursive(sequence, pivotIndex + 1, end, precedes);
    }

    //��� ����� ���� pivot const ������
    int Partition(Sequence<T>& sequence, int start, int end, bool (*precedes)(const T& first, const T& second)) {
        T pivot = sequence.GetElem(end); 
        int partitionIndex = start;

        for (int i = start; i < end; i++) {
            if (precedes(sequence.GetElem(i), pivot)) {
                sequence.Swap(sequence.GetElem(i), sequence.GetElem(partitionIndex)); // Swap �������� � ���������
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
        if (n <= 1) return; // �������� ��� ������� ������ ��� ������ ������ ��������

        // �������� � �������� ���� � ��������� ���
        for (int gap = n / 2; gap > 0; gap /= 2)
        {
            // ��������� ���������� �� �������� ��� �������� ����
            for (int i = gap; i < n; i++)
            {
                T temp = sequence.GetElem(i);
                int j = i;

                // ���������� �������� � ����� gap, ��������� ����������
                while (j >= gap && !precedes(sequence.GetElem(j - gap), temp))
                {
                    sequence.Set(j, sequence.GetElem(j - gap)); // �������� ��������
                    j -= gap;
                }
                // ��������� ������� �� ��� �����
                sequence.Set(j, temp);
            }
        }
    }
};