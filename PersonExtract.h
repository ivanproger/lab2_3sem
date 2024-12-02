#pragma once

template <typename T>
struct Extract {
    int index;
    T value;
    Extract() : index(0), value(T()) {} // Add a default constructor
    Extract(int idx, T val) : index(idx), value(val) {}
    Extract(const Extract& other) : index(other.index), value(other.value) {}
};

