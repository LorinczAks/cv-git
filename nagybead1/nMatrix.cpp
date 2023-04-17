#include "nMatrix.h"
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <ostream>

NMatrix::NMatrix() {
    size = 5;
    int lengthOfVector = 3 * size - 2;
    vec_ = std::vector<int>(lengthOfVector, 0);

    for(int i = 0; i < vec_.size(); i++) {
        vec_[i] = 0;
    }
}

NMatrix::NMatrix(std::vector<int> vec, int n) {
    vec_=vec;
    size = n;
}

NMatrix::NMatrix(int n) {
    size = n;
    int lengthOfVector = 3 * n - 2;
    vec_ = std::vector<int>(lengthOfVector, 0);

    for(int i = 0; i < vec_.size(); i++) {
        vec_[i] = 0;
    }
}
//******************************************************
int NMatrix::getSize() const {
    return size;
}

int NMatrix::getItem(int i) const {
    return vec_[i];
}

int NMatrix::getItem(int i, int j) const {
    if(1 > i || i > size || j > size || 1 > j) {
        throw OVERINDEXED;
    }
    if( j != 1 && j != size && j != i) {
        return 0;
    }
    else {
        int index = 0;
        if (j == 1) {
            index = i-1;
        }
        else if (j == size) {
            index = 2 * size + i-1 - 2;
        }
        else {
            index = size - 1 + j-1;
        }

        return vec_[index];
    }
}

void NMatrix::setItem(int a) {
    int i = 0;
    while(i < vec_.size()) {
        vec_[i] = a;
        i++;
    }
}

void NMatrix::setItem(int i, int j, int a) {
    if(1 > i || i > size || j > size || 1 > j) {
        throw OVERINDEXED;
    }
    if (j != 1 && j != size && j != i) {
        if(a != 0) { throw NULLPART; }
    }
    else {
        int index = 0;
        if (j == 1) {
            index = i-1;
        }
        else if (j == size) {
            index = 2 * size + i-1 - 2;
        }
        else {
            index = size - 1 + j-1;
        }
        vec_[index] = a;
    }
}

int NMatrix::getVectorLength() const {
    return vec_.size();
}

std::ostream &operator<<(std::ostream &os, const NMatrix &matrix) {
    os << "The n-type matrix:\n";
    for(int i = 1; i <= (matrix.getSize()); i++) {
        for(int j = 1; j <= (matrix.getSize()); j++) {
            os << matrix.getItem(i, j) << " ";
        }
        os << "\n";
    }
    return os;
}

NMatrix NMatrix::operator+(const NMatrix &rhs) const {
    if(size == rhs.getSize()) {
        std::vector<int> result;
        for(int i = 0; i < rhs.getVectorLength(); i++) {
            result.push_back(rhs.getItem(i)+vec_[i]);
        }
        return NMatrix(result, size);
    }
    else {
        throw NOT_MATCHING_SIZE;
    }
}

NMatrix NMatrix::operator*(const NMatrix &rhs) const {
    if(size == rhs.getSize()) {
        std::vector<int> result(rhs.getVectorLength(), 0);
        NMatrix resultMatrix = NMatrix(result, size);
        for(int i = 1; i <= size; i++) {
            for(int j = 1; j <= size; j++) {
                int multiplied = 0;
                for (int k = 1; k <= size; k++) {
                    multiplied += getItem(i, k) * rhs.getItem(k, j);
                }
                resultMatrix.setItem(i, j, multiplied);  
            }
        }
        return resultMatrix;
    }
    else {
        throw NOT_MATCHING_SIZE;
    }
}

