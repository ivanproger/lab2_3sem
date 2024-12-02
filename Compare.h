#pragma once
#include "PersonExtract.h"

inline bool AscendingInt(const int& first, const int& second) {
    return first < second; 
}

inline bool DescendingInt(const int& first, const int& second) {
    return first > second; 
}

inline bool PrecedesDouble(const Extract<double>& a, const Extract<double>& b) {
    return a.value < b.value;
}