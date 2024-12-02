#pragma once
#include "Sequence.h"

template <class T>
class ISorter {
public:
    virtual void Sort(Sequence<T>& sequence, bool (*precedes)(const T& first, const T& second)) = 0;

    virtual ~ISorter() {}
};